#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Shader.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Device.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Render/HrRenderConstantBuffer.h"
#include "HrCore/Include/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrRenderD3D11/Include/HrD3D11HardwareBuffer.h"
#include "HrRenderD3D11/Include/HrD3D11Mapping.h"
#include <boost/cast.hpp>

using namespace Hr;

HrD3D11Shader::HrD3D11Shader()
{
	m_pShaderBuffer = HR_NEW HrStreamData();
	m_pVertexShader = nullptr;
	m_pPixelShader = nullptr;
}

HrD3D11Shader::~HrD3D11Shader()
{
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_DELETE(m_pShaderBuffer);
}

void HrD3D11Shader::Bind(HrRender* pRender)
{
	HrD3D11Render* pD3D11Render = boost::polymorphic_cast<HrD3D11Render*>(pRender);
	ID3D11DeviceContext* pD3D11ImmediateContext = pD3D11Render->GetD3D11ImmediateContext();

	switch (m_shaderType)
	{
	case HrShader::ST_VERTEX_SHADER:
	{
		//更新constant数据
		ID3D11Buffer* pConstantBuffer = GetConstantBuffer();
		pD3D11ImmediateContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		pD3D11ImmediateContext->VSSetShader(m_pVertexShader, nullptr, 0);
		break;
	}
	case HrShader::ST_PIXEL_SHADER:
	{
		pD3D11ImmediateContext->PSSetShader(m_pPixelShader, nullptr, 0);
		break;
	}
	default:
		break;
	}
}

void HrD3D11Shader::UnBind(HrRender* pRender)
{

}

void HrD3D11Shader::StreamIn(HrStreamData& streamData)
{
	if (!CompileShader(streamData))
	{
		return;
	}

	switch (m_shaderType)
	{
	case HrShader::ST_VERTEX_SHADER:
		CreateVertexShader();
		break;
	case HrShader::ST_PIXEL_SHADER:
		CreatePixelShader();
		break;
	default:
		break;
	}
}

bool HrD3D11Shader::CompileShader(HrStreamData& streamData)
{
	char* pSource = streamData.GetBufferPoint();
	uint64 nSize = streamData.GetBufferSize();

	ID3DBlob* pShaderBuffer = nullptr;
	ID3DBlob* pErrorBuffer = nullptr;

	std::string strShaderModel = "";
	switch (m_shaderType)
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

	HRESULT hr = D3DCompile(
		pSource,              // [in] Pointer to the shader in memory. 
		nSize,                // [in] Size of the shader in memory.  
		nullptr,              // [in] Optional. You can use this parameter for strings that specify error messages.
		nullptr,              // [in] Optional. Pointer to a NULL-terminated array of macro definitions. See D3D_SHADER_MACRO. If not used, set this to NULL. 
		nullptr,              // [in] Optional. Pointer to an ID3DInclude Interface interface for handling include files. Setting this to NULL will cause a compile error if a shader contains a #include. 
		m_strEntryPoint.c_str(),  // [in] Name of the shader-entrypoint function where shader execution begins. 
		strShaderModel.c_str(),   // [in] A string that specifies the shader model; can be any profile in shader model 4 or higher. 
		0,                    // [in] Effect compile flags - no D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY at the first try...
		NULL,                 // [in] Effect compile flags
		&pShaderBuffer,       // [out] A pointer to an ID3DBlob Interface which contains the compiled shader, as well as any embedded debug and symbol-table information. 
		&pErrorBuffer         // [out] A pointer to an ID3DBlob Interface which contains a listing of errors and warnings that occurred during compilation. These errors and warnings are identical to the the debug output from a debugger.
		);
	if (FAILED(hr))
	{
		if (pErrorBuffer != 0)
		{
			char* pMsg = (char*)(pErrorBuffer->GetBufferPointer());
			pErrorBuffer->Release();
		}
		HRERROR(_T("CompileD3DShader Error! File"));
		return false;
	}

	if (pErrorBuffer != 0)
		pErrorBuffer->Release();

	m_pShaderBuffer->ResizeBuffer(pShaderBuffer->GetBufferSize());
	memcpy(m_pShaderBuffer->GetBufferPoint(), pShaderBuffer->GetBufferPointer(), pShaderBuffer->GetBufferSize());

	pShaderBuffer->Release();

	uint64 nBufferSize = m_pShaderBuffer->GetBufferSize();
	ID3D11ShaderReflection* pShaderReflection = nullptr;
	hr = D3DReflect((void*)m_pShaderBuffer->GetBufferPoint()
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
				constantDesc.name_hash = Hr_Hash_Value(constantBufferDesc.Name);
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
					constantBufferVariableDesc.type = varTypeDesc.Type;
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

	CreateShaderParams();

	return true;
}

void HrD3D11Shader::CreateShaderParams()
{
	for (size_t nConstBufferIndex = 0; nConstBufferIndex < m_shaderDesc.cb_desc.size(); ++nConstBufferIndex)
	{
		HrRenderConstantBuffer* pRenderConstantBuffer = AddRenderConstantBuffer();
		pRenderConstantBuffer->SetName(m_shaderDesc.cb_desc[nConstBufferIndex].name);
		pRenderConstantBuffer->SetSize(m_shaderDesc.cb_desc[nConstBufferIndex].size);
		for (size_t nVariableIndex = 0; nVariableIndex < m_shaderDesc.cb_desc[nConstBufferIndex].var_desc.size(); ++nVariableIndex)
		{
			const D3D11ShaderDesc::ConstantBufferDesc::VariableDesc& variableDesc = m_shaderDesc.cb_desc[nConstBufferIndex].var_desc[nVariableIndex];
			pRenderConstantBuffer->AddParameter(variableDesc.name
				, HrD3D11Mapping::GetRenderParamType(variableDesc.name)
				, HrD3D11Mapping::GetRenderParamDataType(static_cast<D3D_SHADER_VARIABLE_TYPE>(variableDesc.type))
				, variableDesc.start_offset);
		}
	}
}

void HrD3D11Shader::CreateVertexShader()
{
	HRESULT hr = HrD3D11Device::Instance()->GetDevice()->CreateVertexShader(m_pShaderBuffer->GetBufferPoint()
		, m_pShaderBuffer->GetBufferSize(), 0, &m_pVertexShader);
	if (FAILED(hr))
	{
		HRERROR(_T("CompileD3DShader Error! CreateVertexShader!"));
		return;
	}
}

void HrD3D11Shader::CreatePixelShader()
{
	HRESULT hr = HrD3D11Device::Instance()->GetDevice()->CreatePixelShader(m_pShaderBuffer->GetBufferPoint()
		, m_pShaderBuffer->GetBufferSize(), 0, &m_pPixelShader);
	if (FAILED(hr))
	{
		HRERROR(_T("CompileD3DShader Error! CreatePixelShader!"));
		return;
	}
}

void HrD3D11Shader::UpdateAutoParams(HrRenderFrameParameters& renderFrameParameters)
{
	HrRenderConstantBuffer* pRenderConstantBuffer = nullptr;
	for (auto& item : m_vecRenderConstantBuffer)
	{
		pRenderConstantBuffer = item;
		pRenderConstantBuffer->UpdateAutoParams(renderFrameParameters);
	}
}

ID3D11Buffer* HrD3D11Shader::GetConstantBuffer()
{
	ID3D11Buffer* pConstantBuffer = nullptr;
	if (!m_vecRenderConstantBuffer.empty())
	{
		HrGraphicsBuffer* pGraphicsBuffer = m_vecRenderConstantBuffer[0]->GetConstBuffer();
		HrD3D11HardwareBuffer* pD3D11HardwareBuffer = static_cast<HrD3D11HardwareBuffer*>(pGraphicsBuffer);
		pConstantBuffer = pD3D11HardwareBuffer->GetGraphicsBuffer();
	}

	return pConstantBuffer;
}



