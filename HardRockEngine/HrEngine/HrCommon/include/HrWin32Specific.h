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

#endif