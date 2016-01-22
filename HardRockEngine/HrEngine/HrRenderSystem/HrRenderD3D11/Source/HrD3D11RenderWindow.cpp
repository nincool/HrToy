#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderWindow.h"

using namespace Hr;

HrD3D11RenderWindow::HrD3D11RenderWindow()
{
	m_nWidth = m_nHeight = 0;

	m_hWnd = NULL;
}

bool HrD3D11RenderWindow::CreateRenderWindow(uint32 nWidth, uint32 nHeight, WNDPROC lpfnProc)
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
}

