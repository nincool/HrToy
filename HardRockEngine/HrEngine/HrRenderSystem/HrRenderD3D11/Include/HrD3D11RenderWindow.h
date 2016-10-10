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

		IDXGISwapChain* GetSwapChain()
		{
			return m_pSwapChain;
		}
		ID3D11RenderTargetView* GetRenderTargetView()
		{
			return m_pRenderTargetView;
		}
		ID3D11DepthStencilView* GetDepthStencilView()
		{
			return m_pDepthStencilView;
		}

	private:
		bool CreateSwapChain();
		bool CreateD3DView();

	private:
		HWND m_hWnd;
		HR_SYNTHESIZE_READONLY(uint32, m_nWidth, Width);
		HR_SYNTHESIZE_READONLY(uint32, m_nHeight, Height);

		IDXGISwapChain* m_pSwapChain;
		ID3D11RenderTargetView* m_pRenderTargetView;
		ID3D11DepthStencilView* m_pDepthStencilView;
	
	};
}

#endif







