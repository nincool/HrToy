/************************************************************************
*
* @Comment：
*
* @Author: Hr
* @Date: [10/27/2015 By Hr]
*
************************************************************************/  

#ifndef __HRWIN32SPECIFIC_H__
#define __HRWIN32SPECIFIC_H__

#include <Windows.h>
#include <tchar.h>

//Integer formats of fixed bit width
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef int int32;
typedef short int16;
typedef signed char int8;
typedef unsigned __int64 uint64;
typedef __int64 int64;

#define DEPRICATED __declspec(deprecated)


#ifdef UNICODE
#define HrString std::wstring
#else
#define HrString std::string
#endif // UNICODE

#pragma warning(disable:4996)

#endif