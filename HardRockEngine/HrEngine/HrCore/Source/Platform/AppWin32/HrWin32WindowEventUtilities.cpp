﻿#include "Platform/AppWin32/HrWin32WindowEventUtilities.h"
#include "HrDirector.h"

using namespace Hr;

HrWin32WindowEventUtilities::HrWin32WindowEventUtilities()
{
}

HrWin32WindowEventUtilities::~HrWin32WindowEventUtilities()
{
}

bool HrWin32WindowEventUtilities::MessagePump()
{
	MSG msg;
	while (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		if (msg.message != WM_QUIT)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			return false;
		}
	}

	return true;
}

LRESULT CALLBACK Hr::HrWin32WindowEventUtilities::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CLOSE:
		{
			HrDirector::Instance()->End();
			break;
		}
		case WM_RBUTTONDOWN://鼠标消息
		{
			//MessageBox(hWnd,"鼠标右键按下了!","Mouse",MB_OK);
			break;
		}
		case WM_DESTROY://退出消息
		{
			//PostQuitMessage(0);//调用退出函数
			break;
		}

	}

	//调用缺省消息处理过程
	return DefWindowProc(hWnd, message, wParam, lParam);
}
