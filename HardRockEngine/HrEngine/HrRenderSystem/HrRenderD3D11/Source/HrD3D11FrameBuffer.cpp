#include "HrD3D11FrameBuffer.h"
#include "HrD3D11RenderTarget.h"
#include "HrD3D11Render.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrCore/Include/Kernel/HrRenderCoreComponent.h"

#include "HrCore/Include/Render/HrRenderSystem.h"


using namespace Hr;

HrD3D11FrameBuffer::HrD3D11FrameBuffer()
{
}

HrD3D11FrameBuffer::~HrD3D11FrameBuffer()
{
		
}

void HrD3D11FrameBuffer::ClearTarget()
{

}

void HrD3D11FrameBuffer::ClearDepthStencil()
{

}

void HrD3D11FrameBuffer::OnBind()
{
	HrDirector::Instance()->GetRenderCoreComponent()->GetRenderSystem()->GetRender()->SetCurrentFrameBuffer(shared_from_this());
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

