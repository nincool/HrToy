#ifndef _HR_D3D11RENDERWINDOW_H_
#define _HR_D3D11RENDERWINDOW_H_

#include "HrRenderSystem/HrRenderCommon/IRenderWindow.h"
#include "HrD3D11Device.h"

namespace Hr
{
	class HrD3D11RenderWindow : public IRenderWindow
	{
	public:
		HrD3D11RenderWindow();

		virtual bool CreateRenderWindow(uint32 nWidth, uint32 nHeight, WNDPROC lpfnProc) override;
		virtual bool CreateSwapChain() override;
		virtual bool CreateD3DView() override;

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
		const D3D11_VIEWPORT& GetD3D11ViewPort()
		{
			return m_vp;
		}

	private:
		bool CreateD3D11Window(uint32 nWidth, uint32 nHeight, WNDPROC lpfnProc);
	private:
		HWND m_hWnd;
		HR_SYNTHESIZE_READONLY(uint32, m_nWidth, Width);
		HR_SYNTHESIZE_READONLY(uint32, m_nHeight, Height);

		IDXGISwapChain* m_pSwapChain;
		ID3D11RenderTargetView* m_pRenderTargetView;
		ID3D11DepthStencilView* m_pDepthStencilView;
		D3D11_VIEWPORT m_vp;
	};
}

#endif







