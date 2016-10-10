#include "Platform/AppWin32/HrWindowWin.h"
#include "Platform/AppWin32/HrWin32WindowEventUtilities.h"
#include "Config/HrContextConfig.h"

using namespace Hr;

HrWindowWin::HrWindowWin()
{
	m_hWnd = nullptr;
	m_nWidth = 600;
	m_nHeight = 400;

	CreateAppWidnow();
}

HrWindowWin::~HrWindowWin()
{
}

bool HrWindowWin::CreateAppWidnow()
{
	m_nWidth = HrContextConfig::Instance()->GetWindowWidth();
	m_nHeight = HrContextConfig::Instance()->GetWindowHeight();

	HINSTANCE hInst = NULL;
	static const TCHAR staticVar;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, &staticVar, &hInst);

	WNDCLASS wc;
	memset(&wc, 0, sizeof(wc));
	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = &HrWin32WindowEventUtilities::WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _T("HrD3DWindowClass");

	if (!RegisterClass(&wc))
	{
		DWORD dwError = GetLastError();
		if (dwError != ERROR_CLASS_ALREADY_EXISTS)
			OutputDebugString((_T("Cannot Register Window Class.")));
		return false;
	}
	m_hWnd = CreateWindow(_T("HrD3DWindowClass"), _T("HrEngine"), WS_OVERLAPPEDWINDOW, 10, 10, m_nWidth, m_nHeight, NULL, NULL, hInst, 0);

	ShowWindow(m_hWnd, SW_SHOWNORMAL);

	SetFocus(m_hWnd);

	SetForegroundWindow(m_hWnd);

	return true;
}

void HrWindowWin::Update()
{
	HrWin32WindowEventUtilities::MessagePump();
}

void HrWindowWin::Destroy()
{
	::DestroyWindow(m_hWnd);
}

