
#include <windows.h>
#include "MyApp.h"
#include <d3dx9.h>
#include <cassert>

bool EraseEndStringWithChar(char* p, char c)
{
	assert(p && "EraseEndStringWhithChar Error, the param is null");

	char* pFlag = strrchr(p, c);
	if (pFlag != NULL)
	{
		*(pFlag) = '\0';

		return true;
	}

	return false;
}

bool SetMyCurrentDirectory()
{
	//设置工作目录
	char* pFlag = NULL;
	char szModuleDir[255];
	ZeroMemory(szModuleDir, sizeof(szModuleDir));

	GetModuleFileName(NULL, szModuleDir, sizeof(szModuleDir));
	bool b1 = EraseEndStringWithChar(szModuleDir, '\\');
	bool b2 = EraseEndStringWithChar(szModuleDir, '\\');
	if (b1 && b2)
		SetCurrentDirectory(szModuleDir);
	else
		return false;

	return true;
}

int WINAPI WinMain( HINSTANCE hInstance,	//当前实例句柄
				   HINSTANCE hPrevInstance, //前一个实例句柄
				   LPSTR lpCmdLine,			//命令行字符
				   int nCmdShow)			//窗口显示方式
{
	SetMyCurrentDirectory();

	CMyApp app;
	app.AppGo();

	return 0;
}


