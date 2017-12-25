#ifndef _HR_RENDERSYSTEM_H_
#define _HR_RENDERSYSTEM_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrRenderSystem
	{
	public:
		HrRenderSystem(HrRenderFactoryPtr& pRenderFactory);
		virtual ~HrRenderSystem();

		const HrRenderFactoryPtr& GetRenderFactory();
		const HrRenderPtr& GetRender();

	private:
		HrRenderFactoryPtr m_pRenderFactory;

		HrRenderPtr m_pRender;
		HrRenderTargetPtr m_pRenderTarget;

	};
}


#endif
