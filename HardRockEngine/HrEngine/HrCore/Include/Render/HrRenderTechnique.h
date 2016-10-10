#ifndef _HR_RENDERTECHNIQUE_H_
#define _HR_RENDERTECHNIQUE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrRenderTechnique
	{
	public:
		HrRenderTechnique(std::string strTechniqueName);
		virtual ~HrRenderTechnique();

		virtual size_t GetHashName();
		virtual HrRenderPass* GetRenderPass(uint32 nIndex);
		virtual void UpdateEffectParams(HrRenderFrameParameters& renderFrameParameters);

		HrRenderPass* CreatePass(std::string strPassName);
	protected:
		size_t m_nHashName;
		std::string m_strTechniqueName;
		std::vector<HrRenderPass*> m_vecPass;
	};



}

#endif


