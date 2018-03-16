#include <windows.h>
#include <tchar.h>
#include "HrCommon/Include/HrPrerequisite.h"
#include "HrUtilTools/Include/HrModuleLoader.h"

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

#include "HrCore/Include/Kernel/HrDirector.h"

int main()
{
	SetMyCurrentDirectory();

	//这里应该改为根据配置文件进行读取
	typedef void(*APP_INIT_FUNC)();
	typedef void(*APP_RELEASE_FUNC)();

	Hr::HrModuleLoader moduleLoaderApp("HrSampleGeometry");
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

	//todo
	//moduleLoaderApp.HrFreeModule();
	
	return 0;
}


















