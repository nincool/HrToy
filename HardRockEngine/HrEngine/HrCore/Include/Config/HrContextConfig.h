#ifndef _HR_CONTEXTCONFIG_H_
#define _HR_CONTEXTCONFIG_H_

#include "HrCorePrerequisite.h"
#include "HrCommon/include/HrSingleton.h"

namespace Hr
{
	class HrContextConfig : public HrSingleTon<HrContextConfig>
	{
	public:
		HrContextConfig();
		~HrContextConfig();

	public:
		HR_SYNTHESIZE_READONLY(uint32, m_nWindowWidth, WindowWidth);
		HR_SYNTHESIZE_READONLY(uint32, m_nWindowHeight, WindowHeight);
	};
}

#endif


