#ifndef _HR_D3D11RENDERWINDOW_H_
#define _HR_D3D11RENDERWINDOW_H_

#include "HrCore/Include/Render/HrRenderTarget.h"
#include "HrD3D11Device.h"

namespace Hr
{
	class HrD3D11RenderTarget : public HrRenderTarget
	{
	public:
		HrD3D11RenderTarget();

		virtual bool CreateRenderTarget(uint32 nWidth, uint32 nHeight) override;

		const IDXGISwapChainPtr& GetSwapChain() const;
		const IDXGISwapChain1Ptr& GetSwapChain1() const;

		const ID3D11RenderTargetViewPtr& GetRenderTargetView();
		const ID3D11DepthStencilViewPtr& GetDepthStencilView();

		void PresentSwapChain() const;
	private:
		bool CreateSwapChain();
		bool CreateRenderTargetView();
		bool CreateDepthStencilView();

	private:
		HWND m_hWnd;
		
		uint32 m_nWidth;
		uint32 m_nHeight;

		IDXGISwapChainPtr m_pSwapChain;
		IDXGISwapChain1Ptr m_pSwapChain1;

		ID3D11RenderTargetViewPtr m_pRenderTargetView;
		ID3D11DepthStencilViewPtr m_pDepthStencilView;
	
	};
}

#endif







