#ifndef _HR_RENDERTECHNIQUE_H_
#define _HR_RENDERTECHNIQUE_H_

#include "HrCore/Include/Render/IRenderTechnique.h"

namespace Hr
{
	class HR_CORE_API HrRenderTechnique : public IRenderTechnique
	{
	public:
		HrRenderTechnique(std::string strTechniqueName);
		virtual ~HrRenderTechnique(){}

		virtual HrRenderPass* GetRenderPass(uint32 nIndex) override;

		HrRenderPass* CreatePass(std::string strPassName);
	protected:
		std::string m_strTechniqueName;
		std::vector<HrRenderPass*> m_vecPass;
	};



}

#endif


