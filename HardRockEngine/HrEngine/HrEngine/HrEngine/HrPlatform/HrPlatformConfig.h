/************************************************************************
*
* @Comment£º
*
* @Author: Hr
* @Date: [10/21/2015 By Hr]
*
************************************************************************/  

#ifndef _HR_PLATFORMCONFIG_H_
#define _HR_PLATFORMCONFIG_H_


// define supported target platform macro
#define HR_PLATFORM_UNKNOWN            0
#define HR_PLATFORM_IOS                1
#define HR_PLATFORM_ANDROID            2
#define HR_PLATFORM_WIN32              3
#define HR_PLATFORM_MARMALADE          4
#define HR_PLATFORM_LINUX              5
#define HR_PLATFORM_BADA               6
#define HR_PLATFORM_BLACKBERRY         7
#define HR_PLATFORM_MAC                8
#define HR_PLATFORM_NACL               9
#define HR_PLATFORM_EMSCRIPTEN        10
#define HR_PLATFORM_TIZEN             11
#define HR_PLATFORM_QT5               12
#define HR_PLATFORM_WP8               13
#define HR_PLATFORM_WINRT             14

// Determine target platform by compile environment macro.
#define HR_TARGET_PLATFORM             HR_PLATFORM_UNKNOWN

// mac
#if defined(CC_TARGET_OS_MAC) || defined(__APPLE__)
#undef  HR_TARGET_PLATFORM
#define HR_TARGET_PLATFORM         HR_PLATFORM_MAC
#endif

// iphone
#if defined(CC_TARGET_OS_IPHONE)
#undef  HR_TARGET_PLATFORM
#define HR_TARGET_PLATFORM         HR_PLATFORM_IOS
#endif

// android
#if defined(ANDROID)
#undef  HR_TARGET_PLATFORM
#define HR_TARGET_PLATFORM         HR_PLATFORM_ANDROID
#endif

// win32
#if defined(_WIN32) && defined(_WINDOWS)
#undef  HR_TARGET_PLATFORM
#define HR_TARGET_PLATFORM         HR_PLATFORM_WIN32
#endif

// linux
#if defined(LINUX) && !defined(__APPLE__)
#undef  HR_TARGET_PLATFORM
#define HR_TARGET_PLATFORM         HR_PLATFORM_LINUX
#endif

// marmalade
#if defined(MARMALADE)
#undef  HR_TARGET_PLATFORM
#define HR_TARGET_PLATFORM         HR_PLATFORM_MARMALADE
#endif

// bada
#if defined(SHP)
#undef  HR_TARGET_PLATFORM
#define HR_TARGET_PLATFORM         HR_PLATFORM_BADA
#endif

// qnx
#if defined(__QNX__)
#undef  HR_TARGET_PLATFORM
#define HR_TARGET_PLATFORM     HR_PLATFORM_BLACKBERRY
#endif

// native client
#if defined(__native_client__)
#undef  HR_TARGET_PLATFORM
#define HR_TARGET_PLATFORM     HR_PLATFORM_NACL
#endif

// Emscripten
#if defined(EMSCRIPTEN)
#undef  HR_TARGET_PLATFORM
#define HR_TARGET_PLATFORM     HR_PLATFORM_EMSCRIPTEN
#endif

// tizen
#if defined(TIZEN)
#undef  HR_TARGET_PLATFORM
#define HR_TARGET_PLATFORM     HR_PLATFORM_TIZEN
#endif

// qt5
#if defined(CC_TARGET_QT5)
#undef  HR_TARGET_PLATFORM
#define HR_TARGET_PLATFORM     HR_PLATFORM_QT5
#endif

// WinRT (Windows Store App)
#if defined(WINRT)
#undef  HR_TARGET_PLATFORM
#define HR_TARGET_PLATFORM			HR_PLATFORM_WINRT
#endif

// WP8 (Windows Phone 8 App)
#if defined(WP8)
#undef  HR_TARGET_PLATFORM
#define HR_TARGET_PLATFORM			HR_PLATFORM_WP8
#endif


//////////////////////////////////////////////////////////////////////////
// post configure
//////////////////////////////////////////////////////////////////////////

// check user set platform
#if ! HR_TARGET_PLATFORM
#error  "Cannot recognize the target platform; are you targeting an unsupported platform?"
#endif 

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//#ifndef __MINGW32__
//#pragma warning (disable:4127) 
//#endif 
//#endif  // _PLATFORM_WIN32

#endif // !_HR_PLATFORMCONFIG_H_

