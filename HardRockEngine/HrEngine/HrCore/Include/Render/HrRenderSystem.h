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

	private:
		void InitRender();
		void BindScreenFrameBuffer();
	private:
		HrRenderFactoryPtr m_pRenderFactory;

		HrRenderPtr m_pRender;
		HrRenderTargetPtr m_pRenderTarget;

		HrRenderFramePtr m_pScreenFrameBuffer;
	};
}


#endif
