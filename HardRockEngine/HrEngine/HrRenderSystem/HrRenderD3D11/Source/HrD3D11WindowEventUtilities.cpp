#include "HrD3D11WindowEventUtilities.h"

using namespace Hr;

HrD3D11WindowEventUtilities::HrD3D11WindowEventUtilities()
{
}

HrD3D11WindowEventUtilities::~HrD3D11WindowEventUtilities()
{
}

void Hr::HrD3D11WindowEventUtilities::MessagePump()
{
	MSG msg;
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		if (msg.message != WM_QUIT)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

LRESULT CALLBACK Hr::HrD3D11WindowEventUtilities::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN://击键消息
	{
		switch (wParam)
		{
		case VK_F1:
			MessageBox(hWnd, "我按下了F1", "TestMessage", MB_OK);
			break;
		case VK_ESCAPE:
			MessageBox(hWnd, "ESC键按下了!", "Keyboard", MB_OK);
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
