#include "HrD3D11ShaderCompiler.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Asset/HrRenderEffectParameter.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include <D3DCompiler.h>
#include <algorithm>

using namespace Hr;

HrD3D11ShaderCompiler::HrD3D11ShaderCompiler()
{

}

HrD3D11ShaderCompiler::~HrD3D11ShaderCompiler()
{

}

bool HrD3D11ShaderCompiler::CompileShaderFromCode(std::string& strShaderFileName, HrStreamData& streamData
	, HrShader::EnumShaderType shaderType
	, const std::string& strEntryPoint
	, HrStreamData& shaderBuffer)
{
	HrD3D11IncludeShaderHandler includeHandler(strShaderFileName);

	Byte* pSource = streamData.GetBufferPoint();
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
		BOOST_ASSERT(nullptr);
		return false;
	}

	if (pErrorBuffer != 0)
		pErrorBuffer->Release();

	shaderBuffer.ResizeBuffer(pD3DShaderBuffer->GetBufferSize());
	memcpy(shaderBuffer.GetBufferPoint(), pD3DShaderBuffer->GetBufferPointer(), pD3DShaderBuffer->GetBufferSize());

	pD3DShaderBuffer->Release();
}

void HrD3D11ShaderCompiler::GetShaderMacros(std::vector<D3D_SHADER_MACRO>& defines, HrShader::EnumShaderType shaderType)
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

bool HrD3D11ShaderCompiler::ReflectEffectParameters(HrStreamData& shaderBuffer, const std::string& strShaderEntryPoint, HrShader::EnumShaderType shaderType)
{
	uint64 nBufferSize = shaderBuffer.GetBufferSize();
	ID3D11ShaderReflection* pShaderReflection = nullptr;
	TIF(D3DReflect((void*)shaderBuffer.GetBufferPoint()
		, nBufferSize
		, IID_ID3D11ShaderReflection
		, (void**)&pShaderReflection));
	
	D3D11_SHADER_DESC shaderDesc;
	TIF(pShaderReflection->GetDesc(&shaderDesc));

	m_nConstantBufferNum = shaderDesc.ConstantBuffers;
	m_nNumSlots = pShaderReflection->GetNumInterfaceSlots();

	size_t nEntryHashName = HrHashValue(strShaderEntryPoint);
	m_mapShaderDesc.insert(std::make_pair(nEntryHashName, D3D11ShaderDesc()));
	auto& desc = m_mapShaderDesc.find(nEntryHashName)->second;
	desc.shaderType = shaderType;
	for (uint32 nCBIndex = 0; nCBIndex < shaderDesc.ConstantBuffers; ++nCBIndex)
	{
		ID3D11ShaderReflectionConstantBuffer* pShaderReflectionConstantBuffer = pShaderReflection->GetConstantBufferByIndex(nCBIndex);;

		D3D11_SHADER_BUFFER_DESC constantBufferDesc;
		TIF(pShaderReflectionConstantBuffer->GetDesc(&constantBufferDesc));

		D3D_CBUFFER_TYPE bufferType = constantBufferDesc.Type;

		switch (bufferType)
		{
		case D3D_CT_CBUFFER:
		case D3D_CT_TBUFFER:
		{
			D3D11ShaderDesc::ConstantBufferDesc cbDesc;
			cbDesc.name = constantBufferDesc.Name;
			cbDesc.name_hash = HrHashValue(cbDesc.name);
			cbDesc.size = constantBufferDesc.Size;

			for (uint32 nCBVarIndex = 0; nCBVarIndex < constantBufferDesc.Variables; ++nCBVarIndex)
			{
				ID3D11ShaderReflectionVariable* pVarRef = pShaderReflectionConstantBuffer->GetVariableByIndex(nCBVarIndex);

				D3D11_SHADER_VARIABLE_DESC constVarDesc;
				TIF(pVarRef->GetDesc(&constVarDesc));

				ID3D11ShaderReflectionType* pVarRefType = pVarRef->GetType();
				D3D11_SHADER_TYPE_DESC varRefTypeDesc;
				TIF(pVarRefType->GetDesc(&varRefTypeDesc));

				D3D11ShaderDesc::ConstantBufferDesc::VariableDesc constantVariableDesc;
				constantVariableDesc.name = constVarDesc.Name;
				constantVariableDesc.start_offset = constVarDesc.StartOffset;
				constantVariableDesc.size = static_cast<uint32>(constVarDesc.Size);

				constantVariableDesc.varClass = static_cast<uint32>(varRefTypeDesc.Class);
				constantVariableDesc.type = static_cast<uint8>(varRefTypeDesc.Type);//D3D_SHADER_VARIABLE_TYPE https://msdn.microsoft.com/en-us/library/windows/desktop/ff728735(v=vs.85).aspx
				constantVariableDesc.rows = static_cast<uint8>(varRefTypeDesc.Rows);
				constantVariableDesc.columns = static_cast<uint8>(varRefTypeDesc.Columns);
				constantVariableDesc.elements = static_cast<uint16>(varRefTypeDesc.Elements);
				constantVariableDesc.bUsed = constVarDesc.uFlags & D3D_SVF_USED;

				{
					size_t nSeed = HrHashValue(constVarDesc.Name);
					boost::hash_combine(nSeed, constantVariableDesc.varClass);
					boost::hash_combine(nSeed, constantVariableDesc.type);
					boost::hash_combine(nSeed, constantVariableDesc.rows);
					boost::hash_combine(nSeed, constantVariableDesc.columns);
					boost::hash_combine(nSeed, constantVariableDesc.elements);
					constantVariableDesc.name_hash = nSeed;
				}

				if (constantVariableDesc.varClass == D3D_SVC_STRUCT)
				{
					const UINT nParentOffset = constVarDesc.StartOffset;
					for (uint32 nStructVarIndex = 0; nStructVarIndex < varRefTypeDesc.Members; ++nStructVarIndex)
					{
						D3D11_SHADER_TYPE_DESC memberTypeDesc;
						ID3D11ShaderReflectionType* pMemberType = pVarRefType->GetMemberTypeByIndex(nStructVarIndex);

						pMemberType->GetDesc(&memberTypeDesc);
						D3D11ShaderDesc::ConstantBufferDesc::VariableDesc structVariableDesc;
						structVariableDesc.name = pVarRefType->GetMemberTypeName(nStructVarIndex);
						structVariableDesc.start_offset = memberTypeDesc.Offset + nParentOffset;
						structVariableDesc.varClass = static_cast<uint32>(memberTypeDesc.Class);
						structVariableDesc.type = static_cast<uint8>(memberTypeDesc.Type);
						structVariableDesc.rows = static_cast<uint8>(memberTypeDesc.Rows);
						structVariableDesc.columns = static_cast<uint8>(memberTypeDesc.Columns);
						structVariableDesc.elements = static_cast<uint16>(memberTypeDesc.Elements);
						structVariableDesc.bUsed = constantVariableDesc.bUsed;

						{
							size_t nSeed = HrHashValue(structVariableDesc.name);
							boost::hash_combine(nSeed, constVarDesc.Name);
							boost::hash_combine(nSeed, structVariableDesc.varClass);
							boost::hash_combine(nSeed, structVariableDesc.type);
							boost::hash_combine(nSeed, structVariableDesc.rows);
							boost::hash_combine(nSeed, structVariableDesc.columns);
							boost::hash_combine(nSeed, structVariableDesc.elements);
							structVariableDesc.name_hash = nSeed;						
						}

						constantVariableDesc.struct_desc.push_back(structVariableDesc);
					}
				}

				cbDesc.var_desc.push_back(constantVariableDesc);

			}
			desc.cb_desc.push_back(cbDesc);

			break;
		}
		default:
			break;
		}
	}

	int nSamplers = -1;
	int nSrvs = -1;
	int nUavs = -1;
	for (uint32 i = 0; i < shaderDesc.BoundResources; ++i)
	{
		D3D11_SHADER_INPUT_BIND_DESC shaderInputDesc;
		pShaderReflection->GetResourceBindingDesc(i, &shaderInputDesc);

		switch (shaderInputDesc.Type)
		{
		case D3D_SIT_SAMPLER:
			nSamplers = (std::max)(nSamplers, static_cast<int>(shaderInputDesc.BindPoint));
			break;

		case D3D_SIT_TEXTURE:
		case D3D_SIT_STRUCTURED:
		case D3D_SIT_BYTEADDRESS:
			nSrvs = (std::max)(nSrvs, static_cast<int>(shaderInputDesc.BindPoint));
			break;

		case D3D_SIT_UAV_RWTYPED:
		case D3D_SIT_UAV_RWSTRUCTURED:
		case D3D_SIT_UAV_RWBYTEADDRESS:
		case D3D_SIT_UAV_APPEND_STRUCTURED:
		case D3D_SIT_UAV_CONSUME_STRUCTURED:
		case D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER:
			nUavs = (std::max)(nUavs, static_cast<int>(shaderInputDesc.BindPoint));
			break;

		default:
			D3D11ShaderDesc::BoundResourceDesc bindResourceDesc;
			bindResourceDesc.name = shaderInputDesc.Name;
			bindResourceDesc.type = static_cast<uint8>(shaderInputDesc.Type);
			bindResourceDesc.bind_point = static_cast<uint16>(shaderInputDesc.BindPoint);
			bindResourceDesc.dimension = static_cast<uint8>(shaderInputDesc.Dimension);
			desc.res_desc.push_back(bindResourceDesc);

			break;
		}
	}
	desc.num_samplers = static_cast<uint16>(nSamplers + 1);
	desc.num_srvs = static_cast<uint16>(nSrvs + 1);
	desc.num_uavs = static_cast<uint16>(nUavs + 1);

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

	SAFE_RELEASE(pShaderReflection);

	return true;
}

bool HrD3D11ShaderCompiler::StripCompiledCode(HrStreamData& shaderBuffer)
{
	ID3DBlob* pStrippedBlob = nullptr;
	HRESULT hr = D3DStripShader(shaderBuffer.GetBufferPoint(), shaderBuffer.GetBufferSize(), D3DCOMPILER_STRIP_REFLECTION_DATA | D3DCOMPILER_STRIP_DEBUG_INFO
		| D3DCOMPILER_STRIP_TEST_BLOBS | D3DCOMPILER_STRIP_PRIVATE_DATA, &pStrippedBlob);
	shaderBuffer.ClearBuffer();
	shaderBuffer.AddBuffer(static_cast<uint8*>(pStrippedBlob->GetBufferPointer()), pStrippedBlob->GetBufferSize());
	SAFE_RELEASE(pStrippedBlob);

	return true;
}

void HrD3D11ShaderCompiler::CreateEffectParameters(std::vector<HrRenderEffectParameter*>& vecParameter
	, std::vector<HrRenderEffectStructParameter*>& vecRenderEffectStruct
	, std::vector<HrRenderEffectConstantBuffer*>& vecConstantBuffer)
{
	for (auto shaderDescItem : m_mapShaderDesc)
	{
		D3D11ShaderDesc& shaderDesc = shaderDescItem.second;
		uint32 nConstBuffer = shaderDesc.cb_desc.size();
		for (uint32 nCBIndex = 0; nCBIndex < nConstBuffer; ++nCBIndex)
		{
			D3D11ShaderDesc::ConstantBufferDesc& cbDesc = shaderDesc.cb_desc[nCBIndex];

			HrRenderEffectConstantBuffer* pConstBuffer = GetConstantBuffer(vecConstantBuffer, cbDesc.name_hash);
			if (pConstBuffer == nullptr)
			{
				pConstBuffer = HR_NEW HrRenderEffectConstantBuffer(cbDesc.name
					, cbDesc.name_hash, cbDesc.size);
				vecConstantBuffer.push_back(pConstBuffer);
			}

			uint32 nVarNum = shaderDesc.cb_desc[nCBIndex].var_desc.size();
			for (uint32 nVarIndex = 0; nVarIndex < nVarNum; ++nVarIndex)
			{
				D3D11ShaderDesc::ConstantBufferDesc::VariableDesc& varDesc = shaderDesc.cb_desc[nCBIndex].var_desc[nVarIndex];
				if (varDesc.varClass == D3D_SVC_STRUCT)
				{
					uint32 nStructSize = 0;

					HrRenderEffectStructParameter* pEffectStruct = HR_NEW HrRenderEffectStructParameter(varDesc.name, varDesc.name_hash);
					for (uint32 nStructMemIndex = 0; nStructMemIndex < varDesc.struct_desc.size(); ++nStructMemIndex)
					{
						D3D11ShaderDesc::ConstantBufferDesc::VariableDesc& varStructMen = varDesc.struct_desc[nStructMemIndex];
						HrRenderEffectParameter* pEffectParameter = HR_NEW HrRenderEffectParameter(varStructMen.name, varStructMen.name_hash);
						HrRenderParamDefine* pRenderParamDefine = GetRenderParamDefine(varStructMen.name);
						if (pRenderParamDefine != nullptr)
						{
							pEffectParameter->ParamInfo(pRenderParamDefine->paramType, pRenderParamDefine->dataType, varDesc.elements);
							size_t nParamSize = pRenderParamDefine->nSize;
							nStructSize += nParamSize;
							pEffectParameter->BindConstantBuffer(pConstBuffer, varStructMen.start_offset);
						}
						pEffectStruct->AddRenderEffectParameter(pEffectParameter);
					}
					vecRenderEffectStruct.push_back(pEffectStruct);

					BOOST_ASSERT(nStructSize == varDesc.size);
				}
				else
				{
					//if it is worldviewprojmatrix , the class is D3D_SVC_MATRIX_COLUMNS, need to transpose the matrix
					HrRenderEffectParameter* pEffectParameter = HR_NEW HrRenderEffectParameter(varDesc.name, varDesc.name_hash);
					HrRenderParamDefine* pRenderParamDefine = GetRenderParamDefine(varDesc.name);
					if (pRenderParamDefine != nullptr)
					{
						pEffectParameter->ParamInfo(pRenderParamDefine->paramType, pRenderParamDefine->dataType, varDesc.elements);
						pEffectParameter->BindConstantBuffer(pConstBuffer, varDesc.start_offset);
					}

					vecParameter.push_back(pEffectParameter);
				}
			}

		}

	}
}

HrRenderEffectConstantBuffer* HrD3D11ShaderCompiler::GetConstantBuffer(std::vector<HrRenderEffectConstantBuffer*>& renderEffectConstBuffer, size_t nHashName)
{
	for (uint32 nRECBIndex = 0; nRECBIndex < renderEffectConstBuffer.size(); ++nRECBIndex)
	{
		if (renderEffectConstBuffer[nRECBIndex]->HashName() == nHashName)
		{
			return renderEffectConstBuffer[nRECBIndex];
		}
	}

	return nullptr;
}

HrRenderEffectParameter* HrD3D11ShaderCompiler::GetEffectParameter(std::vector<HrRenderEffectParameter*>& renderEffectParameter, size_t nHashName)
{
	for (uint32 nREPIndex = 0; nREPIndex < renderEffectParameter.size(); ++nREPIndex)
	{
		if (renderEffectParameter[nREPIndex]->HashName() == nHashName)
		{
			return renderEffectParameter[nREPIndex];
		}
	}

	return nullptr;
}

HrRenderParamDefine* HrD3D11ShaderCompiler::GetRenderParamDefine(const std::string& strParamName)
{
	uint32 nDefineParamSize = HrRenderParamDefine::m_s_vecRenderParamDefine.size();
	for (uint32 i = 0; i < nDefineParamSize; ++i)
	{
		if (strParamName == HrRenderParamDefine::m_s_vecRenderParamDefine[i].strName)
		{
			return &HrRenderParamDefine::m_s_vecRenderParamDefine[i];
		}
	}

	return nullptr;
}

void HrD3D11ShaderCompiler::BindParametersToShader(std::vector<HrRenderEffectParameter*>& vecParameter
	, std::vector<HrRenderEffectConstantBuffer*>& vecConstantBuffer
	, std::vector<HrShader*>& vecShader)
{
	std::vector<HrRenderEffectParameter*> vecShaderBindParameters;
	std::vector<HrRenderEffectConstantBuffer*> vecShaderBindConstantBuffers;
	for (auto itemShader : vecShader)
	{
		for (auto itemDesc : m_mapShaderDesc)
		{
			if (itemShader->HashName() == itemDesc.first)
			{
				D3D11ShaderDesc& desc = itemDesc.second;
				for (size_t nCBIndex = 0; nCBIndex < desc.cb_desc.size(); ++nCBIndex)
				{
					HrRenderEffectConstantBuffer* pConstBuffer = GetConstantBuffer(vecConstantBuffer, desc.cb_desc[nCBIndex].name_hash);
					BOOST_ASSERT(pConstBuffer);
					vecShaderBindConstantBuffers.push_back(pConstBuffer);
					
					for (size_t nVarIndex = 0; nVarIndex < desc.cb_desc[nCBIndex].var_desc.size(); ++nVarIndex)
					{
						HrRenderEffectParameter* pParameter = GetEffectParameter(vecParameter, desc.cb_desc[nCBIndex].var_desc[nVarIndex].name_hash);
						BOOST_ASSERT(pParameter);
						vecShaderBindParameters.push_back(pParameter);
					}
				}

				break;
			}
		}
		itemShader->BindRenderParameter(vecShaderBindParameters, vecShaderBindConstantBuffers);
	}
}

//
//struct D3D11ShaderDesc
//{
//	D3D11ShaderDesc()
//		: num_samplers(0), num_srvs(0), num_uavs(0)
//	{
//	}
//
//	struct ConstantBufferDesc
//	{
//		ConstantBufferDesc()
//			: size(0)
//		{
//		}
//
//		struct VariableDesc
//		{
//			std::string name;
//			uint32 start_offset;
//			uint32 varClass;
//			uint32 type;
//			uint32 rows;
//			uint32 columns;
//			uint32 elements;
//			bool bUsed;
//		};
//		std::vector<VariableDesc> var_desc;
//
//		std::string name;
//		size_t name_hash;
//		uint32_t size;
//	};
//	std::vector<ConstantBufferDesc> cb_desc;
//
//	uint16_t num_samplers;
//	uint16_t num_srvs;
//	uint16_t num_uavs;
//
//	struct BoundResourceDesc
//	{
//		std::string name;
//		uint8_t type;
//		uint8_t dimension;
//		uint16_t bind_point;
//	};
//	std::vector<BoundResourceDesc> res_desc;
//};
