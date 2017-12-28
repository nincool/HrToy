#ifndef _HR_WINDOW_H_
#define _HR_WINDOW_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrWindow
	{
	public:
		HrWindow();
		virtual ~HrWindow();

		virtual bool CreateAppWidnow() = 0;

		virtual void UpdateMsg() = 0;

		virtual void Destroy() = 0;

		virtual HWND GetHWnd() = 0;

		virtual uint32 GetWidth() = 0;
		virtual uint32 GetHeight() = 0;
	};
}

#endif


