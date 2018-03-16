#include "HrD3D11Render.h"
#include "HrD3D11Shader.h"
#include "HrD3D11RenderTarget.h"
#include "HrD3D11RenderLayout.h"
#include "HrD3D11Mapping.h"
#include "HrD3D11FrameBuffer.h"
#include "HrCore/Include/Render/HrRenderable.h"
#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrViewPort.h"
#include "HrCore/Include/Render/HrRenderTarget.h"
#include "HrUtilTools/Include/HrUtil.h"
#include <boost/cast.hpp>

using namespace Hr;

HrD3D11Render::HrD3D11Render()
{
}

HrD3D11Render::~HrD3D11Render()
{
}

bool HrD3D11Render::Init()
{
	HrD3D11Device::Instance()->CreateD3D11Device();

	return true;
}

void HrD3D11Render::BindFrameBuffer(const HrRenderFramePtr& pRenderFrameBuffer)
{
	m_pCurFrameBuffer = pRenderFrameBuffer;
	m_pCurFrameBuffer->OnBind();
}

const HrRenderFramePtr& HrD3D11Render::GetBindFrameBuffer()
{
	return m_pCurFrameBuffer;
}

void HrD3D11Render::SetCurrentViewPort(const HrViewPortPtr& pViewPort)
{
	D3D11_VIEWPORT vp;
	// Setup the viewport to match the backbuffer
	ZeroMemory(&vp, sizeof(vp));
	vp.TopLeftX = pViewPort->GetTopX();
	vp.TopLeftY = pViewPort->GetTopY();
	vp.Width = pViewPort->GetWidth();
	vp.Height = pViewPort->GetHeight();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	GetD3D11DeviceContext()->RSSetViewports(1, &vp);
}

void HrD3D11Render::ReleaseRenderEngine()
{
	HrD3D11Device::Instance()->Release();
}

void HrD3D11Render::BindShader(const HrShaderPtr& pShader)
{
	//HrD3D11Render* pD3D11Render = boost::polymorphic_cast<HrD3D11Render*>(pRender);
	//ID3D11DeviceContext* pD3D11ImmediateContext = pD3D11Render->GetD3D11DeviceContext().get();

	////汗。。。。todo
	//m_vecD3D11SRV.clear();
	//m_vecSamplerState.clear();
	//for (size_t i = 0; i < m_vecBindRenderParameter.size(); ++i)
	//{
	//	if (m_vecBindRenderParameter[i]->BindType() == HrRenderEffectParameter::REPBT_RESOURCE)
	//	{
	//		switch (m_vecBindRenderParameter[i]->DataType())
	//		{
	//		case REDT_TEXTURE2D:
	//		{
	//			HrTexture* pTex = nullptr;
	//			m_vecBindRenderParameter[i]->Value(pTex);
	//			HrD3D11Texture2D* pTex2D = HrCheckPointerCast<HrD3D11Texture2D>(pTex);
	//			//if (pTex2D != nullptr)
	//			//	m_vecD3D11SRV.push_back(pTex2D->GetD3D11SRV());
	//			break;
	//		}
	//		case REDT_SAMPLER2D:
	//		{
	//			HrSamplerState* pSampler = nullptr;
	//			m_vecBindRenderParameter[i]->Value(pSampler);
	//			HrD3D11SamplerState* pSampler2D = HrCheckPointerCast<HrD3D11SamplerState>(pSampler);
	//			if (pSampler2D != nullptr)
	//				m_vecSamplerState.push_back(pSampler2D->GetD3D11SamplerState());
	//			break;
	//		}
	//		}

	//	}
	//}

	HrD3D11ShaderPtr pD3D11Shader = HrCheckPointerCast<HrD3D11Shader>(pShader);
	auto shaderType = pD3D11Shader->ShaderType();
	switch (shaderType)
	{
	case HrShader::ST_VERTEX_SHADER:
	{
		GetD3D11DeviceContext()->VSSetShader(pD3D11Shader->RetriveD3D11VertexShader().get(), nullptr, 0);
		const std::vector<ID3D11Buffer*>& vecConstBuffers = pD3D11Shader->GetConstBuffers();
		if (!vecConstBuffers.empty())
		{
			if (m_arrCachedBindShaderBuffers[shaderType] != &vecConstBuffers)
			{
				GetD3D11DeviceContext()->VSSetConstantBuffers(0, vecConstBuffers.size(), &vecConstBuffers[0]);
				m_arrCachedBindShaderBuffers[shaderType] = &vecConstBuffers;
			}

			//if (!m_vecD3D11SRV.empty())
			//	pContext->VSSetShaderResources(0, m_vecD3D11SRV.size(), &m_vecD3D11SRV[0]);
			//if (!m_vecSamplerState.empty())
			//	pContext->VSSetSamplers(0, m_vecSamplerState.size(), &m_vecSamplerState[0]);
			break;
		}
		break;
	}
	case HrShader::ST_PIXEL_SHADER:
	{
		GetD3D11DeviceContext()->PSSetShader(pD3D11Shader->RetriveD3D11PixelShader().get(), nullptr, 0);
		const std::vector<ID3D11Buffer*>& vecConstBuffers = pD3D11Shader->GetConstBuffers();
		if (!vecConstBuffers.empty())
		{
			if (m_arrCachedBindShaderBuffers[shaderType] != &vecConstBuffers)
			{
				GetD3D11DeviceContext()->PSSetConstantBuffers(0, vecConstBuffers.size(), &vecConstBuffers[0]);
				m_arrCachedBindShaderBuffers[shaderType] = &vecConstBuffers;
			}
		}
		//if (!m_vecD3D11SRV.empty())
		//	pD3D11ImmediateContext->PSSetShaderResources(0, m_vecD3D11SRV.size(), &m_vecD3D11SRV[0]);
		//if (!m_vecSamplerState.empty())
		//	pD3D11ImmediateContext->PSSetSamplers(0, m_vecSamplerState.size(), &m_vecSamplerState[0]);
		break;
	}
	default:
		break;
	}
}

void HrD3D11Render::Render(const HrRenderTechniquePtr& pRenderTechnique, const HrRenderLayoutPtr& pRenderLayout)
{
	//1.IASetVertexBuffers
	//2.Draw & DrawIndexed
	HrD3D11RenderLayoutPtr pD3D11RenderLayout = HrCheckPointerCast<HrD3D11RenderLayout>(pRenderLayout);
	unsigned int stride = pD3D11RenderLayout->GetVertexSize();
	unsigned int offset = 0;

	//todo renderLayout
	HrD3D11ShaderPtr pVertexShader = HrCheckPointerCast<HrD3D11Shader>(pRenderTechnique->GetRenderPass(0)->GetShader(HrShader::ST_VERTEX_SHADER));
	const ID3D11InputLayoutPtr& pInputLayout = pD3D11RenderLayout->GetInputLayout(pVertexShader);
	GetD3D11DeviceContext()->IASetInputLayout(pInputLayout.get());
	
	ID3D11Buffer* pVertexBuffer = pD3D11RenderLayout->GetVertexBuffer().get();
	GetD3D11DeviceContext()->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	GetD3D11DeviceContext()->IASetPrimitiveTopology(HrD3D11Mapping::GetTopologyType(pD3D11RenderLayout->GetTopologyType()));

	if (pD3D11RenderLayout->UseIndices())
	{
		const ID3D11BufferPtr& pIndexBuffer = pD3D11RenderLayout->GetIndexBuffer();
		GetD3D11DeviceContext()->IASetIndexBuffer(pIndexBuffer.get(), HrD3D11Mapping::GetIndexBufferFormat(pD3D11RenderLayout->GetIndexBufferType()), 0);
	}

	const uint32 nPassNum = pRenderTechnique->GetRenderPassNum();
	if (pD3D11RenderLayout->UseIndices())
	{
		uint32 nNumIndices = pD3D11RenderLayout->GetIndicesNum();
		for (uint32 i = 0; i < nPassNum; ++i)
		{
			pRenderTechnique->GetRenderPass(i)->BindPass(shared_from_this());
			GetD3D11DeviceContext()->DrawIndexed(nNumIndices, 0, 0);
			pRenderTechnique->GetRenderPass(i)->UnBindPass(shared_from_this());
		}
	}
	else
	{
		uint32 nNumVertices = pD3D11RenderLayout->GetVerticesNum();
		for (uint32 i = 0; i < nPassNum; ++i)
		{
			pRenderTechnique->GetRenderPass(i)->BindPass(shared_from_this());
			GetD3D11DeviceContext()->Draw(nNumVertices, 0);
			pRenderTechnique->GetRenderPass(i)->UnBindPass(shared_from_this());
		}
	}
}

void HrD3D11Render::SwapChain()
{

}

const ID3D11DevicePtr& HrD3D11Render::GetD3D11Device()
{
	return HrD3D11Device::Instance()->GetD3DDevice();
}

const ID3D11DeviceContextPtr& HrD3D11Render::GetD3D11DeviceContext()
{
	return HrD3D11Device::Instance()->GetD3DDeviceContext();
}
