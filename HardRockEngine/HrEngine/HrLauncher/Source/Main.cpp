#include <windows.h>
#include <tchar.h>
#include "HrCommon/Include/HrPlatformConfig.h"

#include "HrMain/Include/HrLog.h"

bool EraseEndStringWithChar(TCHAR* p, TCHAR c)
{
	assert(p && "EraseEndStringWhithChar Error, the param is null");

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
	TCHAR* pFlag = NULL;
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

	Hr::HrLog::GetInstance()->Log(Hr::ILog::_HALL, _T("-------start-------"));

	HINSTANCE hHandle = nullptr;
	MODULE_START pFuncStart = HrLoadModule(hHandle, _T("HrApplication"));
	if (pFuncStart != nullptr)
	{
		pFuncStart();
	}
	HrFreeModule(hHandle);
	
	system("pause");

	Hr::HrLog::ReleaseInstance();

	return 0;
}


















