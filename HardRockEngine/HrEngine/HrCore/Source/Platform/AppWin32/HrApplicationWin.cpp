#include "Platform/AppWin32/HrApplicationWin.h"
#include "Platform/AppWin32/HrWin32WindowEventUtilities.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "Config/HrContextConfig.h"
#include "HrDirector.h"
#include "HrLog.h"

using namespace Hr;

HrApplicationWin::HrApplicationWin()
{
	m_hWnd = nullptr;
	m_nWidth = 600;
	m_nHeight = 400;
}

HrApplicationWin::~HrApplicationWin()
{
	Destroy();
}

bool HrApplicationWin::ApplicationDidFinishLaunching()
{
	return true;
}

void HrApplicationWin::ApplicationDidEnterBackground()
{

}

void HrApplicationWin::ApplicationWillEnterForeground()
{

}

void HrApplicationWin::Run()
{
	HRLOG(_T("Application_win32 run"));
	
	CreateAppWindow();

	if (!HrDirector::Instance()->Init())
	{
		HRERROR(_T("Application Run Error!"));
	}
	else
	{
		ApplicationDidFinishLaunching();

		HrDirector::Instance()->StartMainLoop();
	}
}

bool HrApplicationWin::Destroy()
{
	HrDirector::Instance()->Release();
	HrLog::Instance()->Release();
	
	return true;
}

bool HrApplicationWin::CreateAppWindow()
{
	m_nWidth = HrContextConfig::Instance()->GetWindowWidth();
	m_nHeight = HrContextConfig::Instance()->GetWindowHeight();

	HINSTANCE hInst = NULL;
	static const TCHAR staticVar;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, &staticVar, &hInst);

	WNDCLASS wc;
	memset(&wc, 0, sizeof(wc));
	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = HrWin32WindowEventUtilities::WinProc;
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
	m_hWnd = CreateWindow(_T("HrD3D11WindowClass"), _T("HrEngine"), WS_OVERLAPPEDWINDOW, 10, 10, m_nWidth, m_nHeight, NULL, NULL, hInst, 0);
	
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	
	SetFocus(m_hWnd);
	
	SetForegroundWindow(m_hWnd);

	return true;

}
