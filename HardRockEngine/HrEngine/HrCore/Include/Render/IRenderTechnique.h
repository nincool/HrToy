#ifndef _I_RENDERTECHNIQUE_H_
#define _I_RENDERTECHNIQUE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API IRenderTechnique 
	{
	public:
		virtual ~IRenderTechnique(){}

		virtual size_t GetHashName() = 0;
		virtual HrRenderPass* GetRenderPass(uint32 nIndex) = 0;
		virtual void UpdateEffectParams(HrRenderFrameParameters& renderFrameParameters) = 0;
	};
}

#endif

