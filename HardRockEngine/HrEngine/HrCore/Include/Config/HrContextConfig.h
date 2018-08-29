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

		void SetWindowWidth(uint32 nWidth);
		uint32 GetWindowWidth() { return m_nWindowWidth; }
		void SetWindowHeight(uint32 nHeight);
		uint32 GetWindowHeight() { return m_nWindowHeight; }
		void SetRenderTargetViewWidth(uint32 nWidth);
		uint32 GetRenderTargetViewWidth() { return m_nRenderTargetViewWidth; }
		void SetRenderTargetViewHeight(uint32 nHeight);
		uint32 GetRenderTargetViewHeight() { return m_nRenderTargetViewHeight; }

		
	protected:
		uint32 m_nWindowHeight;
		uint32 m_nWindowWidth;
		uint32 m_nRenderTargetViewHeight;
		uint32 m_nRenderTargetViewWidth;

	};
}

#endif


