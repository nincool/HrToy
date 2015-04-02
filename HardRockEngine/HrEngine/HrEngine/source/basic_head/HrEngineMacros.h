#ifndef _HR_ENGINEMACROS_H_
#define _HR_ENGINEMACROS_H_

#include <assert.h>

#define US_NS_HR                    using namespace Hr;

//log
//__VA_ARGS__ 是一个可变参数的宏，很少人知道这个宏，这个可变参数的宏是新的C99规范中新增的
//如果可变参数被忽略或为空，’##’操作将使预处理器(preprocessor)去除掉它前面的那个逗
#ifndef HRLOG
#define HRLOG(msg, ...)				HLog.Log(_HALL, "Engine", msg, ##__VA_ARGS__) 
#endif

#ifndef HRASSERTLOG
#define HRASSERTLOG(msg, ...)       HLog.Log(_HERROR, "HRASSERT", msg, ##__VA_ARGS__)
#endif

#ifndef HRDEBUGLOG						
#define HRDEBUGLOG(m, msg, ...)		HLog.Log( _HDEBUG, m, msg, ##__VA_ARGS__)
#endif

#ifndef HRERRORLOG				
#define HRERRORLOG(m, msg, ...)		HLog.Log(_HERROR, m, msg, ##__VA_ARGS__)
#endif

//assert
#ifndef HRASSERT
#define HRASSERT(cond, msg)  \
	if (!(cond)) HRASSERTLOG("%s %s %d", msg, __FILE__, __LINE__); \
	assert((cond) && msg) 
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


#endif