#include "Kernel/HrLog.h"
#include <iostream>
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrLog::HrLog()
{
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
	//AllocConsole();
	//freopen("CONOUT$", "w+t", stdout);
	//freopen("CONIN$", "r+t", stdin);

	//std::wcout.imbue(std::locale("chs"));
	//::system("chcp 65001");
#endif
}

HrLog::~HrLog()
{
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
	FreeConsole();
#endif
}

void HrLog::Log(EnumLogType nLevel, const wchar_t* pszFormat, ...)
{
	const int HR_MAX_STRING_FORMAT_LENGTH = 2560;

	std::wstring rt;

	va_list ap;
	va_start(ap, pszFormat);

	wchar_t szBuffer[HR_MAX_STRING_FORMAT_LENGTH];
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

void HrLog::LogStringToConsole(EnumLogType nLevel, std::wstring& strContent)
{
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
	static HANDLE consolehwnd;
	consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (nLevel)
	{
	case _HALL:
		break;
	case _HWARNING:
		SetConsoleTextAttribute(consolehwnd, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case _HERROR:
		SetConsoleTextAttribute(consolehwnd, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;

	}

	std::wcout << strContent << std::endl;
	
	SetConsoleTextAttribute(consolehwnd, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
#endif
}

void HrLog::Log(EnumLogType nLevel, const char* pFormat, ...)
{
	const int HR_MAX_STRING_FORMAT_LENGTH = 2560;

	std::string rt;

	va_list ap;
	va_start(ap, pFormat);

	char szBuffer[HR_MAX_STRING_FORMAT_LENGTH];
	memset(szBuffer, 0, HR_MAX_STRING_FORMAT_LENGTH);
	int nCount = vsprintf(szBuffer, pFormat, ap);
	va_end(ap);
	if (nCount == -1 || nCount >= HR_MAX_STRING_FORMAT_LENGTH)
	{
		szBuffer[HR_MAX_STRING_FORMAT_LENGTH - 1] = '\0';
	}
	rt = szBuffer;

	LogStringToConsole(nLevel, rt);
}

void HrLog::LogStringToConsole(EnumLogType nLevel, std::string& strContent)
{
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
	static HANDLE consolehwnd;
	consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (nLevel)
	{
	case _HALL:
		break;
	case _HWARNING:
		SetConsoleTextAttribute(consolehwnd, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case _HERROR:
		SetConsoleTextAttribute(consolehwnd, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;

	}

	std::cout << strContent << std::endl;

	SetConsoleTextAttribute(consolehwnd, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
#endif
}
