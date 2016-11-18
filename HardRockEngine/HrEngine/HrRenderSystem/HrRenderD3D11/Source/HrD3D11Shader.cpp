#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Shader.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Device.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Render/HrRenderConstantBuffer.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrRenderD3D11/Include/HrD3D11GraphicsBuffer.h"
#include "HrRenderD3D11/Include/HrD3D11Mapping.h"
#include "HrRenderD3D11/Include/HrD3D11ShaderCompiler.h"
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

void HrD3D11Shader::StreamIn(HrStreamData& streamData, std::string& strFile, const std::string& strEntryPoint, EnumShaderType shaderType)
{
	m_shaderType = shaderType;
	m_strEntryPoint = strEntryPoint;
	m_strFilePath = strFile;

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
	std::shared_ptr<HrD3D11ShaderCompiler> pShaderCompiler = std::make_shared<HrD3D11ShaderCompiler>();
	if (pShaderCompiler->CompileShaderFromCode(m_strFilePath, streamData, m_shaderType, m_strEntryPoint, m_pShaderBuffer))
	{
		D3D11ShaderDesc shaderDesc = pShaderCompiler->GetShaderDesc();
		for (size_t nConstBufferIndex = 0; nConstBufferIndex < shaderDesc.cb_desc.size(); ++nConstBufferIndex)
		{
			HrRenderConstantBuffer* pRenderConstantBuffer = AddRenderConstantBuffer();
			pRenderConstantBuffer->SetName(shaderDesc.cb_desc[nConstBufferIndex].name);
			//pRenderConstantBuffer->SetSize(shaderDesc.cb_desc[nConstBufferIndex].size);
			for (size_t nVariableIndex = 0; nVariableIndex < shaderDesc.cb_desc[nConstBufferIndex].var_desc.size(); ++nVariableIndex)
			{
				const D3D11ShaderDesc::ConstantBufferDesc::VariableDesc& variableDesc = shaderDesc.cb_desc[nConstBufferIndex].var_desc[nVariableIndex];
				pRenderConstantBuffer->AddParameter(variableDesc.name
					, HrD3D11Mapping::GetRenderParamType(variableDesc.name)
					, HrD3D11Mapping::GetRenderParamDataType(static_cast<D3D_SHADER_VARIABLE_TYPE>(variableDesc.type))
					, variableDesc.start_offset);
			}
			pRenderConstantBuffer->MakeConstBuffer(shaderDesc.cb_desc[nConstBufferIndex].size);
		}
		return true;
	}

	return false;
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

void HrD3D11Shader::UpdateParams(HrRenderFrameParameters& renderFrameParameters)
{
	HrRenderConstantBuffer* pRenderConstantBuffer = nullptr;
	for (auto& item : m_vecRenderConstantBuffer)
	{
		pRenderConstantBuffer = item;
		pRenderConstantBuffer->UpdateParams(renderFrameParameters);
	}
}

ID3D11Buffer* HrD3D11Shader::GetConstantBuffer()
{
	ID3D11Buffer* pConstantBuffer = nullptr;
	if (!m_vecRenderConstantBuffer.empty())
	{
		HrGraphicsBuffer* pGraphicsBuffer = m_vecRenderConstantBuffer[0]->GetConstBuffer();
		HrD3D11GraphicsBuffer* pD3D11HardwareBuffer = static_cast<HrD3D11GraphicsBuffer*>(pGraphicsBuffer);
		pConstantBuffer = pD3D11HardwareBuffer->GetGraphicsBuffer();
	}

	return pConstantBuffer;
}


