#ifndef _HR_WINDOW_H_
#define _HR_WINDOW_H_

#include "HrCorePrerequisite.h"

namespace Hr
{
	class HrWindow
	{
	public:
		HrWindow();
		virtual ~HrWindow();

		virtual bool CreateAppWidnow() = 0;

		virtual void Update() = 0;

		virtual void Destroy() = 0;
	};
}

#endif


