#include "HrD3D11Utility.h"
#include "HrD3D11Device.h"

using namespace Hr;

HrD3D11Adapter::HrD3D11Adapter(unsigned int nAdapterNumer, IHRDXGIAdapter* pDXGIAdapter)
{
	m_nApdapterNumber = nAdapterNumer;
	m_pDXGIAdapter = pDXGIAdapter;
	if (m_pDXGIAdapter != nullptr)
	{
		m_pDXGIAdapter->AddRef();
		m_pDXGIAdapter->GetDesc1(&m_AdapterIdentifier);
	}
}

HrD3D11Adapter::~HrD3D11Adapter()
{
	SAFE_RELEASE(m_pDXGIAdapter);
}

std::string Hr::HrD3D11Adapter::GetDriverDescription() const
{
	size_t size = wcslen(m_AdapterIdentifier.Description);
	char * str = new char[size + 1];

	wcstombs(str, m_AdapterIdentifier.Description, size);
	str[size] = '\0';
	std::string driverDescription = str;
	delete[] str;
	HrStringUtil::Trim(driverDescription);

	return  driverDescription;
}

/////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////

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
	bool bRt = CreateRenderWindow(nWidth, nHeight, lpfnProc);
	HRASSERT(bRt, "HrD3D11Utility Init : CreateRenderWindow Error!");
	//创建DXGIFactory
	bRt = CreateDXGIFactory();
	HRASSERT(bRt, "HrD3D11Utility Init : CreateDXGIFactory Error!");
	//Enumerater Adapter
	bRt = EnumerateAdapter();
	HRASSERT(bRt, "HrD3D11Utility Init : EnumerateAdapter Error!");
	//创建Device
	bRt = CreateDXDevice();
	HRASSERT(bRt, "HrD3D11Utility Init : CreateDXDevice Error!");

	return true;
}

bool HrD3D11Utility::CreateRenderWindow(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc)
{
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

bool HrD3D11Utility::CreateDXGIFactory()
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

bool HrD3D11Utility::CreateDXDevice(HrD3D11Adapter* pD3DAdapter)
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
	UINT nFeatureLevels = pLastFL - pFirstFL + 1;

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
		HRERROR("D3D11CreateDevice Error!");
		return false;
	}

	return true;
}

bool HrD3D11Utility::EnumerateAdapter()
{
	if (HrD3D11Device::GetInstance()->GetDXGIFactory() == nullptr)
	{
		HRASSERT( false, "EnumerateAdapter Error! DXGIFactory is Empty!");
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
		m_vecAdapters.push_back(pDriver);
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
		HRESULT hr = HrD3D11Device::GetInstance()->GetDevice()->CheckMultisampleQualityLevels(fm, n, &nNumLevels);
		if (SUCCEEDED(hr) && nNumLevels > 0)
		{

		}
	}
}

HrD3D11Adapter* Hr::HrD3D11Utility::GetDefaultAdapter()
{
	if (m_vecAdapters.size() > 0)
	{
		return m_vecAdapters[0];
	}

	HRASSERT(false, "GetDefaultAdapter Error! the size of adapters is 0");
	return nullptr;
}

