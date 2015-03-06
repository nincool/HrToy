#include "stdafx.h"
#include <windows.h>
#include "HrWinTools.h"
#include "HrConsole.h"

#include "debug_new/DebugNew_impl.h"



class TestA
{
public:
	TestA( int _a, int _b )
	{
		c = _a;
		a = _b;
	}
	int c;
	int a;
	double d;
	float e;
};


int WINAPI WinMain( HINSTANCE hInstance,	//��ǰʵ�����
	HINSTANCE hPrevInstance,                //ǰһ��ʵ�����
	LPSTR lpCmdLine,			            //�������ַ�
	int nCmdShow )			                //������ʾ��ʽ
{
	SetMyCurrentDirectory();
	
#ifdef _DEBUG
	CHrConsole::OpenConsole();
#endif // DEBUG

	TestA* pTest = HR_NEW2( TestA, 1, 2 );
	
	HR_DELETE( pTest );
#ifdef _DEBUG
	CHrConsole::CloseConsole();
#endif // DEBUG

	return 0;
}


















