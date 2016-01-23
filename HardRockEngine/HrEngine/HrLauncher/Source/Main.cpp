#include <windows.h>
#include <tchar.h>
#include "HrCommon/Include/HrPlatformConfig.h"
#include "HrUtilTools/Include/HrModuleLoader.h"

//#include "HrMain/Include/HrLog.h"

bool EraseEndStringWithChar(TCHAR* p, TCHAR c)
{
	TCHAR* pFlag = _tcsrchr(p, c);
	if (pFlag != NULL)
	{
		*(pFlag) = '\0';

		return true;
	}

	return false;
}

inline bool SetMyCurrentDirectory()
{
	//设置工作目录
	TCHAR szModuleDir[512];
	ZeroMemory(szModuleDir, sizeof(szModuleDir));

	GetModuleFileName(NULL, szModuleDir, sizeof(szModuleDir));
	bool b1 = EraseEndStringWithChar(szModuleDir, _T('\\'));
	bool b2 = EraseEndStringWithChar(szModuleDir, _T('\\'));

	if (b1 && b2)
		SetCurrentDirectory(szModuleDir);
	else
		return false;

	return true;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	SetMyCurrentDirectory();

	typedef void(*AppInitFunc)();

	Hr::HrModuleLoader moduleLoaderApp("HrCore", "HrModuleInitialize");
	if (moduleLoaderApp.HrLoadModule())
	{
		AppInitFunc runFunc = static_cast<AppInitFunc>(moduleLoaderApp.GetProcAddress());
		if (runFunc)
		{
			runFunc();
		}
	}
	moduleLoaderApp.HrFreeModule();

	return 0;
}


















