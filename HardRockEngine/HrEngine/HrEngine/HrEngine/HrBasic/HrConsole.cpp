#include "HrConsole.h"
#include <stdarg.h>
#include <string>
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32) || (HR_TARGET_PLATFORM == HR_PLATFORM_WINRT)
#include <windows.h>
#pragma warning(disable:4996)

#endif


using namespace Hr;

CHrConsole::CHrConsole()
{
}


CHrConsole::~CHrConsole()
{
}

void Hr::CHrConsole::Log(const char* pFormat, ...)
{
	va_list args;
	va_start(args, pFormat);
	{
		char buf[MAX_LOG_LENGTH];

		vsnprintf(buf, MAX_LOG_LENGTH - 3, pFormat, args);
		strcat(buf, "\n");


#if HR_TARGET_PLATFORM ==  HR_PLATFORM_WIN32 || HR_TARGET_PLATFORM == HR_PLATFORM_WINRT || HR_TARGET_PLATFORM == HR_PLATFORM_WP8
		WCHAR wszBuf[MAX_LOG_LENGTH] = { 0 };
		MultiByteToWideChar(CP_UTF8, 0, buf, -1, wszBuf, sizeof(wszBuf));
		OutputDebugStringW(wszBuf);
		WideCharToMultiByte(CP_ACP, 0, wszBuf, -1, buf, sizeof(buf), nullptr, FALSE);
		printf("%s", buf);
		fflush(stdout);
#else
		// Linux, Mac, iOS, etc
		fprintf(stdout, "%s", buf);
		fflush(stdout);
#endif
	}
	va_end(args);
}
