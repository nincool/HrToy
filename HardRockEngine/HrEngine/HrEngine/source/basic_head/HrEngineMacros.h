#ifndef _HR_ENGINEMACROS_H_
#define _HR_ENGINEMACROS_H_

#include <assert.h>

#define US_NS_HR                    using namespace Hr;

//log
//__VA_ARGS__ ��һ���ɱ�����ĺ꣬������֪������꣬����ɱ�����ĺ����µ�C99�淶��������
//����ɱ���������Ի�Ϊ�գ���##��������ʹԤ������(preprocessor)ȥ������ǰ����Ǹ���
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