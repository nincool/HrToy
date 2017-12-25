#include "Kernel/HrRenderCoreComponent.h"
#include "Kernel/HrLog.h"
#include "Render/HrRenderSystem.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderFactory.h"

using namespace Hr;

HrRenderCoreComponent::HrRenderCoreComponent(const std::string& strRenderModule)
{
	this->GetRenderFactory(strRenderModule);
}

HrRenderCoreComponent::~HrRenderCoreComponent()
{

}

void HrRenderCoreComponent::GetRenderFactory(const std::string& strRenderModule)
{
	m_pRenderModuleLoader = HrMakeUniquePtr<HrModuleLoader>(strRenderModule);
	if (m_pRenderModuleLoader->HrLoadModule())
	{
		typedef void(*RENDER_INIT_FUNC)(HrRenderFactoryPtr& ptr);
		RENDER_INIT_FUNC func = static_cast<RENDER_INIT_FUNC>(m_pRenderModuleLoader->GetProcAddress(std::string("HrModuleInitialize")));
		if (func)
		{
			func(m_pRenderFactory);
		}

		CreateRenderSystem();
	}
}

void HrRenderCoreComponent::CreateRenderSystem()
{
	if (m_pRenderFactory)
	{
		m_pRenderSystem = HrMakeSharedPtr<HrRenderSystem>(m_pRenderFactory);
	}
}
