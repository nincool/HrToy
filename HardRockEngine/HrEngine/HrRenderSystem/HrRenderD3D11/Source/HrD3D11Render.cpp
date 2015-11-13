#include "HrD3D11Render.h"
#include "HrD3D11DriverList.h"
#include "HrD3D11Driver.h"
#include "HrD3D11Device.h"

using namespace Hr;

HrD3D11Render* HrD3D11Render::m_s_pInstance = nullptr;

HrD3D11Render::HrD3D11Render()
{
	m_hWnd = nullptr;
	m_pDXGIFactory = nullptr;
	m_pDriverList = nullptr;

	m_pD3D11Device = HNEW(HrD3D11Device);
}

HrD3D11Render::~HrD3D11Render()
{
	SAFE_DELETE(m_pDriverList);
	SAFE_DELETE(m_pD3D11Device);
}

#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
bool HrD3D11Render::Create(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc)
{
	if (!CreateRenderWindow(nWidth, nHeight, lpfnProc))
	{
		return false;
	}

	if (!CreateD3D11Device())
	{
		return false;
	}


	return true;
}
#else
bool HrD3D11Render::Create(unsigned int nWidth, unsigned int nHeight)
{
}
#endif

void HrD3D11Render::Destroy()
{

}

bool HrD3D11Render::CreateRenderWindow(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc)
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

bool HrD3D11Render::CreateD3D11Device()
{
	m_pDXGIFactory = nullptr;
	HRESULT hr = CreateDXGIFactory1(__uuidof(IHRDXGIFactory), (void**)&m_pDXGIFactory);
	if (FAILED(hr))
	{
		return false;
	}
	m_pDriverList = HNEW1(HrD3D11DriverList, m_pDXGIFactory);
	HrD3D11Driver* pDefaultDriver = m_pDriverList->GetDefaultDriver();
	if (pDefaultDriver == nullptr)
	{
		return false;
	}

	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;

	UINT deviceFlags = 0;
	deviceFlags != D3D11_CREATE_DEVICE_DEBUG;
	
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

	IHRD3D11Device* pD3DDevice;
	D3D11CreateDevice(pDefaultDriver->GetDeviceAdapter()
		, driverType
		, NULL
		, deviceFlags
		, requestedLevels
		, sizeof(requestedLevels) / sizeof(requestedLevels[0])
		, D3D11_SDK_VERSION
		, &pD3DDevice
		, NULL
		, 0);

	m_pD3D11Device->SetDevice(pD3DDevice);

	return true;
}
