#include "HrLog.h"
#include <iostream>

using namespace Hr;

HR_INSTANCE_DEF(HrLog);

HrLog::HrLog()
{
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);
	freopen("CONIN$", "r+t", stdin);

	//::system("chcp 65001");
#endif
}

HrLog::~HrLog()
{
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
	fclose(stdout);
	fclose(stdin);
	FreeConsole();
#endif
}

void HrLog::Log(ILog::EnumLogType nLevel, const TCHAR* pszFormat, ...)
{
#define HR_MAX_STRING_FORMAT_LENGTH (10 * 256)

	HrString rt;

	va_list ap;
	va_start(ap, pszFormat);

	TCHAR szBuffer[HR_MAX_STRING_FORMAT_LENGTH];
	memset(szBuffer, 0, HR_MAX_STRING_FORMAT_LENGTH);
	int nCount = _vstprintf(szBuffer, pszFormat, ap);
	va_end(ap);
	if (nCount == -1 || nCount >= HR_MAX_STRING_FORMAT_LENGTH)
	{
		szBuffer[HR_MAX_STRING_FORMAT_LENGTH - 1] = '\0';
	}
	rt = szBuffer;

	LogStringToConsole(nLevel, rt);
}

void HrLog::LogStringToConsole(ILog::EnumLogType nLevel, HrString& strContent)
{
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
	static HANDLE consolehwnd;
	consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (nLevel)
	{
	case ILog::_HALL:
		break;
	case ILog::_HWARNING:
		SetConsoleTextAttribute(consolehwnd, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case ILog::_HERROR:
		SetConsoleTextAttribute(consolehwnd, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;

	}

#ifdef UNICODE
	std::wcout << strContent << std::endl;
#else
	std::cout << strContent << std::endl;
#endif // UNICODE

	
	SetConsoleTextAttribute(consolehwnd, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
#endif
}

