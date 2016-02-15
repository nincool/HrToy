#ifndef _HR_RENDERABLE_H_
#define _HR_RENDERABLE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IRenderable : public RenderableAllocatedObject
	{
	public:
		IRenderable()
		{
			m_pRenderLayout = nullptr;
			m_pRenderTechnique = nullptr;
		}
		virtual ~IRenderable(){}

		HrRenderLayout* GetRenderLayout()
		{
			return m_pRenderLayout;
		}
		HrRenderTechnique* GetRenderTechnique()
		{
			return m_pRenderTechnique;
		}
	private:
		HrRenderLayout* m_pRenderLayout;
		HrRenderTechnique* m_pRenderTechnique;
		
	};
}

#endif



