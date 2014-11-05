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
	WNDCLASSEX wc; //������ṹ

	//��䴰����ṹ
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

	//ע�ᴰ����
	RegisterClassEx( &wc );

	//����������
	m_hWnd = CreateWindow(
		"HrEngine",             //����������
		"HrEngine",             //���ڱ���
		WS_OVERLAPPEDWINDOW,     //���ڷ�񣬶���Ϊ��ͨ��
		0,                       //����λ�õ�x����
		0,                       //����λ�õ�y����
		m_nWndWidth,             //���ڵĿ��
		m_nWndHeight,            //���ڵĸ߶�
		NULL,                    //�����ھ��
		NULL,                    //�˵����
		hInstance,               //Ӧ�ó���ʵ�����
		NULL );                  //���ڴ�������ָ��

	if( !m_hWnd )
		return FALSE;
	//Get the width and height of the window
	int nWindowWidth = GetSystemMetrics(SM_CXSCREEN);
	int nWindowHeight = GetSystemMetrics(SM_CYSCREEN);
	int nWindowX = (nWindowWidth - m_nWndWidth) >> 1;
	int nWindowY = (nWindowHeight - m_nWndHeight) >> 1;

	MoveWindow(m_hWnd, nWindowX, nWindowY, m_nWndWidth, m_nWndHeight, false);
	//��ʾ�����´���
	ShowWindow( m_hWnd, nCmdShow );

	UpdateWindow( m_hWnd );

	return TRUE;
}

LRESULT CALLBACK CHrApplication::WinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
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
		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )   //�鿴Ӧ�ó�����Ϣ���У�����Ϣʱ�������е���Ϣ�ɷ���ȥ��
		{
			TranslateMessage( &msg );					//���������Ϣת��Ϊ�ַ���Ϣ
			DispatchMessage( &msg );					//�ú����ַ�һ����Ϣ�����ڳ���
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

