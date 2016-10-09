#ifndef _HR_APPLICATION_WIN32_
#define _HR_APPLICATION_WIN32_

#include "HrCore/Include/HrApplication.h"

namespace Hr
{
	class HR_CORE_API HrApplicationWin : public HrApplication
	{
	public:
		HrApplicationWin();
		virtual ~HrApplicationWin();

		virtual bool ApplicationDidFinishLaunching() override;

		virtual void ApplicationDidEnterBackground() override;

		virtual void ApplicationWillEnterForeground() override;

		virtual Platform GetTargetPlatform() override
		{
			return HrApplication::Platform::OS_WINDOWS;
		}

		virtual void Run() override;

		virtual bool Destroy() override;

	protected:
		bool CreateAppWindow();

	protected:
		HR_SYNTHESIZE_READONLY(HWND, m_hWnd, Hwnd);
		HR_SYNTHESIZE_READONLY(uint32, m_nWidth, Width);
		HR_SYNTHESIZE_READONLY(uint32, m_nHeight, Height);

	};


}

#endif

