#include "Kernel/HrRenderModule.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrSceneModule.h"
#include "Config/HrContextConfig.h"
#include "Render/HrRenderSystem.h"
#include "Render/HrRenderTarget.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderFrame.h"
#include "Render/HrRender.h"
#include "Render/HrRenderable.h"
#include "Render/HrViewPort.h"
#include "Render/HrCamera.h"
#include "Render/HrRenderFrameParameters.h"
#include "Scene/HrScene.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"
#include "Scene/HrSceneObjectComponent.h"


using namespace Hr;

HrRenderModule::HrRenderModule(const std::string& strRenderModule)
{
	CreateRenderFactory(strRenderModule);
	m_pRender = m_pRenderFactory->CreateRender();
}

HrRenderModule::~HrRenderModule()
{

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

bool HrRenderModule::InitComponent()
{
	m_pForwardRenderSystem = HrMakeSharedPtr<HrForwardRenderSystem>();
	m_pDeferredRenderSystem = HrMakeSharedPtr<HrDeferredRenderSystem>();

	return true;
}

const HrRenderSystemPtr& HrRenderModule::GetCurRenderSystem() const
{
	return m_pCurRenderSystem;
}

void HrRenderModule::BindFrameBuffer(const HrRenderFramePtr& pRenderFrame)
{
	if (m_pCurFrameBuffer != pRenderFrame)
	{
		m_pCurFrameBuffer = pRenderFrame;
		m_pRender->BindFrameBuffer(pRenderFrame);
	}
}

void HrRenderModule::ClearRenderFrame()
{
	m_pCurFrameBuffer->ClearTarget();
	m_pCurFrameBuffer->ClearDepthStencil();
}

void HrRenderModule::RenderSceneView(const HrViewPortPtr& pViewPort)
{
	m_pRender->SetViewPort(pViewPort);

	const HrCameraPtr& pCamera = pViewPort->GetCamera();
	RenderFrameForward();
	
	//RenderFrameDeferred();

	//switch (pCamera->GetRenderPath())
	//{
	//case RP_FORWARD:
	//	RenderFrameForward();
	//	break;
	//case RP_DEFERRED:
	//	RenderFrameDeferred();
	//	break;
	//default:
	//	break;
	//}
}

void HrRenderModule::RenderFrameForward()
{
	m_pCurRenderSystem = m_pForwardRenderSystem;
	m_pForwardRenderSystem->StartRenderProcess();
}

void HrRenderModule::RenderFrameDeferred()
{
	m_pCurRenderSystem = m_pDeferredRenderSystem;
	m_pDeferredRenderSystem->StartRenderProcess();
}

void HrRenderModule::Present()
{
	m_pCurFrameBuffer->Present();
}

void HrRenderModule::DoRender(const HrRenderTechniquePtr& pRenderTechnique, const HrRenderLayoutPtr& pRenderLayout)
{
	m_pRender->Render(pRenderTechnique, pRenderLayout);
}

void HrRenderModule::DoRender(HrRenderCommand* pCommand)
{
	m_pRender->DoRender(pCommand);
}






void HrRenderModule::RenderDeferredFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrSceneLightDataPtr& pLightData, const HrRenderFrameParametersPtr& pRenderFrameParam)
{
	//m_pRenderSystem->RenderSceneToGBuffers(pRenderQueue, pLightData, pRenderFrameParam);
	//m_pRenderSystem->RenderGBuffers(pRenderFrameParam);
}

void HrRenderModule::RenderShadowMapFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrSceneLightDataPtr& pLightData, const HrRenderFrameParametersPtr& pRenderFrameParam)
{
	//m_pRenderSystem->RenderSceneToShadowMap(pRenderQueue, pLightData, pRenderFrameParam);
}

void HrRenderModule::RenderBindFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrRenderFrameParametersPtr& pRenderFrameParam)
{
	//m_pRenderSystem->RenderBasicRenderQueue(pRenderQueue, pRenderFrameParam);
}
//if (pBindFrameBuffer)
//{
//	auto mapAllViewPorts = pBindFrameBuffer->GetAllViewPorts();
//	for (auto& itemViewPort : mapAllViewPorts)
//	{
//		const HrViewPortPtr& pViewPort = itemViewPort.second;
//		m_pRender->SetViewPort(pViewPort);
//		pRenderFrameParam->SetCurrentCamera(pViewPort->GetCamera());
//
//		//auto pEffShadowMapDepth = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("HrShadowMap.json");
//		//HrRenderEffectParameterPtr pDiffuseTexParam = pEffShadowMapDepth->GetParameterByName("texShadowMap");
//		//if (pDiffuseTexParam)
//		//{
//		//	HrTexturePtr pDepthTex = m_pShadowMap->GetDepthStencilFrame()->GetDepthStencil()->GetDepthStencilSRV();
//		//	pDiffuseTexParam->operator = (pDepthTex.get());
//		//}
//		//HrRenderEffectParameterPtr pViewProjMatrix = pEffShadowMapDepth->GetParameterByName("point_view_proj_matrix");
//		//if (pViewProjMatrix)
//		//{
//		//	*pViewProjMatrix = m_pShadowMap->GetShadowMapCamera()->GetViewProjMatrix();
//		//}
//
//		//auto pTech = pEffShadowMapDepth->GetTechniqueByIndex(0);
//
//		//auto pTestEff = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("HrStandard.json");
//		//auto pTestTech = pEffShadowMapDepth->GetTechniqueByIndex(0);
//
//		const std::vector<HrRenderablePtr>& vecRenderables = pRenderQueue->GetRenderables();
//		for (auto& iteRenderable : vecRenderables)
//		{
//			pRenderFrameParam->SetCurrentRenderable(iteRenderable);
//
//			//auto pTTT = iteRenderable->GetRenderEffect()->GetTechniqueByIndex(0);
//			//auto pTTT = iteRenderable->GetRenderTechnique();
//
//			//�����ε���Ӱ��Ⱦ
//			//iteRenderable->SetRenderEffect(pEffShadowMapDepth);
//
//			iteRenderable->Render();
//		}
//	}
//}
void HrRenderModule::RenderBindFrameBuffer()
{
	//const HrSceneModulePtr& pSceneModule = HrDirector::Instance()->GetSceneModule();
	//const HrRenderFramePtr& pRenderFrame = m_pRenderSystem->GetBindFrameBuffer();
	//auto& mapViewPorts = pRenderFrame->GetAllViewPorts();
	//for (auto& itemViewPort : mapViewPorts)
	//{
	//	const HrViewPortPtr& pViewPort = itemViewPort.second;
		//todo m_pRenderSystem->SetViewPort();
		//todo Camera
	//	const HrCameraPtr& pCamera = pViewPort->GetCamera();

		//�����Ⱦ����
		//pSceneModule->FillRenderQueue();
	//}
}


//void HrRenderModule::CreateRenderSystem()
//{
//	if (m_pRenderFactory && !m_pRenderSystem)
//	{
//		m_pRenderSystem = HrMakeSharedPtr<HrRenderSystem>(m_pRenderFactory);
//	}
//
//
//}

void HrRenderModule::AddViewPort(const HrViewPortPtr& pViewPort)
{
	//m_pRenderSystem->GetBindFrameBuffer()->AddViewPort(pViewPort);
}



const HrRenderFramePtr& HrRenderModule::GetRenderFrameBuffer() const
{
	return m_pCurFrameBuffer;
}

//void HrRenderModule::SetViewPort(const HrViewPortPtr& pViewPort)
//{
//	m_pRenderSystem->SetViewPort(pViewPort);
//}
//
