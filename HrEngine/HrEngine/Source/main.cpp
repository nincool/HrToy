
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
	//���ù���Ŀ¼
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

int WINAPI WinMain( HINSTANCE hInstance,	//��ǰʵ�����
				   HINSTANCE hPrevInstance, //ǰһ��ʵ�����
				   LPSTR lpCmdLine,			//�������ַ�
				   int nCmdShow)			//������ʾ��ʽ
{
	SetMyCurrentDirectory();

	CMyApp app;
	app.AppGo();

	return 0;
}


