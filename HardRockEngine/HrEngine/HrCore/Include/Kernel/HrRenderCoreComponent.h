#ifndef _HR_HRRENDERCORECOMPONENT_H_
#define _HR_HRRENDERCORECOMPONENT_H_

#include "HrCore/Include/Kernel/HrCoreComponent.h"

namespace Hr
{
	class HR_CORE_API HrRenderCoreComponent : public HrCoreComponent
	{
	public:
		HrRenderCoreComponent(const std::string& strRenderModule);
		~HrRenderCoreComponent();

		virtual bool InitComponent() override;

		void BindFrameBuffer(const HrRenderFramePtr& pRenderFrame);

		void OnRenderFrameBegin();
		void OnRenderFrameEnd();

		void SwapChain();

		//todo ¡Ÿ ±
		const HrRenderSystemPtr& GetRenderSystem()
		{
			return m_pRenderSystem;
		}

	private:
		void GetRenderFactory(const std::string& strRenderModule);

		void CreateRenderSystem();
		
		void ClearRenderFame();
	protected:
		std::unique_ptr<HrModuleLoader> m_pRenderModuleLoader;
		HrRenderFactoryPtr m_pRenderFactory;
		HrRenderSystemPtr m_pRenderSystem;
	};
}

#endif
