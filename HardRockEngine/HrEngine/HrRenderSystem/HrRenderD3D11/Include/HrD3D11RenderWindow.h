#ifndef _HR_D3D11RENDERWINDOW_H_
#define _HR_D3D11RENDERWINDOW_H_

#include "HrCore/Include/Render/HrRenderTarget.h"
#include "HrD3D11Device.h"

namespace Hr
{
	class HrD3D11RenderWindow : public HrRenderTarget
	{
	public:
		HrD3D11RenderWindow();

		virtual bool CreateRenderWindow(uint32 nWidth, uint32 nHeight) override;

		const IDXGISwapChainPtr& GetSwapChain() const;
		const IDXGISwapChain1Ptr& GetSwapChain1() const;

		ID3D11RenderTargetView* GetRenderTargetView()
		{
			return m_pRenderTargetView;
		}
		ID3D11DepthStencilView* GetDepthStencilView()
		{
			return m_pDepthStencilView;
		}

		uint32 GetWidth()
		{
			return m_nWidth;
		}

		uint32 GetHeight()
		{
			return m_nHeight;
		}

		void PresentSwapChain() const;
	private:
		bool CreateSwapChain();
		bool CreateD3DView();

	private:
		HWND m_hWnd;
		
		uint32 m_nWidth;
		uint32 m_nHeight;

		IDXGISwapChainPtr m_pSwapChain;
		IDXGISwapChain1Ptr m_pSwapChain1;

		ID3D11RenderTargetView* m_pRenderTargetView;
		ID3D11DepthStencilView* m_pDepthStencilView;
	
	};
}

#endif







