#include "HrApplication.h"
#include "HrCommon.h"

using namespace HR;
CHrApplication::CHrApplication(void)
{
	InitParam();
}

CHrApplication::~CHrApplication(void)
{
	AppRelease();
}

void CHrApplication::InitParam()
{
	m_nWndWidth = 800;
	m_nWndHeight = 600;
}

bool CHrApplication::InitWindow( HINSTANCE hInstance, int nCmdShow )
{
	WNDCLASSEX wc; //窗口类结构

	//填充窗口类结构
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = (WNDPROC)(WinProc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;
	wc.hIcon = (HICON)::LoadImage(NULL, "Res/Hr.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor = LoadCursor( NULL,  IDC_ARROW );
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "HrEngine";
	wc.hIconSm = NULL;

	//注册窗口类
	RegisterClassEx( &wc );

	//创建主窗口
	m_hWnd = CreateWindow(
		"HrEngine",             //窗口类名称
		"HrEngine",             //窗口标题
		WS_OVERLAPPEDWINDOW,     //窗口风格，定义为普通型
		0,                       //窗口位置的x坐标
		0,                       //窗口位置的y坐标
		m_nWndWidth,             //窗口的宽度
		m_nWndHeight,            //窗口的高度
		NULL,                    //父窗口句柄
		NULL,                    //菜单句柄
		hInstance,               //应用程序实例句柄
		NULL );                  //窗口创建数据指针

	if( !m_hWnd )
		return FALSE;
	//Get the width and height of the window
	int nWindowWidth = GetSystemMetrics(SM_CXSCREEN);
	int nWindowHeight = GetSystemMetrics(SM_CYSCREEN);
	int nWindowX = (nWindowWidth - m_nWndWidth) >> 1;
	int nWindowY = (nWindowHeight - m_nWndHeight) >> 1;

	MoveWindow(m_hWnd, nWindowX, nWindowY, m_nWndWidth, m_nWndHeight, false);
	//显示并更新窗口
	ShowWindow( m_hWnd, nCmdShow );

	UpdateWindow( m_hWnd );

	return TRUE;
}

LRESULT CALLBACK CHrApplication::WinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
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

void CHrApplication::AppGo()
{
	m_hInstance = GetModuleHandle(0);

	InitWindow(m_hInstance, SW_SHOW);
	InitD3D();

	AppSetup();

	MSG msg;
	memset(&msg, 0, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )   //查看应用程序消息队列，有消息时将队列中的消息派发出去。
		{
			TranslateMessage( &msg );					//将虚拟键消息转换为字符消息
			DispatchMessage( &msg );					//该函数分发一个消息给窗口程序。
		}
		else
		{
			UpdateScene();
			RenderScene();
		}
	}

	UnregisterClass("MyApp", m_hInstance);
}

bool CHrApplication::InitD3D()
{
	return CHrD3DUtil::InitializeD3D(m_hWnd, m_nWndWidth, m_nWndHeight, false, D3DDEVTYPE_HAL);
}

void CHrApplication::AppSetup()
{

}

void CHrApplication::AppRelease()
{
	CHrD3DUtil::ReleaseD3D();
}

void CHrApplication::PreRender()
{

}

void CHrApplication::RenderScene()
{

}

void CHrApplication::PostRender()
{

}

void CHrApplication::UpdateScene()
{

}

