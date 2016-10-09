#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderWindow.h"
#include "HrCore/Include/HrLog.h"

using namespace Hr;

HrD3D11RenderWindow::HrD3D11RenderWindow()
{
	m_nWidth = m_nHeight = 0;

	m_hWnd = NULL;
	m_pSwapChain = nullptr;
	m_pRenderTargetView = nullptr;
	m_pDepthStencilView = nullptr;
}

bool HrD3D11RenderWindow::CreateRenderWindow(uint32 nWidth, uint32 nHeight, WNDPROC lpfnProc)
{
	CreateD3D11Window(nWidth, nHeight, lpfnProc);
	
	CreateSwapChain();
	
	CreateD3DView();

	HrD3D11Device::Instance()->GetImmediateContext()->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	return true;
}

bool HrD3D11RenderWindow::CreateD3D11Window(uint32 nWidth, uint32 nHeight, WNDPROC lpfnProc)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	HINSTANCE hInst = NULL;
	static const TCHAR staticVar;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, &staticVar, &hInst);

	WNDCLASS wc;
	memset(&wc, 0, sizeof(wc));
	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = lpfnProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _T("HrD3D11WindowClass");

	if (!RegisterClass(&wc))
	{
		DWORD dwError = GetLastError();
		if (dwError != ERROR_CLASS_ALREADY_EXISTS)
			OutputDebugString((_T("Cannot Register Window Class.")));
		return false;
	}
	m_hWnd = CreateWindow(_T("HrD3D11WindowClass"), _T("HrEngine"), WS_OVERLAPPEDWINDOW, 10, 10, nWidth, nHeight, NULL, NULL, hInst, 0);
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	SetFocus(m_hWnd);
	SetForegroundWindow(m_hWnd);

	return true;
}

bool HrD3D11RenderWindow::CreateSwapChain()
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
	swapChainDesc.OutputWindow = m_hWnd;
	swapChainDesc.Windowed = true;

	HRESULT hr = HrD3D11Device::Instance()->GetDXGIFactory()->CreateSwapChain(HrD3D11Device::Instance()->GetDevice(), &swapChainDesc, &m_pSwapChain);
	if (FAILED(hr))
	{
		HRERROR(_T("D3D11CreateSwapChain Error!"));
		return false;
	}

	return true;
}

bool HrD3D11RenderWindow::CreateD3DView()
{
	ID3D11Texture2D* pBackBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	HRESULT hr = HrD3D11Device::Instance()->GetDevice()->CreateRenderTargetView(pBackBuffer, 0, &m_pRenderTargetView);
	if (FAILED(hr))
	{
		HRERROR(_T("D3D11CreateD3DViews Error!"));
		return false;
	}
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

	hr = HrD3D11Device::Instance()->GetDevice()->CreateTexture2D(&depthStencilDesc, nullptr, &pDepthStencil);
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
	hr = HrD3D11Device::Instance()->GetDevice()->CreateDepthStencilView(pDepthStencil, &descDSV, &m_pDepthStencilView);
	if (FAILED(hr))
	{

		HRERROR(_T("D3D11CreateDepthStencilView Error!"));
		return false;
	}

	return true;
}

