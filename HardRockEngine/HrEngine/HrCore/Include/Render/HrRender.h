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
		*	@Param:
		*	@Return:
		*/
		virtual bool Init() = 0;
		
		virtual void SetRenderTarget(HrRenderTargetPtr& renderTarget) = 0;
		
		virtual void SetCurrentViewPort(HrViewPort* pViewPort) = 0;

		virtual void ClearRenderTargetView() = 0;
		
		virtual void ClearDepthStencilView() = 0;

		virtual void Render(HrRenderTechnique* pRenderTechnique, HrRenderLayout* pRenderLayout) = 0;

		virtual void SwapChain() = 0;
		/**
		*	@Brief:  ¥›ªŸ‰÷»æ∆˜[10/28/2015 By Hr]
		*	@Param:
		*	@Return:
		*/
		virtual void Release() = 0;

		//—ßœ∞≤‚ ‘‰÷»æ”√
		virtual bool StartRender() = 0;
	public:
		

	};
}

#endif




