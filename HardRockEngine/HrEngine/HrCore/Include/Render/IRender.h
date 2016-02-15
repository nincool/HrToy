#ifndef _I_RENDER_H_
#define _I_RENDER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IDirector;
	class IRenderTechnique;
	class IRenderLayout;

	class IRender : public RenderSysAllocatedObject
	{
	public:
		virtual ~IRender(){};
		/**
		*	@Brief:  ¥¥Ω®‰÷»æ∆˜[10/28/2015 By Hr]
		*	@Param:
		*	@Return:
		*/
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
		virtual bool Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc) = 0;
#else
		virtual bool Init(unsigned int nWidth, unsigned int nHeight) = 0;
#endif

		/**
		*	@Brief:  ¥›ªŸ‰÷»æ∆˜[10/28/2015 By Hr]
		*	@Param:
		*	@Return:
		*/
		virtual void Release() = 0;



		//—ßœ∞≤‚ ‘‰÷»æ”√
		virtual bool StartRender() = 0;
	public:
		virtual void Render(IRenderTechnique* pRenderTechnique, IRenderLayout* pRenderLayout) = 0;

	};
}

#endif




