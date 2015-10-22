#ifndef _HR_ENGINEMACROS_H_
#define _HR_ENGINEMACROS_H_

#include <assert.h>
#include "HrBasic/HrConsole.h"
#include "HrPlatform/HrPlatformMacros.h"

#define US_NS_HR                    using namespace Hr;

//assert
#ifndef HRASSERT
#define HRASSERT(cond, msg)  \
	if (!(cond)) HRLOG("%s %s %d", msg, __FILE__, __LINE__); \
	assert((cond) && msg) 
#endif

#if !defined(HR_DEBUG) || (HR_DEBUG == 0)

#elif (HR_DEBUG == 1)

#elif (HR_DEBUG > 1)

#endif

//
//#ifdef _DEBUG
//extern bool HrAssertFunction( bool bFlag, char* des, long line, const char* pFile )
//{
//	if (!bFlag) HRLOG( "CHRASSERT", "%s %s %s", des, pFile, line );
//	return bFlag;
//}
//
//#define CHRASSERT(exp, description) \
//	if (HrAssertFunction(exp, description, __LINE__, __FILE__)) \
//				{_asm{int 3)} } //this will cause the debugger to break here on pc's
//#else
//#define CHRASSERT(exp, description)
//#endif

#define HR_SYNTHESIZE(varType, varName, funName) \
	protected:varType varName;\
	public: varType Get##funName(void) const {return varName;}\
	public: void Set##funName(varType var){varName = var;}

#endif