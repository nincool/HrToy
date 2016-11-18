#include "HrD3D11ShaderCompiler.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include <D3DCompiler.h>

using namespace Hr;

HrD3D11ShaderCompiler::HrD3D11ShaderCompiler()
{

}

HrD3D11ShaderCompiler::~HrD3D11ShaderCompiler()
{

}

bool HrD3D11ShaderCompiler::CompileShaderFromCode(std::string& strShaderFileName, HrStreamData& streamData
	, HrD3D11Shader::EnumShaderType shaderType
	, std::string& strEntryPoint
	, HrStreamData* pShaderBuffer)
{
	HrD3D11IncludeShaderHandler includeHandler(strShaderFileName);

	char* pSource = streamData.GetBufferPoint();
	uint64 nSize = streamData.GetBufferSize();

	std::vector<D3D_SHADER_MACRO> vecDefines;
	const D3D_SHADER_MACRO* pDefines = nullptr;
	GetShaderMacros(vecDefines, shaderType);
	pDefines = &vecDefines[0];

	UINT compileFlags = 0;
	compileFlags |= D3DCOMPILE_OPTIMIZATION_LEVEL3;
	compileFlags |= D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR; //Directs the compiler to pack matrices in column-major order on input and output from the shader. This type of packing is generally more efficient because a series of dot-products can then perform vector-matrix multiplication.
	
	std::string strShaderModel = "";
	switch (shaderType)
	{
	case HrShader::ST_VERTEX_SHADER:
		strShaderModel = "vs_5_0";
		break;
	case HrShader::ST_PIXEL_SHADER:
		strShaderModel = "ps_5_0";
		break;
	default:
		break;
	}

	ID3DBlob* pD3DShaderBuffer = nullptr;
	ID3DBlob* pErrorBuffer = nullptr;

	HRESULT hr = D3DCompile(
		pSource,					// [in] Pointer to the shader in memory. 
		nSize,						// [in] Size of the shader in memory.  
		strShaderFileName.c_str(),  // [in] Optional. You can use this parameter for strings that specify error messages.
		pDefines,					// [in] Optional. Pointer to a NULL-terminated array of macro definitions. See D3D_SHADER_MACRO. If not used, set this to NULL. 
		&includeHandler,			// [in] Optional. Pointer to an ID3DInclude Interface interface for handling include files. Setting this to NULL will cause a compile error if a shader contains a #include. 
		strEntryPoint.c_str(),		// [in] Name of the shader-entrypoint function where shader execution begins. 
		strShaderModel.c_str(),		// [in] A string that specifies the shader model; can be any profile in shader model 4 or higher. 
		compileFlags,				// [in] Effect compile flags - no D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY at the first try...
		NULL,						// [in] Effect compile flags
		&pD3DShaderBuffer,			// [out] A pointer to an ID3DBlob Interface which contains the compiled shader, as well as any embedded debug and symbol-table information. 
		&pErrorBuffer				// [out] A pointer to an ID3DBlob Interface which contains a listing of errors and warnings that occurred during compilation. These errors and warnings are identical to the the debug output from a debugger.
	);
	if (FAILED(hr))
	{
		if (pErrorBuffer != 0)
		{
			char* pMsg = (char*)(pErrorBuffer->GetBufferPointer());
			HRERROR(pMsg);
			pErrorBuffer->Release();
		}
		HRERROR(_T("CompileD3DShader Error! File"));
		return false;
	}

	if (pErrorBuffer != 0)
		pErrorBuffer->Release();

	pShaderBuffer->ResizeBuffer(pD3DShaderBuffer->GetBufferSize());
	memcpy(pShaderBuffer->GetBufferPoint(), pD3DShaderBuffer->GetBufferPointer(), pD3DShaderBuffer->GetBufferSize());

	pD3DShaderBuffer->Release();

	uint64 nBufferSize = pShaderBuffer->GetBufferSize();
	ID3D11ShaderReflection* pShaderReflection = nullptr;
	hr = D3DReflect((void*)pShaderBuffer->GetBufferPoint()
		, nBufferSize
		, IID_ID3D11ShaderReflection
		, (void**)&pShaderReflection);
	if (FAILED(hr))
	{
		HRASSERT(nullptr, "CompileD3DShader Error! D3DReflect");
	}
	D3D11_SHADER_DESC shaderDesc;
	hr = pShaderReflection->GetDesc(&shaderDesc);
	if (FAILED(hr))
	{
		HRASSERT(nullptr, "CompileD3DShader Error! GetDesc");
	}

	//get the input parameters
	m_vecD3D11ShaderInputParameters.resize(shaderDesc.InputParameters);
	for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
	{
		D3D11_SIGNATURE_PARAMETER_DESC& curParam = m_vecD3D11ShaderInputParameters[i];
		pShaderReflection->GetInputParameterDesc(i, &curParam);
	}
	//get the output parameters
	m_vecD3D11ShaderOutputParamters.resize(shaderDesc.OutputParameters);
	for (UINT i = 0; i < shaderDesc.OutputParameters; ++i)
	{
		D3D11_SIGNATURE_PARAMETER_DESC& curParam = m_vecD3D11ShaderOutputParamters[i];
		pShaderReflection->GetOutputParameterDesc(i, &curParam);
	}

	//ConstBuffer
	m_nConstantBufferNum = shaderDesc.ConstantBuffers;
	m_nNumSlots = pShaderReflection->GetNumInterfaceSlots();

	if (shaderDesc.ConstantBuffers > 0)
	{
		for (uint32 nCBIndex = 0; nCBIndex < shaderDesc.ConstantBuffers; ++nCBIndex)
		{
			ID3D11ShaderReflectionConstantBuffer* pShaderReflectionConstantBuffer = pShaderReflection->GetConstantBufferByIndex(nCBIndex);;

			D3D11_SHADER_BUFFER_DESC constantBufferDesc;
			hr = pShaderReflectionConstantBuffer->GetDesc(&constantBufferDesc);
			if (FAILED(hr))
			{
				HRASSERT(nullptr, "CompileD3DShader Error! ConstBuffer GetDesc");
			}
			if (D3D_CT_CBUFFER == constantBufferDesc.Type || D3D_CT_TBUFFER == constantBufferDesc.Type)
			{
				D3D11ShaderDesc::ConstantBufferDesc constantDesc;
				constantDesc.name = constantBufferDesc.Name;
				constantDesc.name_hash = HrHashValue(constantBufferDesc.Name);
				constantDesc.size = constantBufferDesc.Size;

				for (uint32 nCBVarIndex = 0; nCBVarIndex < constantBufferDesc.Variables; ++nCBVarIndex)
				{
					ID3D11ShaderReflectionVariable* pVarRef = pShaderReflectionConstantBuffer->GetVariableByIndex(nCBVarIndex);

					D3D11_SHADER_VARIABLE_DESC varDesc;
					pVarRef->GetDesc(&varDesc);

					D3D11_SHADER_TYPE_DESC varTypeDesc;
					ID3D11ShaderReflectionType* pVarType = pVarRef->GetType();
					pVarType->GetDesc(&varTypeDesc);

					D3D11ShaderDesc::ConstantBufferDesc::VariableDesc constantBufferVariableDesc;
					constantBufferVariableDesc.name = varDesc.Name;
					constantBufferVariableDesc.start_offset = varDesc.StartOffset;
					constantBufferVariableDesc.type = varTypeDesc.Type; //D3D_SHADER_VARIABLE_TYPE https://msdn.microsoft.com/en-us/library/windows/desktop/ff728735(v=vs.85).aspx
					constantBufferVariableDesc.rows = varTypeDesc.Rows;
					constantBufferVariableDesc.columns = varTypeDesc.Columns;
					constantBufferVariableDesc.elements = varTypeDesc.Elements;

					constantDesc.var_desc.push_back(constantBufferVariableDesc);
				}
				m_shaderDesc.cb_desc.push_back(constantDesc);
			}
		}

		int nSamplers = -1;
		int nSrvs = -1;
		int nUavs = -1;
		for (uint32_t i = 0; i < shaderDesc.BoundResources; ++i)
		{
			D3D11_SHADER_INPUT_BIND_DESC shaderInputDesc;
			pShaderReflection->GetResourceBindingDesc(i, &shaderInputDesc);

		}
	}

	SAFE_RELEASE(pShaderReflection);

}

void HrD3D11ShaderCompiler::GetShaderMacros(std::vector<D3D_SHADER_MACRO>& defines, HrD3D11Shader::EnumShaderType shaderType)
{
	//Add D3D11 define to all program, compiled with D3D11 RenderSystem
	D3D_SHADER_MACRO macro = { "D3D11","1" };
	defines.push_back(macro);

	// Using different texture sampling instructions, tex2D for D3D9 and SampleXxx for D3D11,
	// declaring type of BLENDINDICES as float4 for D3D9 but as uint4 for D3D11 -  all those
	// small but annoying differences that otherwise would require declaring separate programs.
	macro.Name = "SHADER_MODEL_5";
	defines.push_back(macro);

	switch (shaderType)
	{
	case HrShader::ST_VERTEX_SHADER:
		macro.Name = "HR_VERTEX_SAHDER";
		break;
	case HrShader::ST_PIXEL_SHADER:
		macro.Name = "HR_PIXEL_SHADER";
		break;
	case HrShader::ST_GEOMETRY_SHADER:
		macro.Name = "HR_GEOMETRY_SHADER";
		break;
	case HrShader::ST_DOMAIN_SHADER:
		macro.Name = "HR_DOMAIN_SHADER";
		break;
	case HrShader::ST_HULL_SHADER:
		macro.Name = "HR_HULL_SHADER";
		break;
	case HrShader::ST_COMPUTE_SHADER:
		macro.Name = "HR_COMPUTE_SHADER";
		break;
	default:
		BOOST_ASSERT(false);
		break;
	}
	defines.push_back(macro);

	// Add NULL terminator
	macro.Name = 0;
	macro.Definition = 0;
	defines.push_back(macro);

}

bool HrD3D11ShaderCompiler::RelfectEffectParameters(HrStreamData* pShaderBuffer)
{
	uint64 nBufferSize = pShaderBuffer->GetBufferSize();
	ID3D11ShaderReflection* pShaderReflection = nullptr;
	HRESULT hr = D3DReflect((void*)pShaderBuffer->GetBufferPoint()
		, nBufferSize
		, IID_ID3D11ShaderReflection
		, (void**)&pShaderReflection);
	if (FAILED(hr))
	{
		HRASSERT(nullptr, "CompileD3DShader Error! D3DReflect");
	}
	D3D11_SHADER_DESC shaderDesc;
	hr = pShaderReflection->GetDesc(&shaderDesc);
	if (FAILED(hr))
	{
		HRASSERT(nullptr, "CompileD3DShader Error! GetDesc");
	}

	//get the input parameters
	m_vecD3D11ShaderInputParameters.resize(shaderDesc.InputParameters);
	for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
	{
		D3D11_SIGNATURE_PARAMETER_DESC& curParam = m_vecD3D11ShaderInputParameters[i];
		pShaderReflection->GetInputParameterDesc(i, &curParam);
	}
	//get the output parameters
	m_vecD3D11ShaderOutputParamters.resize(shaderDesc.OutputParameters);
	for (UINT i = 0; i < shaderDesc.OutputParameters; ++i)
	{
		D3D11_SIGNATURE_PARAMETER_DESC& curParam = m_vecD3D11ShaderOutputParamters[i];
		pShaderReflection->GetOutputParameterDesc(i, &curParam);
	}

	m_nConstantBufferNum = shaderDesc.ConstantBuffers;
	m_nNumSlots = pShaderReflection->GetNumInterfaceSlots();

	if (shaderDesc.ConstantBuffers > 0)
	{
		for (uint32 nCBIndex = 0; nCBIndex < shaderDesc.ConstantBuffers; ++nCBIndex)
		{
			ID3D11ShaderReflectionConstantBuffer* pShaderReflectionConstantBuffer = pShaderReflection->GetConstantBufferByIndex(nCBIndex);;

			D3D11_SHADER_BUFFER_DESC constantBufferDesc;
			hr = pShaderReflectionConstantBuffer->GetDesc(&constantBufferDesc);
			if (FAILED(hr))
			{
				HRASSERT(nullptr, "CompileD3DShader Error! ConstBuffer GetDesc");
			}
			if (D3D_CT_CBUFFER == constantBufferDesc.Type || D3D_CT_TBUFFER == constantBufferDesc.Type)
			{
				D3D11ShaderDesc::ConstantBufferDesc constantDesc;
				constantDesc.name = constantBufferDesc.Name;
				constantDesc.name_hash = HrHashValue(constantBufferDesc.Name);
				constantDesc.size = constantBufferDesc.Size;

				for (uint32 nCBVarIndex = 0; nCBVarIndex < constantBufferDesc.Variables; ++nCBVarIndex)
				{
					ID3D11ShaderReflectionVariable* pVarRef = pShaderReflectionConstantBuffer->GetVariableByIndex(nCBVarIndex);

					D3D11_SHADER_VARIABLE_DESC varDesc;
					pVarRef->GetDesc(&varDesc);

					D3D11_SHADER_TYPE_DESC varTypeDesc;
					ID3D11ShaderReflectionType* pVarType = pVarRef->GetType();
					pVarType->GetDesc(&varTypeDesc);

					D3D11ShaderDesc::ConstantBufferDesc::VariableDesc constantBufferVariableDesc;
					constantBufferVariableDesc.name = varDesc.Name;
					constantBufferVariableDesc.start_offset = varDesc.StartOffset;
					constantBufferVariableDesc.type = varTypeDesc.Type; //D3D_SHADER_VARIABLE_TYPE https://msdn.microsoft.com/en-us/library/windows/desktop/ff728735(v=vs.85).aspx
					constantBufferVariableDesc.rows = varTypeDesc.Rows;
					constantBufferVariableDesc.columns = varTypeDesc.Columns;
					constantBufferVariableDesc.elements = varTypeDesc.Elements;

					constantDesc.var_desc.push_back(constantBufferVariableDesc);
				}
				m_shaderDesc.cb_desc.push_back(constantDesc);
			}
		}

		int nSamplers = -1;
		int nSrvs = -1;
		int nUavs = -1;
		for (uint32_t i = 0; i < shaderDesc.BoundResources; ++i)
		{
			D3D11_SHADER_INPUT_BIND_DESC shaderInputDesc;
			pShaderReflection->GetResourceBindingDesc(i, &shaderInputDesc);

		}
	}

	SAFE_RELEASE(pShaderReflection);

	return true;
}

