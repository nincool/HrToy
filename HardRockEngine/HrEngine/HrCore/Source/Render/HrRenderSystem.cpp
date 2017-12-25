#include "HrCore/Include/Render/HrRenderSystem.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderFactory.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"

using namespace Hr;

HrRenderSystem::HrRenderSystem(HrRenderFactoryPtr& pRenderFactory)
{
	m_pRenderFactory = pRenderFactory;

	m_pRender = m_pRenderFactory->CreateRender();
	
}

HrRenderSystem::~HrRenderSystem()
{

}

const HrRenderFactoryPtr& HrRenderSystem::GetRenderFactory()
{
	return m_pRenderFactory;
}

const HrRenderPtr& HrRenderSystem::GetRender()
{
	return m_pRender;
}



