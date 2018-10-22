#include "Kernel/HrRenderModule.h"
#include "Kernel/HrLog.h"
#include "Render/HrRenderSystem.h"
#include "Render/HrRenderTarget.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderFrame.h"
#include "Render/HrRender.h"

using namespace Hr;

HrRenderModule::HrRenderModule(const std::string& strRenderModule)
{
	this->CreateRenderFactory(strRenderModule);
}

HrRenderModule::~HrRenderModule()
{

}

bool HrRenderModule::InitComponent()
{
	CreateRenderSystem();

	//初始化默认渲染到屏幕
	m_pRenderSystem->BindScreenFrameBuffer();

	return true;
}

void HrRenderModule::BindFrameBuffer(const HrRenderFramePtr& pRenderFrame)
{
	m_pRenderSystem->BindFrameBuffer(pRenderFrame);
}

void HrRenderModule::OnRenderFrameBegin()
{
	ClearRenderFame();
}

void HrRenderModule::OnRenderFrameEnd()
{
}

void HrRenderModule::RenderDeferredFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrSceneLightDataPtr& pLightData, const HrRenderFrameParametersPtr& pRenderFrameParam)
{
	m_pRenderSystem->RenderSceneToGBuffers(pRenderQueue, pLightData, pRenderFrameParam);
	//m_pRenderSystem->RenderGBuffers(pRenderFrameParam);
}

void HrRenderModule::RenderShadowMapFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrSceneLightDataPtr& pLightData, const HrRenderFrameParametersPtr& pRenderFrameParam)
{
	m_pRenderSystem->RenderSceneToShadowMap(pRenderQueue, pLightData, pRenderFrameParam);
}

void HrRenderModule::RenderBindFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrRenderFrameParametersPtr& pRenderFrameParam)
{
	m_pRenderSystem->RenderBasicRenderQueue(pRenderQueue, pRenderFrameParam);
}

void HrRenderModule::ClearRenderFame()
{
	m_pRenderSystem->ClearRenderTarget();
	m_pRenderSystem->ClearDepthStencil();
}

void HrRenderModule::Present()
{
	m_pRenderSystem->Present();
}

bool HrRenderModule::CreateRenderFactory(const std::string& strRenderModule)
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

		return true;
	}

	return false;
}

const HrRenderFactoryPtr& HrRenderModule::GetRenderFactory() const
{
	return m_pRenderFactory;
}

void HrRenderModule::CreateRenderSystem()
{
	if (m_pRenderFactory && !m_pRenderSystem)
	{
		m_pRenderSystem = HrMakeSharedPtr<HrRenderSystem>(m_pRenderFactory);
	}
}

void HrRenderModule::AddViewPort(const HrViewPortPtr& pViewPort)
{
	m_pRenderSystem->GetBindFrameBuffer()->AddViewPort(pViewPort);
}

void HrRenderModule::DoRender(const HrRenderTechniquePtr& pRenderTechnique, const HrRenderLayoutPtr& pRenderLayout)
{
	m_pRenderSystem->GetRender()->Render(pRenderTechnique, pRenderLayout);
}

const HrRenderFramePtr& HrRenderModule::GetRenderFrameBuffer() const
{
	return m_pRenderSystem->GetScreenFrameBuffer();
}
