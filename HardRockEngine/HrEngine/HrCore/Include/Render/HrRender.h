#ifndef _HR_RENDER_H_
#define _HR_RENDER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrRender
	{
	public:
		virtual ~HrRender(){};
		/**
		*	@Brief:  ¥¥Ω®‰÷»æ∆˜[10/28/2015 By Hr]
		*/
		virtual bool Init() = 0;
		
		virtual void BindFrameBuffer(const HrRenderFramePtr& pRenderFrameBuffer) = 0;
		virtual const HrRenderFramePtr& GetBindFrameBuffer() = 0;

		virtual void SetCurrentViewPort(const HrViewPortPtr& pViewPort) = 0;

		virtual void Render(const HrRenderTechniquePtr& pRenderTechnique, const HrRenderLayoutPtr& pRenderLayout) = 0;

		virtual void SwapChain() = 0;
		/**
		*	@Brief:  ¥›ªŸ‰÷»æ∆˜[10/28/2015 By Hr]
		*/
		virtual void ReleaseRenderEngine() = 0;

		//—ßœ∞≤‚ ‘‰÷»æ”√
		virtual bool StartRender() = 0;
	};
}

#endif




