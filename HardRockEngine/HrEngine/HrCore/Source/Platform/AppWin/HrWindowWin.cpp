#include "Platform/AppWin/HrWindowWin.h"
#include "Platform/AppWin/HrWindowsEventUtilities.h"
#include "Config/HrContextConfig.h"

using namespace Hr;

HrWindowWin::HrWindowWin(uint32 nWidth, uint32 nHeight)
{
	m_hWnd = nullptr;
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	CreateAppWidnow();
}

HrWindowWin::~HrWindowWin()
{
}

bool HrWindowWin::CreateAppWidnow()
{
	HINSTANCE hInst = NULL;
	static const TCHAR staticVar;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, &staticVar, &hInst);

	WNDCLASS wc;
	memset(&wc, 0, sizeof(wc));
	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = &HrWindowsEventUtilities::WinProc;
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

void HrWindowWin::UpdateMsg()
{
	HrWindowsEventUtilities::MessagePump();
}

void HrWindowWin::Destroy()
{
	::DestroyWindow(m_hWnd);
}

HWND HrWindowWin::GetHWnd()
{
	return m_hWnd;
}

uint32 HrWindowWin::GetWidth()
{
	return m_nWidth;
}

uint32 HrWindowWin::GetHeight()
{
	return m_nHeight;
}

