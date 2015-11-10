#include "HrD3D11Render.h"

using namespace Hr;

HrD3D11Render* HrD3D11Render::m_s_pInstance = nullptr;

HrD3D11Render::HrD3D11Render()
{
	m_hWnd = nullptr;
}

HrD3D11Render::~HrD3D11Render()
{
}

#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)

void HrD3D11Render::Create(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc)
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
		return;
	}
	m_hWnd = CreateWindow(_T("HrD3D11WindowClass"), _T("HrEngine"), WS_OVERLAPPEDWINDOW, 10, 10, nWidth, nHeight, NULL, NULL, hInst, 0);
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	SetFocus(m_hWnd);
	SetForegroundWindow(m_hWnd);
}
#else
void HrD3D11Render::Create(unsigned int nWidth, unsigned int nHeight)
{
}
#endif

void HrD3D11Render::Destroy()
{

}
