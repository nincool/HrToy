#ifndef _HR_CONTEXTCONFIG_H_
#define _HR_CONTEXTCONFIG_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/include/HrSingleton.h"

namespace Hr
{
	class HR_CORE_API HrContextConfig : public HrSingleTon<HrContextConfig>
	{
	public:
		HrContextConfig();
		~HrContextConfig();

		
		HR_SYNTHESIZE_READONLY(uint32, m_nWindowWidth, WindowWidth);
		HR_SYNTHESIZE_READONLY(uint32, m_nWindowHeight, WindowHeight);

		HR_SYNTHESIZE_READONLY(uint32, m_nRenderTargetViewWidth, RenderTargetViewWidth);
		HR_SYNTHESIZE_READONLY(uint32, m_nRenderTargetViewHeight, RenderTargetViewHeight);
	};
}

#endif


