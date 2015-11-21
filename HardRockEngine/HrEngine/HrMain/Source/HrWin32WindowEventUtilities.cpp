#include "HrWin32WindowEventUtilities.h"
#include "HrDirector.h"

using namespace Hr;

HrWin32WindowEventUtilities::HrWin32WindowEventUtilities()
{
}

HrWin32WindowEventUtilities::~HrWin32WindowEventUtilities()
{
}

void Hr::HrWin32WindowEventUtilities::MessagePump()
{
	MSG msg;
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		if (msg.message != WM_QUIT)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			HrDirector::GetInstance()->PurgeDirector();
		}
	}
}

LRESULT CALLBACK Hr::HrWin32WindowEventUtilities::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN://击键消息
	{
		switch (wParam)
		{
		case VK_F1:
			MessageBox(hWnd, _T("我按下了F1"), _T("TestMessage"), MB_OK);
			break;
		case VK_ESCAPE:
			MessageBox(hWnd, _T("ESC键按下了!"), _T("Keyboard"), MB_OK);
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	case WM_RBUTTONDOWN://鼠标消息
	{
		//MessageBox(hWnd,"鼠标右键按下了!","Mouse",MB_OK);
		break;
	}
	case WM_DESTROY://退出消息
	{
		PostQuitMessage(0);//调用退出函数
		break;
	}

	}

	//调用缺省消息处理过程
	return DefWindowProc(hWnd, message, wParam, lParam);
}
