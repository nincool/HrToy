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
	case WM_KEYDOWN://������Ϣ
	{
		switch (wParam)
		{
		case VK_F1:
			MessageBox(hWnd, "�Ұ�����F1", "TestMessage", MB_OK);
			break;
		case VK_ESCAPE:
			MessageBox(hWnd, "ESC��������!", "Keyboard", MB_OK);
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	case WM_RBUTTONDOWN://�����Ϣ
	{
		//MessageBox(hWnd,"����Ҽ�������!","Mouse",MB_OK);
		break;
	}
	case WM_DESTROY://�˳���Ϣ
	{
		PostQuitMessage(0);//�����˳�����
		break;
	}

	}

	//����ȱʡ��Ϣ�������
	return DefWindowProc(hWnd, message, wParam, lParam);
}
