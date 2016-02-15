#ifndef _HR_RENDERTECHNIQUE_H_
#define _HR_RENDERTECHNIQUE_H_

#include "HrCore/Include/Render/IRenderTechnique.h"

namespace Hr
{

	class HR_CORE_API HrRenderTechnique : public IRenderTechnique
	{
	public:
		HrRenderTechnique();
		virtual ~HrRenderTechnique(){}

		virtual HrRenderPass* GetRenderPass() override;

	};



}

#endif


