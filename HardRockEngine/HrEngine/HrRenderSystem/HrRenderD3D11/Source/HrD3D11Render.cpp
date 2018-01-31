#include "HrD3D11Render.h"
#include "HrD3D11Shader.h"
#include "HrD3D11RenderTarget.h"
#include "HrD3D11RenderLayout.h"
#include "HrD3D11Mapping.h"
#include "HrD3D11FrameBuffer.h"
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
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = 1280;
	vp.Height = 720;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	GetD3D11DeviceContext()->RSSetViewports(1, &vp);
}

void HrD3D11Render::ReleaseRenderEngine()
{
	HrD3D11Device::Instance()->Release();
}

bool HrD3D11Render::StartRender()
{
	return true;
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
