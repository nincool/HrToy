#include <windows.h>
#include "HrWinTools.h"
#include "HrConsole.h"

int WINAPI WinMain( HINSTANCE hInstance,	//当前实例句柄
	HINSTANCE hPrevInstance,                //前一个实例句柄
	LPSTR lpCmdLine,			            //命令行字符
	int nCmdShow )			                //窗口显示方式
{
	SetMyCurrentDirectory();
	
#ifdef _DEBUG
	CHrConsole::OpenConsole();
#endif // DEBUG




#ifdef _DEBUG
	CHrConsole::CloseConsole();
#endif // DEBUG

	return 0;
}


















