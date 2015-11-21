#ifndef _HR_APPLICATION_WIN32_
#define _HR_APPLICATION_WIN32_

#include "HrApplicationPrerequisites.h"
#include "IApplication.h"

namespace Hr
{
	class HrApplication : public IApplication
	{
	public:
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

		HR_INSTANCE(HrApplication);
	protected:
		HrApplication();
	};


}

#endif

