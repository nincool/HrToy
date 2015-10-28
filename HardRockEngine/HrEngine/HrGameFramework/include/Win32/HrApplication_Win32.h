#ifndef _HR_APPLICATION_WIN32_
#define _HR_APPLICATION_WIN32_

#include "IApplication.h"
#include "HrFrameworkPrerequisites.h"

namespace Hr
{
	class HrApplication : public IApplication
	{
	public:
		HrApplication();
		virtual ~HrApplication();


		virtual bool ApplicationDidFinishLaunching() override;

		virtual void ApplicationDidEnterBackground() override;

		virtual void ApplicationWillEnterForeground() override;

		virtual Platform GetTargetPlatform() override
		{
			return IApplication::Platform::OS_WINDOWS;
		}

		virtual void Run() override;

		virtual bool Destroy() override;
	};


}

#endif

