#ifndef _HR_APPLICATION_WIN32_
#define _HR_APPLICATION_WIN32_

#include "HrCore/Include/Kernel/HrApplication.h"

namespace Hr
{
	class HR_CORE_API HrAppWindows : public HrApplication
	{
	public:
		HrAppWindows();
		virtual ~HrAppWindows();

		virtual bool ApplicationDidFinishLaunching() override;

		virtual void ApplicationDidEnterBackground() override;

		virtual void ApplicationWillEnterForeground() override;

		virtual Platform GetTargetPlatform() override
		{
			return HrApplication::Platform::OS_WINDOWS;
		}
	};
}

#endif

