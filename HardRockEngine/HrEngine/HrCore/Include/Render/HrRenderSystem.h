#ifndef _HR_RENDERSYSTEM_H_
#define _HR_RENDERSYSTEM_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrRenderSystem
	{
	public:
		HrRenderSystem(HrRenderFactoryPtr& pRenderFactory);
		virtual ~HrRenderSystem();

		void InitRenderSystem();

		const HrRenderFactoryPtr& GetRenderFactory();
		const HrRenderPtr& GetRender();
		const HrRenderTargetPtr& GetRenderTarget();
		const HrRenderFramePtr& GetScreenFrameBuffer();

		void SetCurrentFrameBuffer(const HrRenderFramePtr& pRenderFrame);
		/**
		 @Comment: 这里不能返回引用，因为函数内也存在临时变量 [12/29/2017 By Hr]
		*/
		HrRenderFramePtr GetCurrentFrameBuffer();
		
		void ClearRenderTarget();
		void ClearDepthStencil();

		void SwapChain();
	private:
		void InitRender();
		void BindScreenFrameBuffer();
	private:
		HrRenderFactoryPtr m_pRenderFactory;

		HrRenderPtr m_pRender;
		HrRenderTargetPtr m_pRenderTarget;

		//主适配器的渲染帧
		HrRenderFramePtr m_pScreenFrameBuffer;
	};
}


#endif
