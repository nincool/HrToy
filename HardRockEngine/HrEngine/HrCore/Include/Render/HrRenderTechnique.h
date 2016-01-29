#ifndef _HR_RENDERTECHNIQUE_H_
#define _HR_RENDERTECHNIQUE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatedObject.h"

namespace Hr
{
	class HrRenderPass;

	class HR_CORE_API HrRenderTechnique
	{
	public:
		HrRenderTechnique();
		virtual ~HrRenderTechnique(){}

		HrRenderPass* GetRenderPass();

	private:
		HrRenderPass* m_pRenderPass;
	};



}

#endif


