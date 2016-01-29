#include <windows.h>
#include <tchar.h>
#include "HrCommon/Include/HrPrerequisite.h"
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

	typedef void(*APP_INIT_FUNC)();
	typedef void(*APP_RELEASE_FUNC)();

	Hr::HrModuleLoader moduleLoaderApp("HrCore");
	if (moduleLoaderApp.HrLoadModule())
	{
		APP_INIT_FUNC runFunc = static_cast<APP_INIT_FUNC>(moduleLoaderApp.GetProcAddress(std::string("HrModuleInitialize")));
		if (runFunc)
		{
			runFunc();
		}

		APP_RELEASE_FUNC releaseFunc = static_cast<APP_RELEASE_FUNC>(moduleLoaderApp.GetProcAddress(std::string("HrModuleUnload")));
		if (releaseFunc)
		{
			releaseFunc();
		}
	}

	moduleLoaderApp.HrFreeModule();

	return 0;
}


















