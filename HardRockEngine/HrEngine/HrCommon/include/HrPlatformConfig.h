/************************************************************************
*
* @Comment：
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

//////////////////////////////////////////////////////////////////////////
// Compiler Judge
// Determine compiler: after this, one of the following symbols will
// be defined: COMPILER_GCC, COMPILER_MSVC.

#if defined(__GNUG__)
# define COMPILER_GCC
#elif defined(_MSC_VER)
# define COMPILER_MSVC
// i don't care about your debug symbol issues...
//# pragma warning(disable:4786)
#else
# error "Could not determine compiler"
#endif

//////////////////////////////////////////////////////////////////////////
// shared lib access define
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32 || HR_TARGET_PLATFORM == HR_PLATFORM_WINRT)
#define HR_EXPORT __declspec(dllexport)
#define HR_IMPORT __declspec(dllimport)

#define HR_MODULE_OPEN(a) LoadLibraryEx(a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
#define HR_MODULE_GETSYSTEM(a,b) GetProcAddress(a,b)
#define HR_MODULE_FREE(a) FreeLibrary(a)

#if (HR_DEBUG > 0)
#define HR_PREFIX _T("")
#define HR_SUFFIX _T("D.dll")
#else
#define HR_PREFIX _T("")
#define HR_SUFFIX _T(".dll")
#endif
#define HR_MODULE_START_FUNC _T("HrModuleInitialize")
#define HR_MUDULE_END_FUNC _T("HrModuleUnload")

#else
#define HR_EXPORT __attribute__ ((visibility("default")))
#define HR_IMPORT __attribute__ ((visibility("default")))

#define HR_MODULE_OPEN(a) dlopen(a, RTLD_LAZY | RTLD_GLOBAL)
#define HR_MODULE_GETSYM(a,b) dlsym(a,b)
#define HR_MODULE_FREE(a) dlclose(a)

#define HR_PREFIX _T("/data/data/com.kkstudio.gklauncher/lib/lib")
#define HR_SUFFIX _T(".so")

#endif

#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32 || HR_TARGET_PLATFORM  == HR_PLATFORM_WINRT)
#include "HrWin32Specific.h"
#else if(HR_TARGET_PLATFORM == HR_PLATFORM_LINUX || HR_TARGET_PLATFORM == HR_PLATFORM_ANDROID)
#include "HrLinuxSpecific.h"
#endif

//////////////////////////////////////////////////////////////////////////
// Module Init

// start & end func
typedef void(*MODULE_START)();
typedef void(*MODULE_END)(void);

// module accessing func
inline void HrFreeModule(HINSTANCE& hHandle)
{
	if (hHandle)
	{
		MODULE_END pFunc = (MODULE_END)HR_MODULE_GETSYSTEM(hHandle, HR_MUDULE_END_FUNC);
		pFunc();
		HR_MODULE_FREE(hHandle);
	}
}

inline MODULE_START HrLoadModule(HINSTANCE& hHandle, const TCHAR* pModuleName)
{
	TCHAR finalModuleName[MAX_PATH] = HR_PREFIX;
	_tcscat(finalModuleName, pModuleName);
	_tcscat(finalModuleName, HR_SUFFIX);

	hHandle = HR_MODULE_OPEN(finalModuleName);
	if (hHandle)
	{
		MODULE_START pFunc = (MODULE_START)HR_MODULE_GETSYSTEM(hHandle, HR_MODULE_START_FUNC);
		return pFunc;
	}
	else
	{
		int winError = GetLastError();
		return nullptr;
	}
}


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

