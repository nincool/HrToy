#include "Kernel/HrCoreComponentRender.h"
#include "Kernel/HrLog.h"
#include "Render/HrRenderSystem.h"
#include "Render/HrRenderTarget.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderFrame.h"
#include "Render/HrRender.h"

using namespace Hr;

HrCoreComponentRender::HrCoreComponentRender(const std::string& strRenderModule)
{
	this->CreateRenderFactory(strRenderModule);
}

HrCoreComponentRender::~HrCoreComponentRender()
{

}

bool HrCoreComponentRender::InitComponent()
{
	CreateRenderSystem();

	//��ʼ��Ĭ����Ⱦ����Ļ
	m_pRenderSystem->BindScreenFrameBuffer();

	return true;
}

void HrCoreComponentRender::BindFrameBuffer(const HrRenderFramePtr& pRenderFrame)
{
	m_pRenderSystem->BindFrameBuffer(pRenderFrame);
}

void HrCoreComponentRender::OnRenderFrameBegin()
{
	ClearRenderFame();
}

void HrCoreComponentRender::OnRenderFrameEnd()
{
}

void HrCoreComponentRender::RenderShadowMapFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrSceneLightDataPtr& pLightData, const HrRenderFrameParametersPtr& pRenderFrameParam)
{
	m_pRenderSystem->RenderSceneToShadowMap(pRenderQueue, pLightData, pRenderFrameParam);
}

void HrCoreComponentRender::RenderBindFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrRenderFrameParametersPtr& pRenderFrameParam)
{
	m_pRenderSystem->RenderBasicRenderQueue(pRenderQueue, pRenderFrameParam);
}

void HrCoreComponentRender::ClearRenderFame()
{
	m_pRenderSystem->ClearRenderTarget();
	m_pRenderSystem->ClearDepthStencil();
}

void HrCoreComponentRender::Present()
{
	m_pRenderSystem->Present();
}

bool HrCoreComponentRender::CreateRenderFactory(const std::string& strRenderModule)
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

const HrRenderFactoryPtr& HrCoreComponentRender::GetRenderFactory() const
{
	return m_pRenderFactory;
}

void HrCoreComponentRender::CreateRenderSystem()
{
	if (m_pRenderFactory && !m_pRenderSystem)
	{
		m_pRenderSystem = HrMakeSharedPtr<HrRenderSystem>(m_pRenderFactory);
	}
}

void HrCoreComponentRender::AddViewPort(const HrViewPortPtr& pViewPort)
{
	m_pRenderSystem->GetBindFrameBuffer()->AddViewPort(pViewPort);
}

void HrCoreComponentRender::DoRender(const HrRenderTechniquePtr& pRenderTechnique, const HrRenderLayoutPtr& pRenderLayout)
{
	m_pRenderSystem->GetRender()->Render(pRenderTechnique, pRenderLayout);
}

