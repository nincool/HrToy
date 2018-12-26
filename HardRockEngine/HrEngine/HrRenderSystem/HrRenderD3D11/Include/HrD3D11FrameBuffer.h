#ifndef _HR_D3D11FRAMEBUFFER_H_
#define _HR_D3D11FRAMEBUFFER_H_

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/HrRenderFrame.h"

namespace Hr
{
	class HrD3D11FrameBuffer : public HrRenderFrame, public std::enable_shared_from_this<HrD3D11FrameBuffer>
	{
	public:
		HrD3D11FrameBuffer(uint32 nWidth, uint32 nHeight);
		~HrD3D11FrameBuffer();

		const ID3D11RenderTargetViewPtr& D3D11RenderTargetView(EnumRenderTargetLayer renderTargetLayer);
		const ID3D11DepthStencilViewPtr& D3D11DepthStencilView();

		virtual void AttachRenderTarget(EnumRenderTargetLayer attachLayer, HrRenderTargetPtr& pRenderTarget) override;
		virtual void DetachRenderTarget(EnumRenderTargetLayer attachLayer) override;

		virtual void OnBind(const HrRenderPtr& pRender) override;
		virtual void OnUnBind() override;

		virtual void ClearTarget() override;
		virtual void ClearDepthStencil() override;

		virtual void Present() override;

	protected:

	};

	/////////////////////////////////////////////////////////////////

	class HrD3D11ScreenFrameBuffer : public HrD3D11FrameBuffer
	{
	public:
		HrD3D11ScreenFrameBuffer(uint32 nWidth, uint32 nHeight);
		~HrD3D11ScreenFrameBuffer();

		virtual void OnBind(const HrRenderPtr& pRender) override;
		virtual void OnUnBind() override;

		virtual void ClearTarget() override;
		virtual void ClearDepthStencil() override;

		virtual void Present() override;

		bool CreateSwapChain();

	private:
		void CreateRenderTargetView();
		void CreateDepthStencilView();
	protected:
		IDXGISwapChainPtr m_pSwapChain;
		IDXGISwapChain1Ptr m_pSwapChain1;

	};

	/////////////////////////////////////////////////////////////////

	class HrD3D11DepthStencilFrameBuffer : public HrD3D11FrameBuffer
	{
	public:
		HrD3D11DepthStencilFrameBuffer(uint32 nWidth, uint32 nHeight);
		~HrD3D11DepthStencilFrameBuffer();

		virtual void OnBind(const HrRenderPtr& pRender) override;
		virtual void OnUnBind() override;

		virtual void ClearTarget() override;
		virtual void ClearDepthStencil() override;
	protected:
		void CreateDepthStencilView();
		
		
	};

	//////////////////////////////////////////////////////////////////

	class HrD3D11DeferredFrameBuffer : public HrD3D11FrameBuffer
	{
	public:
		HrD3D11DeferredFrameBuffer(uint32 nWidth, uint32 nHeight, const HrDeferredGBufferDataPtr& pDeferredGBufferData);
		~HrD3D11DeferredFrameBuffer();

		virtual void OnBind(const HrRenderPtr& pRender) override;
		virtual void OnUnBind() override;

		virtual void ClearTarget() override;
		virtual void ClearDepthStencil() override;
	protected:
		void CreateGBuffers();
		void CreateDepthStencilView();
	private:
		//g_buffers
		HrD3D11Texture2DPtr m_pPositionSRV;
		HrD3D11Texture2DPtr m_pNormalSRV;
		HrD3D11Texture2DPtr m_pAlbedoSRV;

		HrDeferredGBufferDataPtr m_pGBufferData;
	};
}


#endif


