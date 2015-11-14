#include <windows.h>
#include <tchar.h>
#include "HrCommon/Include/HrPlatformConfig.h"

#include "HrMain/Include/HrLog.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	HINSTANCE hHandle = nullptr;
	MODULE_START pFuncStart = HrLoadModule(hHandle, _T("HrGameFramework"));
	if (pFuncStart != nullptr)
	{
		pFuncStart();
	}

	return 0;
}


















