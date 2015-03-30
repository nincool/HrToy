#ifndef _HR_ENGINEMACROS_H_
#define _HR_ENGINEMACROS_H_

#include <assert.h>

#define US_NS_HR                    using namespace Hr;

//log

#ifndef HRLOG
#define HRLOG(msg, ...)				HLog.Log(_HALL, "Engine", msg, ##__VA_ARGS__) 
#endif

#ifndef HRDEBUGLOG						
#define HRDEBUGLOG(m, msg, ...)		HLog.Log( _HDEBUG, m, msg, ##__VA_ARGS__)//如果可变参数被忽略或为空，’##’操作将使预处理器(preprocessor)去除掉它前面的那个逗
#endif

#ifndef HRERRORLOG				
#define HRERRORLOG(m, msg, ...)		HLog.Log(_HERROR, m, msg, ##__VA_ARGS__)
#endif

//assert
#ifndef HRASSERT
#define HRASSERT(cond, msg)  \
	if (!(cond)) HRLOG("HrAssert", msg); \
	assert((cond) && msg) 
#endif

#ifdef _DEBUG
extern bool HrAssertFunction( bool bFlag, const char* pFile, const char* pLine );

#define CHRASSERT(exp, description) \
	if (HrAssertFunction((int)exp, description, __LINE__, __FILE__)) \
				{_asm{int 3)} } //this will cause the debugger to break here on pc's
#else
#define CHRASSERT(exp, description)
#endif




#endif