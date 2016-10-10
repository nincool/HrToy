#ifndef _HR_RENDERABLE_H_
#define _HR_RENDERABLE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrRenderable
	{
	public:
		HrRenderable();
		~HrRenderable();

		virtual HrRenderLayout* GetRenderLayout();
		virtual HrRenderTechnique* GetRenderTechnique();

		virtual void UpdateRenderFrameParameters(HrRenderFrameParameters& renderFrameParameters);
	protected:
		HrRenderLayout* m_pRenderLayout;
		HrRenderTechnique* m_pRenderTechnique;
	};
}

#endif

