#ifndef _HR_RENDERABLE_H_
#define _HR_RENDERABLE_H_

#include "HrCore/Include/Render/IRenderable.h"

namespace Hr
{
	class HrRenderable : public IRenderable
	{
	public:
		HrRenderable();
		~HrRenderable();

		virtual IRenderLayout* GetRenderLayout() override;
		virtual IRenderTechnique* GetRenderTechnique() override;

		virtual void Update(HrRenderFrameParameters& renderFrameParameters) override;
	protected:
		IRenderLayout* m_pRenderLayout;
		IRenderTechnique* m_pRenderTechnique;
	};
}

#endif

