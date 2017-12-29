#ifndef _HR_D3D11FRAMEBUFFER_H_
#define _HR_D3D11FRAMEBUFFER_H_

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/HrRenderFrame.h"

namespace Hr
{
	class HrD3D11FrameBuffer : public HrRenderFrame, public std::enable_shared_from_this<HrD3D11FrameBuffer>
	{
	public:
		HrD3D11FrameBuffer();
		~HrD3D11FrameBuffer();

		const ID3D11RenderTargetViewPtr& D3D11RenderTargetView();
		const ID3D11DepthStencilViewPtr& D3D11DepthStencilView();

		virtual void AttachRenderTarget(HrRenderTargetPtr& pRenderTarget) override;
		virtual void DetachRenderTarget() override;

		virtual void OnBind() override;
		virtual void OnUnBind() override;

		virtual void ClearTarget() override;
		virtual void ClearDepthStencil() override;

		virtual void SwapChain() override;
	protected:
		HrD3D11RenderTargetPtr m_pD3D11RenderTarget;

		ID3D11RenderTargetViewPtr m_pRenderTargetView;
		ID3D11DepthStencilViewPtr m_pDepthStencilView;

	};
}


#endif
