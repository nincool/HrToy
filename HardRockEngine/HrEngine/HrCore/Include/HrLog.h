#ifndef _HR_LOG_H_
#define _HR_LOG_H_

#include "ILog.h"

namespace Hr
{
	class HR_CORE_API HrLog : public ILog
	{
	public:
		HrLog();
		~HrLog();

		static HrLog& GetInstance();

		void Log(ILog::EnumLogType nLevel, const TCHAR* pszFormat, ...);

	private:
		void LogStringToConsole(ILog::EnumLogType nLevel, HrString&  strContent);

	private:
		static HrLogPtr m_pUniqueLog;
	};
}


#endif

