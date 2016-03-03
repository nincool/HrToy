#ifndef _I_RENDERTECHNIQUE_H_
#define _I_RENDERTECHNIQUE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HR_CORE_API IRenderTechnique : public RenderSysAllocatedObject
	{
	public:
		virtual ~IRenderTechnique(){}

		virtual HrRenderPass* GetRenderPass(uint32 nIndex) = 0;
	};
}

#endif

