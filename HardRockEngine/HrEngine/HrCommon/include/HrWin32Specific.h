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

#   pragma warning( disable: 4996)

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

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{ if(p) { delete (p);		(p)=NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete [] (p);		(p)=NULL; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release();	(p)=NULL; } }
#endif

#ifndef SAFE_release
#define SAFE_release(p)			{ if(p) { (p)->release();	(p)=NULL; } }
#endif

#define HrString std::string

#endif