#include "HrD3D11Render.h"
#include "HrD3D11Shader.h"
#include "HrD3D11RenderTarget.h"
#include "HrD3D11RenderLayout.h"
#include "HrD3D11DepthStencil.h"
#include "HrD3D11Mapping.h"
#include "HrD3D11FrameBuffer.h"
#include "HrD3D11RasterizerState.h"
#include "HrD3D11BlendState.h"
#include "HrD3D11DepthStencilState.h"
#include "HrCore/Include/Render/HrRenderable.h"
#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrViewPort.h"
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
	m_pCurFrameBuffer->OnBind(shared_from_this());
}

const HrRenderFramePtr& HrD3D11Render::GetBindFrameBuffer()
{
	return m_pCurFrameBuffer;
}

void HrD3D11Render::SetRenderTarget(const HrRenderTargetPtr& pRenderTarget, const HrDepthStencilPtr& pDepthStencil)
{
	ID3D11RenderTargetView* pD3DRenderTargetView[1] = {0};
	ID3D11DepthStencilView* pD3DDepthStencilView = nullptr;
	if (pRenderTarget)
	{
		pD3DRenderTargetView[0] = HrCheckPointerCast<HrD3D11RenderTarget>(pRenderTarget)->GetRenderTargetView().get();
	}
	pD3DDepthStencilView = HrCheckPointerCast<HrD3D11DepthStencil>(pDepthStencil)->GetDepthStencilView().get();
	
	GetD3D11DeviceContext()->OMSetRenderTargets(1, pD3DRenderTargetView, pD3DDepthStencilView);
}

void HrD3D11Render::SetViewPort(const HrViewPortPtr& pViewPort)
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

void HrD3D11Render::BindRasterizerState(const HrRasterizerStatePtr& pRasterizerState)
{
	if (m_pCachedRasterizerState != pRasterizerState)
	{
		m_pCachedRasterizerState = pRasterizerState;

		HrD3D11RasterizerStatePtr pD3DRasterizerState = HrCheckPointerCast<HrD3D11RasterizerState>(pRasterizerState);
		GetD3D11DeviceContext()->RSSetState(pD3DRasterizerState->RetriveD3D11RasterizerState().get());
	}
}

void HrD3D11Render::BindBlendState(const HrBlendStatePtr& pBlendState)
{
	if (m_pCachedBindBlendState != pBlendState)
	{
		m_pCachedBindBlendState = pBlendState;

		HrD3D11BlendStatePtr pD3D11BlendState = HrCheckPointerCast<HrD3D11BlendState>(pBlendState);
		GetD3D11DeviceContext()->OMSetBlendState(pD3D11BlendState->RetriveD3D11BlendState().get(), &(pD3D11BlendState->GetBlendFactor().r()), pD3D11BlendState->GetSampleMask());
	}
}

void HrD3D11Render::BindDepthStencilState(const HrDepthStencilStatePtr& pDepthStencilState)
{
	if (m_pCachedDepthStencilState != pDepthStencilState)
	{
		m_pCachedDepthStencilState = pDepthStencilState;

		HrD3D11DepthStencilStatePtr pD3D11DepthStencilState = HrCheckPointerCast<HrD3D11DepthStencilState>(pDepthStencilState);
		GetD3D11DeviceContext()->OMSetDepthStencilState(pD3D11DepthStencilState->RetriveD3D11DepthStencil().get(), pD3D11DepthStencilState->GetStencilRef());
	}
}

void HrD3D11Render::BindShader(const HrShaderPtr& pShader)
{
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
		const std::vector<ID3D11ShaderResourceView*>& vecSRV = pD3D11Shader->GetSRVs();
		if (!vecSRV.empty())
			GetD3D11DeviceContext()->PSSetShaderResources(0, vecSRV.size(), &vecSRV[0]);
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
	//IASetVertexBuffers
	HrD3D11RenderLayoutPtr pD3D11RenderLayout = HrCheckPointerCast<HrD3D11RenderLayout>(pRenderLayout);
	pD3D11RenderLayout->Active();

	HrD3D11ShaderPtr pVertexShader = HrCheckPointerCast<HrD3D11Shader>(pRenderTechnique->GetRenderPass(0)->GetShader(HrShader::ST_VERTEX_SHADER));
	const ID3D11InputLayoutPtr& pInputLayout = pD3D11RenderLayout->GetInputLayout(pVertexShader);
	GetD3D11DeviceContext()->IASetInputLayout(pInputLayout.get());
	
	uint32 nVertexStreams = pD3D11RenderLayout->GetVertexStreamSize();
	const std::vector<ID3D11Buffer*>& vecD3DVertexBuffers = pD3D11RenderLayout->GetD3DVertexBuffers();
	const std::vector<UINT>& vecStrides = pD3D11RenderLayout->GetStrides();
	const std::vector<UINT>& vecOffsets = pD3D11RenderLayout->GetOffsets();

	GetD3D11DeviceContext()->IASetVertexBuffers(0, nVertexStreams, &vecD3DVertexBuffers[0], &vecStrides[0], &vecOffsets[0]);
	GetD3D11DeviceContext()->IASetPrimitiveTopology(HrD3D11Mapping::GetTopologyType(pD3D11RenderLayout->GetTopologyType()));

	uint32 nInstanceCount = pRenderLayout->GetInstanceNum();
	
	if (pD3D11RenderLayout->UseIndices())
	{
		GetD3D11DeviceContext()->IASetIndexBuffer(pD3D11RenderLayout->GetD3DIndexBuffer(), HrD3D11Mapping::GetIndexBufferFormat(pD3D11RenderLayout->GetIndexBufferType()), 0);
	}

	const uint32 nPassNum = pRenderTechnique->GetRenderPassNum();
	if (pD3D11RenderLayout->UseIndices())
	{
		uint32 nNumIndices = pD3D11RenderLayout->GetIndicesNum();
		for (uint32 i = 0; i < nPassNum; ++i)
		{
			pRenderTechnique->GetRenderPass(i)->BindPass(shared_from_this());
			GetD3D11DeviceContext()->DrawIndexedInstanced(nNumIndices, nInstanceCount, 0, 0, 0);
			pRenderTechnique->GetRenderPass(i)->UnBindPass(shared_from_this());
		}
	}
	else
	{
		uint32 nNumVertices = pD3D11RenderLayout->GetVerticesNum();
		for (uint32 i = 0; i < nPassNum; ++i)
		{
			pRenderTechnique->GetRenderPass(i)->BindPass(shared_from_this());
			GetD3D11DeviceContext()->DrawInstanced(nNumVertices, nInstanceCount, 0, 0);
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
