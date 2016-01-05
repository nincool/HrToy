#include "HrD3D11Utility.h"
#include "HrD3D11Device.h"

using namespace Hr;

HR_INSTANCE_DEF(HrD3D11Utility);

HrD3D11Utility::HrD3D11Utility()
{
	m_hWnd = nullptr;
}

HrD3D11Utility::~HrD3D11Utility()
{
}

bool Hr::HrD3D11Utility::Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc)
{
	//创建窗口
	bool bRt = CreateD3DRenderWindow(nWidth, nHeight, lpfnProc);
	HRASSERT(bRt, _T("HrD3D11Utility Init : CreateRenderWindow Error!"));
	//创建DXGIFactory
	bRt = CreateD3DDXGIFactory();
	HRASSERT(bRt, _T("HrD3D11Utility Init : CreateDXGIFactory Error!"));
	//创建Device
	bRt = CreateD3DDXDevice();
	HRASSERT(bRt, _T("HrD3D11Utility Init : CreateDXDevice Error!"));
	//Enumerater Adapter
	bRt = D3DEnumerate();
	HRASSERT(bRt, _T("HrD3D11Utility Init : EnumerateAdapter Error!"));
	//抗锯齿
	BuildMutisampleQualityList();
	
	bRt = CreateD3DSwapChain();
	HRASSERT(bRt, _T("HrD3D11Utility Init : CreateD3DSwapChain Error!"));
	bRt = CreateD3DViews();
	HRASSERT(bRt, _T("HrD3D11Utility Init : CreateD3DViews Error!"));

	return true;
}

bool HrD3D11Utility::CreateD3DRenderWindow(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc)
{
	HrD3D11Device::GetInstance()->SetWidth(nWidth);
	HrD3D11Device::GetInstance()->SetHeight(nHeight);

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

bool HrD3D11Utility::CreateD3DDXGIFactory()
{
	if (HrD3D11Device::GetInstance()->GetDXGIFactory() == nullptr)
	{
		IHRDXGIFactory* pDXGIFactory = nullptr;
		HRESULT hr = CreateDXGIFactory1(__uuidof(IHRDXGIFactory), (void**)&pDXGIFactory);
		if (FAILED(hr))
		{
			return false;
		}
		HrD3D11Device::GetInstance()->SetDXGIFactory(pDXGIFactory);
	}

	return true;
}

bool HrD3D11Utility::CreateD3DDXDevice(HrD3D11Adapter* pD3DAdapter)
{
	HrD3D11Adapter* pAdapter = pD3DAdapter;
	IHRDXGIAdapter* pDeviceAdapter = pAdapter == nullptr ? nullptr : pAdapter->GetDeviceAdapter();

	// determine feature levels
	D3D_FEATURE_LEVEL requestedLevels[] =
	{
#if defined(_WIN32_WINNT_WIN8) && _WIN32_WINNT >= _WIN32_WINNT_WIN8
		D3D_FEATURE_LEVEL_11_1,
#endif
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};
	D3D_FEATURE_LEVEL* pFirstFL = &requestedLevels[0];
	D3D_FEATURE_LEVEL* pLastFL = &requestedLevels[1];
	uint64 nFeatureLevels = pLastFL - pFirstFL + 1;

	D3D_DRIVER_TYPE driverType = pAdapter == nullptr ? D3D_DRIVER_TYPE_HARDWARE : D3D_DRIVER_TYPE_UNKNOWN;

	UINT deviceFlags = 0;
	//deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

	IHRD3D11Device* pD3DDevice;
	HRESULT hr = D3D11CreateDevice(pDeviceAdapter
		, driverType
		, NULL
		, deviceFlags
		, pFirstFL
		, nFeatureLevels
		, D3D11_SDK_VERSION
		, &pD3DDevice
		, NULL
		, 0);
	if (hr != S_OK)
	{
		HRERROR(_T("D3D11CreateDevice Error!"));
		return false;
	}

	HrD3D11Device::GetInstance()->SetDevice(pD3DDevice);

	return true;
}

bool Hr::HrD3D11Utility::D3DEnumerate()
{
	if (!D3D3EnumerateAdapter())
	{
		return false;
	}

	D3DEnumerateModeList();

	return true;
}

void Hr::HrD3D11Utility::D3DEnumerateModeList()
{
	HRESULT hr = S_OK;
	IDXGIOutput* pOutput = nullptr;
	for (int nOutput = 0;; ++nOutput)
	{
		hr = HrD3D11Device::GetInstance()->GetCurrentAdapter()->GetDeviceAdapter()->EnumOutputs(nOutput, &pOutput);
		if (DXGI_ERROR_NOT_FOUND == hr)
		{
			break;
		}
		else if (FAILED(hr))
		{
			break;
		}
		else
		{
			HrD3D11EnumOutputInfo* pEnumOutputInfo = new HrD3D11EnumOutputInfo();

			pEnumOutputInfo->m_pOutput = pOutput;
			pOutput->GetDesc(&(pEnumOutputInfo->desc));

			// Fast-path: Try to grab at least 512 modes.
			//			  This is to avoid calling GetDisplayModeList more times than necessary.
			//			  GetDisplayModeList is an expensive call.
			UINT NumModes = 512;
			DXGI_MODE_DESC* pDesc = new DXGI_MODE_DESC[NumModes];
			hr = pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
				DXGI_ENUM_MODES_SCALING,
				&NumModes,
				pDesc);
			if (DXGI_ERROR_NOT_FOUND == hr)
			{
				SAFE_DELETE_ARRAY(pDesc);
				NumModes = 0;
			}
			else if (hr == DXGI_ERROR_NOT_CURRENTLY_AVAILABLE)
			{
				NumModes = 1;
				pDesc[0].Width = pEnumOutputInfo->desc.DesktopCoordinates.right - pEnumOutputInfo->desc.DesktopCoordinates.left;
				pDesc[0].Height = pEnumOutputInfo->desc.DesktopCoordinates.bottom - pEnumOutputInfo->desc.DesktopCoordinates.top;
				pDesc[0].Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				pDesc[0].RefreshRate.Numerator = 60;
				pDesc[0].RefreshRate.Denominator = 1;
				pDesc[0].ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
				pDesc[0].Scaling = DXGI_MODE_SCALING_CENTERED;
				hr = S_OK;
			}
			else if (DXGI_ERROR_MORE_DATA == hr)
			{
				// Slow path.  There were more than 512 modes.
				SAFE_DELETE_ARRAY(pDesc);
				hr = pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
					DXGI_ENUM_MODES_SCALING,
					&NumModes,
					NULL);

				if (FAILED(hr))
				{
					NumModes = 0;
					break;
				}
				pDesc = new DXGI_MODE_DESC[NumModes];
				hr = pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
					DXGI_ENUM_MODES_SCALING,
					&NumModes,
					pDesc);
				if (FAILED(hr))
				{
					SAFE_DELETE_ARRAY(pDesc);
					NumModes = 0;
					break;
				}
			}
			if (SUCCEEDED(hr))
			{
				HrD3D11Device::GetInstance()->GetCurrentAdapter()->m_vecEnumOutputInfo.push_back(pEnumOutputInfo);
				for (UINT nNumIndex = 0; nNumIndex < NumModes; ++nNumIndex)
				{
					pEnumOutputInfo->m_vecPlayModeList.push_back(pDesc[nNumIndex]);
				}
			}
			else
			{
				SAFE_DELETE(pEnumOutputInfo);
			}
		}
	}
}

bool HrD3D11Utility::D3D3EnumerateAdapter()
{
	if (HrD3D11Device::GetInstance()->GetDXGIFactory() == nullptr)
	{
		HRASSERT(false, _T("EnumerateAdapter Error! DXGIFactory is Empty!"));
		return false;
	}
	for (uint32 nAdapter = 0;; ++nAdapter)
	{
		IHRDXGIAdapter* pDXGIAdapter = nullptr;
		HRESULT hr = HrD3D11Device::GetInstance()->GetDXGIFactory()->EnumAdapters1(nAdapter, &pDXGIAdapter);
		if (DXGI_ERROR_NOT_FOUND == hr)
		{
			hr = S_OK;
			break;
		}
		if (FAILED(hr))
		{
			SAFE_DELETE(pDXGIAdapter);
			return false;
		}

		HrD3D11Adapter* pDriver = new HrD3D11Adapter(nAdapter, pDXGIAdapter);
		HrD3D11Device::GetInstance()->m_vecAdapters.push_back(pDriver);
		SAFE_RELEASE(pDXGIAdapter);
	}

	return true;
}

void HrD3D11Utility::BuildMutisampleQualityList()
{
	UINT nNumLevels = 0;
	DXGI_FORMAT fm = DXGI_FORMAT_R8G8B8A8_UNORM;
	for (uint32 n = 0; n < D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; ++n)
	{
		IHRD3D11Device* pDevice = HrD3D11Device::GetInstance()->GetDevice();
		HRESULT hr = HrD3D11Device::GetInstance()->GetDevice()->CheckMultisampleQualityLevels(fm, n, &nNumLevels);
		if (SUCCEEDED(hr) && nNumLevels > 0)
		{
			HrD3D11Device::GetInstance()->m_vecMultiSampleCountList.push_back(n);
			HrD3D11Device::GetInstance()->m_vecMultiSampleQualityList.push_back(nNumLevels);
		}
	}
}

bool Hr::HrD3D11Utility::CreateD3DSwapChain()
{
	auto pHrD3D11Device = HrD3D11Device::GetInstance();
	pHrD3D11Device->m_swapChainDesc.BufferDesc.Width = pHrD3D11Device->GetWidth();
	pHrD3D11Device->m_swapChainDesc.BufferDesc.Height = pHrD3D11Device->GetHeight();
	pHrD3D11Device->m_swapChainDesc.BufferDesc.Format = pHrD3D11Device->GetFormat();

	pHrD3D11Device->m_swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	pHrD3D11Device->m_swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;

	pHrD3D11Device->m_swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	pHrD3D11Device->m_swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	pHrD3D11Device->m_swapChainDesc.SampleDesc.Count = 1;
	pHrD3D11Device->m_swapChainDesc.SampleDesc.Quality = 0;

	pHrD3D11Device->m_swapChainDesc.BufferCount = 1;
	pHrD3D11Device->m_swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	pHrD3D11Device->m_swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	pHrD3D11Device->m_swapChainDesc.OutputWindow = m_hWnd;
	pHrD3D11Device->m_swapChainDesc.Windowed = true;

	IHRDXGISwapChain* pDXSwapChain = nullptr;
	HRESULT hr = pHrD3D11Device->GetDXGIFactory()->CreateSwapChain(pHrD3D11Device->GetDevice(), &pHrD3D11Device->m_swapChainDesc, &pDXSwapChain);
	if (FAILED(hr))
	{
		HRERROR(_T("D3D11CreateSwapChain Error!"));
		return false;
	}
	pHrD3D11Device->SetSwapChain(pDXSwapChain);

	return true;
}

bool Hr::HrD3D11Utility::CreateD3DViews()
{
	ID3D11RenderTargetView* pRenderTargetView = nullptr;
	ID3D11Texture2D* pBackBuffer = nullptr;
	HrD3D11Device::GetInstance()->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	HRESULT hr = HrD3D11Device::GetInstance()->GetDevice()->CreateRenderTargetView(pBackBuffer, 0, &pRenderTargetView);
	if (FAILED(hr))
	{
		HRERROR(_T("D3D11CreateD3DViews Error!"));
		return false;
	}
	HrD3D11Device::GetInstance()->SetRenderTargetView(pRenderTargetView);
	SAFE_RELEASE(pBackBuffer);

	ID3D11Texture2D* pDepthStencil = nullptr;
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthStencilDesc.Width = HrD3D11Device::GetInstance()->GetWidth();
	depthStencilDesc.Height = HrD3D11Device::GetInstance()->GetHeight();
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	hr = HrD3D11Device::GetInstance()->GetDevice()->CreateTexture2D(&depthStencilDesc, nullptr, &pDepthStencil);
	if (FAILED(hr))
	{
		HRERROR(_T("D3D11CreateDepthStencil Error!"));
		return false;
	}
	HrD3D11Device::GetInstance()->SetDepthStencil(pDepthStencil);

	//Create the depth stencil view
	ID3D11DepthStencilView* pDepthStencilView = nullptr;
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
	hr = HrD3D11Device::GetInstance()->GetDevice()->CreateDepthStencilView(pDepthStencil, &descDSV, &pDepthStencilView);
	if (FAILED(hr))
	{

		HRERROR(_T("D3D11CreateDepthStencilView Error!"));
		return false;
	}
	HrD3D11Device::GetInstance()->SetDepthStencilView(pDepthStencilView);

	HrD3D11Device::GetInstance()->GetImmediateContext()->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);

	// Setup the viewport to match the backbuffer
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = static_cast<FLOAT>(depthStencilDesc.Width);
	vp.Height = static_cast<FLOAT>(depthStencilDesc.Height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	HrD3D11Device::GetInstance()->GetImmediateContext()->RSSetViewports(1, &vp);

	return true;
}



