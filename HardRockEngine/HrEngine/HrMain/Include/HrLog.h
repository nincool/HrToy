#ifndef _HR_LOG_H_
#define _HR_LOG_H_

#include "HrMainPrerequisiters.h"
#include "ILog.h"

namespace Hr
{
	class HR_MAIN_API HrLog : public ILog
	{
	public:
		HrLog();
		~HrLog();

		void Log(ILog::EnumLogType nLevel, const TCHAR* pszFormat, ...);

		HR_INSTANCE(HrLog);
	private:
		void LogStringToConsole(ILog::EnumLogType nLevel, HrString&  strContent);
	};
}


#endif

