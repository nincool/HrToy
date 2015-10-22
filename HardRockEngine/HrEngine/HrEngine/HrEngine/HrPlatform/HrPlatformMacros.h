#ifndef _HR_PLATFORMMACROS_H_
#define _HR_PLATFORMMACROS_H_

#include "HrPlatformConfig.h"

#if !defined(HR_DEBUG) || HR_DEBUG == 0
#define HRLOG(...)       do {} while (0)
#define HRLOGINFO(...)   do {} while (0)
#define HRLOGERROR(...)  do {} while (0)
#define HRLOGWARN(...)   do {} while (0)

//log
//__VA_ARGS__ ��һ���ɱ�����ĺ꣬������֪������꣬����ɱ�����ĺ����µ�C99�淶��������
//����ɱ���������Ի�Ϊ�գ���##��������ʹԤ������(preprocessor)ȥ������ǰ����Ǹ���
#define HRLOGFILE(msg, ...)				do {} while (0)

#elif HR_DEBUG == 1
#define HRLOG(format, ...)				Hr::CHrConsole::Log(format, ##__VA_ARGS__)
#define HRLOGERROR(format,...)  
#define HRLOGINFO(format,...)			do {} while (0)
#define HRLOGWARN(...) 

#define HRLOGFILE(msg, ...)				HLog.Log(_HALL, "Engine", msg, ##__VA_ARGS__)  

#elif HR_DEBUG > 1
#define HRLOG(format, ...)				Hr::CHrConsole::Log(format, ##__VA_ARGS__)
#define HRLOGERROR(format,...)  
#define HRLOGINFO(format,...)   
#define HRLOGWARN(...) 

#define HRLOGFILE(msg, ...)				HLog.Log(_HALL, "Engine", msg, ##__VA_ARGS__) 

#endif // COCOS2D_DEBUG

#endif

