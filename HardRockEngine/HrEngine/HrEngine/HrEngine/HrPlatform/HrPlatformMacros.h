#ifndef _HR_PLATFORMMACROS_H_
#define _HR_PLATFORMMACROS_H_

#include "HrPlatformConfig.h"

#if !defined(HR_DEBUG) || HR_DEBUG == 0
#define HRLOG(...)       do {} while (0)
#define HRLOGINFO(...)   do {} while (0)
#define HRLOGERROR(...)  do {} while (0)
#define HRLOGWARN(...)   do {} while (0)

//log
//__VA_ARGS__ 是一个可变参数的宏，很少人知道这个宏，这个可变参数的宏是新的C99规范中新增的
//如果可变参数被忽略或为空，’##’操作将使预处理器(preprocessor)去除掉它前面的那个逗
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

