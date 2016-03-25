#ifndef _I_RENDER_H_
#define _I_RENDER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IRender : public RenderSysAllocatedObject
	{
	public:
		virtual ~IRender(){};
		/**
		*	@Brief:  ¥¥Ω®‰÷»æ∆˜[10/28/2015 By Hr]
		*	@Param:
		*	@Return:
		*/
		virtual bool Init() = 0;
		virtual void SetRenderTarget(IRenderTargetPtr& renderTarget) = 0;
		virtual void SetCurrentViewPort(HrViewPort* pViewPort) = 0;

		virtual void ClearRenderTargetView() = 0;
		virtual void ClearDepthStencilView() = 0;

		virtual void Render(IRenderTechnique* pRenderTechnique, IRenderLayout* pRenderLayout) = 0;

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




