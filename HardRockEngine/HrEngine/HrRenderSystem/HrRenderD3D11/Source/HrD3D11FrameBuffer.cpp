#include "HrD3D11FrameBuffer.h"
#include "HrD3D11RenderTarget.h"
#include "HrD3D11Render.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrCore/Include/Kernel/HrRenderCoreComponent.h"
#include "HrCore/Include/Render/HrRenderSystem.h"
#include <DirectXMath.h>

using namespace Hr;
using namespace DirectX;

HrD3D11FrameBuffer::HrD3D11FrameBuffer()
{

}

HrD3D11FrameBuffer::~HrD3D11FrameBuffer()
{
		
}

void HrD3D11FrameBuffer::AttachRenderTarget(HrRenderTargetPtr& pRenderTarget)
{
	HrRenderFrame::AttachRenderTarget(pRenderTarget);

	m_pD3D11RenderTarget = HrCheckPointerCast<HrD3D11RenderTarget>(m_pRenderTarget);
}

void HrD3D11FrameBuffer::DetachRenderTarget()
{

}

void HrD3D11FrameBuffer::OnBind()
{
	HrDirector::Instance()->GetRenderCoreComponent()->BindFrameBuffer(shared_from_this());
}

void HrD3D11FrameBuffer::OnUnBind()
{
}

const ID3D11RenderTargetViewPtr& HrD3D11FrameBuffer::D3D11RenderTargetView()
{
	if (!m_pRenderTargetView)
	{
		m_pRenderTargetView = HrCheckPointerCast<HrD3D11RenderTarget>(m_pRenderTarget)->GetRenderTargetView();
	}

	return m_pRenderTargetView;
}

const ID3D11DepthStencilViewPtr& HrD3D11FrameBuffer::D3D11DepthStencilView()
{
	if (!m_pDepthStencilView)
	{
		m_pDepthStencilView = HrCheckPointerCast<HrD3D11RenderTarget>(m_pRenderTarget)->GetDepthStencilView();
	}

	return m_pDepthStencilView;
}

void HrD3D11FrameBuffer::ClearTarget()
{
	XMVECTORF32 Blue = { m_clearColor.r(), m_clearColor.g(), m_clearColor.b(), m_clearColor.a() };

	HrD3D11Device::Instance()->GetD3DDeviceContext()->ClearRenderTargetView(D3D11RenderTargetView().get(), reinterpret_cast<const float*>(&Blue));
}

void HrD3D11FrameBuffer::ClearDepthStencil()
{
	HrD3D11Device::Instance()->GetD3DDeviceContext()->ClearDepthStencilView(D3D11DepthStencilView().get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, m_clearDepth, m_clearStencil);
}

void HrD3D11FrameBuffer::SwapChain()
{
	HrCheckPointerCast<HrD3D11RenderTarget>(m_pRenderTarget)->PresentSwapChain();
}

