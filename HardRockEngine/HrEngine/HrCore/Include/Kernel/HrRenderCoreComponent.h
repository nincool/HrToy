#ifndef _HR_HRRENDERCORECOMPONENT_H_
#define _HR_HRRENDERCORECOMPONENT_H_

#include "HrCore/Include/Kernel/HrCoreComponent.h"

namespace Hr
{
	class HrRenderCoreComponent : public HrCoreComponent
	{
	public:
		HrRenderCoreComponent(const std::string& strRenderModule);
		~HrRenderCoreComponent();

	public:

	private:
		void GetRenderFactory(const std::string& strRenderModule);

		void CreateRenderSystem();
	protected:
		std::unique_ptr<HrModuleLoader> m_pRenderModuleLoader;
		HrRenderFactoryPtr m_pRenderFactory;
		HrRenderSystemPtr m_pRenderSystem;
	};
}

#endif
