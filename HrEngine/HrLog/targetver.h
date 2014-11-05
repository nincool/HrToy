#pragma once

// 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。

// 如果要为以前的 Windows 平台生成应用程序，请包括 WinSDKVer.h，并将
// WIN32_WINNT 宏设置为要支持的平台，然后再包括 SDKDDKVer.h。

#define _WIN32_WINNT 0x0501      //0x0501为windos xp
#define WINVER 0x0501

#ifndef WINVER                   //指定要求的最低平台是windows vista
#define WINVER 0x0600
#endif

#ifndef _WIN32_WINNT             //指定要求的最低平台是 windows vista
#define _WIN32_WINNT            
#endif

#ifndef _WIN32_WINDOWS           //指定要求的最低平台是 windows 98
#define _WIN32_WINDOWS 0x0410
#endif

#ifndef _WIN32_IE                //指定要求的最低平台是 Internet Explorer 7.0
#define _WIN32_IE 0x0700
#endif

#include <SDKDDKVer.h>


