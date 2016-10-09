#ifndef _HR_LOG_H_
#define _HR_LOG_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/include/HrSingleton.h"

namespace Hr
{
	class HR_CORE_API HrLog : public HrSingleTon<HrLog>
	{
	public:
		HrLog();
		~HrLog();

		enum EnumLogType
		{
			_HALL = 0,
			_HDEBUG,
			_HNOTE,
			_HWARNING,
			_HERROR,
		};

		void Log(EnumLogType nLevel, const wchar_t* pszFormat, ...);
		void Log(EnumLogType nLevel, const char* pFormat, ...);

	private:
		void LogStringToConsole(EnumLogType nLevel, std::wstring&  strContent);
		void LogStringToConsole(EnumLogType nLevel, std::string& strContent);
	};
}


#endif

