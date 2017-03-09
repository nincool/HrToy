#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Shader.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Device.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrRenderD3D11/Include/HrD3D11GraphicsBuffer.h"
#include "HrRenderD3D11/Include/HrD3D11Mapping.h"
#include "HrRenderD3D11/Include/HrD3D11ShaderCompiler.h"
#include "HrRenderD3D11/Include/HrD3D11Texture.h"
#include "HrRenderD3D11/Include/HrD3D11SamplerState.h"
#include "HrUtilTools/Include/HrUtil.h"

#include <boost/cast.hpp>

using namespace Hr;

HrD3D11Shader::HrD3D11Shader()
{
	m_pVertexShader = nullptr;
	m_pPixelShader = nullptr;
	m_pShaderBuffer = HR_NEW HrStreamData();
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

	//汗。。。。
	m_vecD3D11SRV.clear();
	m_vecSamplerState.clear();
	for (size_t i = 0; i < m_vecBindRenderParameter.size(); ++i)
	{
		if (m_vecBindRenderParameter[i]->BindType() == HrRenderEffectParameter::REPBT_RESOURCE)
		{
			switch (m_vecBindRenderParameter[i]->DataType())
			{
			case REDT_TEXTURE2D:
			{
				HrTexture* pTex = nullptr;
				m_vecBindRenderParameter[i]->Value(pTex);
				HrD3D11Texture2D* pTex2D = HrCheckPointerCast<HrD3D11Texture2D>(pTex);
				if (pTex2D != nullptr)
					m_vecD3D11SRV.push_back(pTex2D->GetD3D11SRV());
				break;
			}
			case REDT_SAMPLER2D:
			{
				HrSamplerState* pSampler = nullptr;
				m_vecBindRenderParameter[i]->Value(pSampler);
				HrD3D11SamplerState* pSampler2D = HrCheckPointerCast<HrD3D11SamplerState>(pSampler);
				if (pSampler2D != nullptr)
					m_vecSamplerState.push_back(pSampler2D->GetD3D11SamplerState());
				break;
			}
			}

		}
	}

	switch (m_shaderType)
	{
	case HrShader::ST_VERTEX_SHADER:
	{
		pD3D11ImmediateContext->VSSetShader(m_pVertexShader, nullptr, 0);

		if (!m_vecD3D11ConstBuffer.empty())
		{
			//todo if the rende has binded the buffer, then continue
			pD3D11ImmediateContext->VSSetConstantBuffers(0, m_vecD3D11ConstBuffer.size(), &m_vecD3D11ConstBuffer[0]);
			if (!m_vecD3D11SRV.empty())
				pD3D11ImmediateContext->VSSetShaderResources(0, m_vecD3D11SRV.size(), &m_vecD3D11SRV[0]);
			if (!m_vecSamplerState.empty())
				pD3D11ImmediateContext->VSSetSamplers(0, m_vecSamplerState.size(), &m_vecSamplerState[0]);
			break;
		}
		break;
	}
	case HrShader::ST_PIXEL_SHADER:
	{
		pD3D11ImmediateContext->PSSetShader(m_pPixelShader, nullptr, 0);
		if (!m_vecD3D11SRV.empty())
			pD3D11ImmediateContext->PSSetShaderResources(0, m_vecD3D11SRV.size(), &m_vecD3D11SRV[0]);
		if (!m_vecSamplerState.empty())
			pD3D11ImmediateContext->PSSetSamplers(0, m_vecSamplerState.size(), &m_vecSamplerState[0]);
		break;
	}
	default:
		break;
	}
}

void HrD3D11Shader::UnBind(HrRender* pRender)
{

}

void HrD3D11Shader::StreamIn(HrStreamData& streamBuffer, const std::string& strFile, const std::string& strName, EnumShaderType shaderType)
{
	m_shaderType = shaderType;
	m_strFilePath = strFile;
	m_strName = strName;
	m_nHashName = HrHashValue(strName);
	m_pShaderBuffer->CopyFrom(streamBuffer);

	switch (m_shaderType)
	{
	case HrShader::ST_VERTEX_SHADER:
		CreateVertexShader(streamBuffer);
		break;
	case HrShader::ST_PIXEL_SHADER:
		CreatePixelShader(streamBuffer);
		break;
	default:
		break;
	}
}

void HrD3D11Shader::CreateVertexShader(HrStreamData& streamBuffer)
{
	HRESULT hr = HrD3D11Device::Instance()->GetDevice()->CreateVertexShader(streamBuffer.GetBufferPoint()
		, streamBuffer.GetBufferSize(), 0, &m_pVertexShader);
	if (FAILED(hr))
	{
		HRERROR(_T("CompileD3DShader Error! CreateVertexShader!"));
		return;
	}
}

void HrD3D11Shader::CreatePixelShader(HrStreamData& streamBuffer)
{
	HRESULT hr = HrD3D11Device::Instance()->GetDevice()->CreatePixelShader(streamBuffer.GetBufferPoint()
		, streamBuffer.GetBufferSize(), 0, &m_pPixelShader);
	if (FAILED(hr))
	{
		HRERROR(_T("CompileD3DShader Error! CreatePixelShader!"));
		return;
	}
}

void HrD3D11Shader::BindRenderParameterImpl()
{
	for (size_t i = 0; i < m_vecBindRenderConstantBuffer.size(); ++i)
	{
		HrD3D11GraphicsBuffer* pGraphicsBuffer = HrCheckPointerCast<HrD3D11GraphicsBuffer>(m_vecBindRenderConstantBuffer[i]->GetGraphicsBuffer());
		m_vecD3D11ConstBuffer.push_back(pGraphicsBuffer->GetD3DGraphicsBuffer());
	}
}

