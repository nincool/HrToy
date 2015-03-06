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


int WINAPI WinMain( HINSTANCE hInstance,	//当前实例句柄
	HINSTANCE hPrevInstance,                //前一个实例句柄
	LPSTR lpCmdLine,			            //命令行字符
	int nCmdShow )			                //窗口显示方式
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


















