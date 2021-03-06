﻿/************************************************************************
*
* @Comment：
*
* @Author: Hr
* @Date: [10/21/2015 By Hr]
*
************************************************************************/  

#ifndef _HR_PLATFORMCONFIG_H_
#define _HR_PLATFORMCONFIG_H_



#pragma region PLATFORM
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
#define HR_TARGET_PLATFORM             HR_PLATFORM_WIN32

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


#pragma endregion

#pragma region CPU

#define HR_CPU_X86        0
#define HR_CPU_ARM        1
/* Find CPU type
*/
#if (defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))) || \
	(defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__)))
#   define HR_CPU HR_CPU_X86
#else
#	define HR_CPU HR_CPU_ARM
#endif

#pragma endregion

#pragma region COMPILER
////////////////////////////////////////////////////////////////////////////
// Compiler Judge
// Determine compiler: after this, one of the following symbols will
// be defined: COMPILER_GCC, COMPILER_MSVC.

#if defined(__GNUG__)
# define COMPILER_GCC
#elif defined(_MSC_VER)
# define COMPILER_MSVC
#else
# error "Could not determine compiler"
#endif
#pragma endregion


#define HR_RESTRICT_ALIASING 1

#if HR_RESTRICT_ALIASING != 0
	#ifdef COMPILER_MSVC
		#define RESTRICT_ALIAS __restrict   //MSVC
		#define RESTRICT_ALIAS_RETURN __restrict
	#else
		#define RESTRICT_ALIAS __restrict__ //GCC... and others?
		#define RESTRICT_ALIAS_RETURN
	#endif
#else
	#define RESTRICT_ALIAS
	#define RESTRICT_ALIAS_RETURN
#endif


#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
#include "HrWin32Specific.h"
#else if(HR_TARGET_PLATFORM == HR_PLATFORM_LINUX || HR_TARGET_PLATFORM == HR_PLATFORM_ANDROID)
#include "HrLinuxSpecific.h"
#endif

//////////////////////////////////////////////////////////////////////////
// shared lib access define
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32 || HR_TARGET_PLATFORM == HR_PLATFORM_WINRT)
#define HR_EXPORT __declspec(dllexport)
#define HR_IMPORT __declspec(dllimport)
#else
#define HR_EXPORT __attribute__ ((visibility("default")))
#define HR_IMPORT __attribute__ ((visibility("default")))
#endif

#endif // !_HR_PLATFORMCONFIG_H_

