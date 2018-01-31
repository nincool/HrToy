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

		const ID3D11RenderTargetViewPtr& D3D11RenderTargetView(EnumRenderTargetLayer renderTargetLayer);
		const ID3D11DepthStencilViewPtr& D3D11DepthStencilView();

		virtual void AttachRenderTarget(EnumRenderTargetLayer attachLayer, HrRenderTargetPtr& pRenderTarget) override;
		virtual void DetachRenderTarget(EnumRenderTargetLayer attachLayer) override;

		virtual void OnBind() override;
		virtual void OnUnBind() override;

		virtual void ClearTarget() override;
		virtual void ClearDepthStencil() override;

		virtual void Present() override;
	};

	class HrD3D11ScreenFrameBuffer : public HrD3D11FrameBuffer
	{
	public:
		HrD3D11ScreenFrameBuffer(uint32 nWidth, uint32 nHeight);
		~HrD3D11ScreenFrameBuffer();

		virtual void OnBind() override;
		virtual void OnUnBind() override;

		virtual void ClearTarget() override;
		virtual void ClearDepthStencil() override;

		virtual void Present() override;

		bool CreateSwapChain();

	private:
		void CreateRenderTargetView();
		void CreateDepthStencilView();
	protected:
		uint32 m_nWidth;
		uint32 m_nHeight;

		IDXGISwapChainPtr m_pSwapChain;
		IDXGISwapChain1Ptr m_pSwapChain1;

	};
}


#endif
