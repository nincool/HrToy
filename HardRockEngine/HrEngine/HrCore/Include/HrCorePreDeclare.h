#ifndef _HR_COREPREDECLARE_H_
#define _HR_COREPREDECLARE_H_

#include <memory>

namespace Hr
{
	class IApplication;
	typedef std::unique_ptr<IApplication> IApplicationPtr;
	class HrApplication;
	typedef std::unique_ptr<HrApplication> HrApplicationPtr;

	class ILog;
	class HrLog;
	typedef std::unique_ptr<HrLog> HrLogPtr;
}


#endif



