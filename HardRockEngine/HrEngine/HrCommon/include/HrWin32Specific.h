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
#include <cstdint>

//Integer formats of fixed bit width
typedef std::uint32_t uint32;
typedef std::uint16_t uint16;
typedef std::uint8_t uint8;
typedef std::int32_t int32;
typedef std::int16_t int16;
typedef std::int8_t int8;
typedef std::uint64_t uint64;
typedef std::int64_t int64;

typedef char Byte;
typedef Byte* pbyte;

#define DEPRICATED __declspec(deprecated)


#ifdef UNICODE
#define HrString std::wstring
#else
#define HrString std::string
#endif // UNICODE

#pragma warning(disable:4996)

#endif