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
		static void ReleaseInstance();

		void Log(ILog::EnumLogType nLevel, const wchar_t* pszFormat, ...);
		void Log(ILog::EnumLogType nLevel, const char* pFormat, ...);


	private:
		void LogStringToConsole(ILog::EnumLogType nLevel, std::wstring&  strContent);
		void LogStringToConsole(ILog::EnumLogType nLevel, std::string& strContent);
	private:
		static HrLogPtr m_pUniqueLog;
	};
}


#endif

