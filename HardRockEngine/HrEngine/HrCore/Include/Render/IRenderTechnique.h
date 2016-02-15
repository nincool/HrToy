#ifndef _I_RENDERTECHNIQUE_H_
#define _I_RENDERTECHNIQUE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HrRenderPass;

	class HR_CORE_API IRenderTechnique : public RenderSysAllocatedObject
	{
	public:
		IRenderTechnique()
		{
			m_pRenderPass = nullptr;
		}
		virtual ~IRenderTechnique(){}

		virtual HrRenderPass* GetRenderPass() = 0;

	protected:
		HrRenderPass* m_pRenderPass;
	};
}

#endif