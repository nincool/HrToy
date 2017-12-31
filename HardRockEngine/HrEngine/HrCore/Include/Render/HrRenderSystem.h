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
		 @Comment: ���ﲻ�ܷ������ã���Ϊ������Ҳ������ʱ���� [12/29/2017 By Hr]
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

		//������������Ⱦ֡
		HrRenderFramePtr m_pScreenFrameBuffer;
	};
}


#endif
