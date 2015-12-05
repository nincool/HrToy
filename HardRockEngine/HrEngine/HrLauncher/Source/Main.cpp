﻿#include <windows.h>
#include <tchar.h>
#include "HrCommon/Include/HrPlatformConfig.h"

#include "HrMain/Include/HrLog.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	Hr::HrLog::GetInstance()->Log(Hr::ILog::_HALL, _T("-------start-------"));

	HINSTANCE hHandle = nullptr;
	MODULE_START pFuncStart = HrLoadModule(hHandle, _T("HrApplication"));
	if (pFuncStart != nullptr)
	{
		pFuncStart();
	}
	HrFreeModule(hHandle);

	Hr::HrLog::ReleaseInstance();

	return 0;
}

















