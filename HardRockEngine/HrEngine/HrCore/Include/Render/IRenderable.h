#ifndef _I_RENDERABLE_H_
#define _I_RENDERABLE_H_

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

		IRenderLayout* GetRenderLayout()
		{
			return m_pRenderLayout;
		}
		IRenderTechnique* GetRenderTechnique()
		{
			return m_pRenderTechnique;
		}
	protected:
		IRenderLayout* m_pRenderLayout;
		IRenderTechnique* m_pRenderTechnique;
		
	};
}

#endif



