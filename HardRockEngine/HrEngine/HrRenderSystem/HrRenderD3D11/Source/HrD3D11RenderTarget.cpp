#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderTarget.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include "HrCore/Include/Config/HrContextConfig.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrCore/Include/Platform/AppWin32/HrWindowWin.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrD3D11RenderTarget::HrD3D11RenderTarget()
{
	m_nWidth = m_nHeight = 0;

	m_hWnd = NULL;
	m_pSwapChain = nullptr;
	m_pSwapChain1 = nullptr;
	m_pRenderTargetView = nullptr;
	m_pDepthStencilView = nullptr;
}

const ID3D11RenderTargetViewPtr& HrD3D11RenderTarget::GetRenderTargetView()
{
	return m_pRenderTargetView;
}

const ID3D11DepthStencilViewPtr& HrD3D11RenderTarget::GetDepthStencilView()
{
	return m_pDepthStencilView;
}

bool HrD3D11RenderTarget::CreateRenderTargetView(uint32 nWidth, uint32 nHeight)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	CreateSwapChain();
	CreateD3DView();

	ID3D11RenderTargetView* pRenderTargetView = m_pRenderTargetView.get();
	HrD3D11Device::Instance()->GetD3DDeviceContext()->OMSetRenderTargets(1, &pRenderTargetView, m_pDepthStencilView.get());

	return true;
}

bool HrD3D11RenderTarget::CreateSwapChain()
{
	if (HrD3D11Device::Instance()->GetDXGISubVersion() >= 2)
	{
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc1;
		ZeroMemory(&swapChainDesc1, sizeof(swapChainDesc1));
		swapChainDesc1.Width = m_nWidth;
		swapChainDesc1.Height = m_nHeight;
		swapChainDesc1.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		bool bStereo = HrD3D11Device::Instance()->GetDXGIFactory2()->IsWindowedStereoEnabled();
		swapChainDesc1.Stereo = bStereo;

		swapChainDesc1.SampleDesc.Count = 1;
		swapChainDesc1.SampleDesc.Quality = 0;

		swapChainDesc1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc1.BufferCount = 1;

		swapChainDesc1.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc1.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc1.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swapChainDesc1.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainFullScreenDesc;
		ZeroMemory(&swapChainFullScreenDesc, sizeof(swapChainFullScreenDesc));
		swapChainFullScreenDesc.RefreshRate.Numerator = 60;
		swapChainFullScreenDesc.RefreshRate.Denominator = 1;
		swapChainFullScreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainFullScreenDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainFullScreenDesc.Windowed = true;

		HrWindowWinPtr pWindow = HrCheckPointerCast<HrWindowWin>(HrDirector::Instance()->GetWindow());
		IDXGISwapChain1* pSwapChain = nullptr;
		HRESULT hr = HrD3D11Device::Instance()->GetDXGIFactory2()->CreateSwapChainForHwnd(HrD3D11Device::Instance()->GetD3DDevice().get(), pWindow->GetHWnd()
			, &swapChainDesc1
			, &swapChainFullScreenDesc
			, nullptr
			, &pSwapChain);

		if (FAILED(hr))
		{
			HRERROR(_T("D3D11CreateSwapChain Error!"));
			return false;
		}
		m_pSwapChain1 = MakeComPtr(pSwapChain);

		return true;
	}
	else
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferDesc.Width = m_nWidth;
		swapChainDesc.BufferDesc.Height = m_nHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;

		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		swapChainDesc.BufferCount = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		HrWindowWinPtr pWindow = HrCheckPointerCast<HrWindowWin>(HrDirector::Instance()->GetWindow());
		swapChainDesc.OutputWindow = pWindow->GetHWnd();
		swapChainDesc.Windowed = true;

		//todo
		IDXGISwapChain* pSwapChain = nullptr;
		HRESULT hr = HrD3D11Device::Instance()->GetDXGIFactory1()->CreateSwapChain(HrD3D11Device::Instance()->GetD3DDevice().get(), &swapChainDesc, &pSwapChain);
		if (FAILED(hr))
		{
			HRERROR(_T("D3D11CreateSwapChain Error!"));
			return false;
		}
		m_pSwapChain = MakeComPtr(pSwapChain);

		return true;
	}
}

bool HrD3D11RenderTarget::CreateD3DView()
{
	ID3D11Texture2D* pBackBuffer = nullptr;
	if (m_pSwapChain1)
	{
		m_pSwapChain1->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	}
	else if (m_pSwapChain)
	{
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	}
	ID3D11RenderTargetView* pRenderTargetView = nullptr;
	HRESULT hr = HrD3D11Device::Instance()->GetD3DDevice()->CreateRenderTargetView(pBackBuffer, 0, &pRenderTargetView);
	if (FAILED(hr))
	{
		HRERROR(_T("D3D11CreateD3DViews Error!"));
		return false;
	}
	m_pRenderTargetView = MakeComPtr(pRenderTargetView);
	SAFE_RELEASE(pBackBuffer);

	ID3D11Texture2D* pDepthStencil = nullptr;
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthStencilDesc.Width = m_nWidth;
	depthStencilDesc.Height = m_nHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	hr = HrD3D11Device::Instance()->GetD3DDevice()->CreateTexture2D(&depthStencilDesc, nullptr, &pDepthStencil);
	if (FAILED(hr))
	{
		HRERROR(_T("D3D11CreateDepthStencil Error!"));
		return false;
	}

	//Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	descDSV.Format = depthStencilDesc.Format;
	if (depthStencilDesc.SampleDesc.Count > 1)
	{
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	}
	else
	{
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	}
	descDSV.Texture2D.MipSlice = 0;

	ID3D11DepthStencilView* pDepthStencilView = nullptr;
	hr = HrD3D11Device::Instance()->GetD3DDevice()->CreateDepthStencilView(pDepthStencil, &descDSV, &pDepthStencilView);
	if (FAILED(hr))
	{
		HRERROR(_T("D3D11CreateDepthStencilView Error!"));
		return false;
	}
	m_pDepthStencilView = MakeComPtr(pDepthStencilView);
	return true;
}

const IDXGISwapChainPtr& HrD3D11RenderTarget::GetSwapChain() const
{
	return m_pSwapChain;
}

const IDXGISwapChain1Ptr& HrD3D11RenderTarget::GetSwapChain1() const
{
	return m_pSwapChain1;
}

void HrD3D11RenderTarget::PresentSwapChain() const
{
	if (m_pSwapChain1)
	{
		m_pSwapChain1->Present(0, 0);
	}
	else if (m_pSwapChain)
	{
		m_pSwapChain->Present(0, 0);
	}
}


