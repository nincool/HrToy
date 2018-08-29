#include "Platform/AppWin/HrWrapperWin.h"
#include "Platform/AppWin/HrWindowsEventUtilities.h"
#include "Config/HrContextConfig.h"

using namespace Hr;

LRESULT HrWrapperWin::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#pragma warning(push)
#pragma warning(disable: 4312) // LONG_PTR to Window*, could cast to a greater size
	HrWrapperWin* win = reinterpret_cast<HrWrapperWin*>(::GetWindowLongPtrW(hWnd, GWLP_USERDATA));
#pragma warning(pop)

	if (win != nullptr)
	{
		return win->MsgProc(hWnd, uMsg, wParam, lParam);
	}
	else
	{
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

HrWrapperWin::HrWrapperWin(HWND hWnd)
{
	m_hWnd = hWnd;

	CreateAppWidnow();
}

HrWrapperWin::~HrWrapperWin()
{
}

bool HrWrapperWin::CreateAppWidnow()
{
	//default_wnd_proc_ = reinterpret_cast<WNDPROC>(::GetWindowLongPtrW(m_hWnd, GWLP_WNDPROC));
	//::SetWindowLongPtrW(m_hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc));

	RECT rc;
	::GetClientRect(m_hWnd, &rc);
	m_nLeft = rc.left;
	m_nTop = rc.top;
	m_nWidth = rc.right - rc.left;
	m_nHeight = rc.bottom - rc.top;

#pragma warning(push)
#pragma warning(disable: 4244) // Pointer to LONG_PTR, possible loss of data
	::SetWindowLongPtrW(m_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
#pragma warning(pop)


	::UpdateWindow(m_hWnd);

	return true;
}

void HrWrapperWin::UpdateMsg()
{
	HrWindowsEventUtilities::MessagePump();
}

void HrWrapperWin::Destroy()
{
	::DestroyWindow(m_hWnd);
}

HWND HrWrapperWin::GetHWnd()
{
	return m_hWnd;
}

uint32 HrWrapperWin::GetWidth()
{
	return m_nWidth;
}

uint32 HrWrapperWin::GetHeight()
{
	return m_nHeight;
}

LRESULT HrWrapperWin::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ACTIVATE:
		break;
	case WM_ERASEBKGND:
		return 1;
	case WM_PAINT:
		break;
	case WM_ENTERSIZEMOVE:
		break;
	case WM_EXITSIZEMOVE:
		break;
	case WM_SIZE:
		break;
	case WM_GETMINMAXINFO:
		break;
	case WM_SETCURSOR:
		break;
	case WM_CHAR:
		break;
	case WM_INPUT:
		break;
	case WM_POINTERDOWN:
		break;
	case WM_POINTERUP:
		break;
	case WM_POINTERUPDATE:
		break;
	case WM_POINTERWHEEL:
		break;
	case WM_DPICHANGED:
		break;
	case WM_CLOSE:
		::PostQuitMessage(0);
		return 0;
	case WM_SYSCOMMAND:
		break;
	}

	return default_wnd_proc_(hWnd, uMsg, wParam, lParam);
}

uint32 HrWrapperWin::GetTopX()
{
	return m_nLeft;
}

uint32 HrWrapperWin::GetTopY()
{
	return m_nTop;
}
