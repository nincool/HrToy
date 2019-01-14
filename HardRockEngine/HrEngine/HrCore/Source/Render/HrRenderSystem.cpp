#include "Render/HrRenderSystem.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderFrame.h"
#include "Render/HrRender.h"
#include "Render/HrViewPort.h"
#include "Render/HrRenderable.h"
#include "Render/HrRenderQueue.h"
#include "Render/HrRenderFrameParameters.h"
#include "Render/HrShadowMap.h"
#include "Render/HrCamera.h"
#include "Render/HrDepthStencil.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderProcessing.h"
#include "Render/HrRenderFactory.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrWindowModule.h"
#include "Kernel/HrResourceModule.h"
#include "Kernel/HrSceneModule.h"
#include "Kernel/HrRenderModule.h"
#include "Scene/HrScene.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrRenderEffectParameter.h"
#include "Asset/HrSceneObjectFactory.h"
#include "Config/HrContextConfig.h"

using namespace Hr;

HrRenderSystem::HrRenderSystem()
{
	m_pScreenFrameBuffer = HrDirector::Instance()->GetRenderModule()->GetRenderFactory()->CreateScreenRenderFrameBuffer(HrSingleTon<HrContextConfig>::Instance()->GetRTVWidth()
		, HrSingleTon<HrContextConfig>::Instance()->GetRTVHeight());
}

HrRenderSystem::~HrRenderSystem()
{
}

void HrRenderSystem::StartRenderProcess()
{
}

const HrSceneNodePtr& HrRenderSystem::GetScreenQuadRenderable()
{
	return m_pScreenQuad;
}

const HrRenderFramePtr& HrRenderSystem::GetScreenFrameBuffer()
{
	return m_pScreenFrameBuffer;
}

///////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////
HrForwardRenderSystem::HrForwardRenderSystem()
{
	BuildRenderProcesses();
}

HrForwardRenderSystem::~HrForwardRenderSystem()
{
}

void HrForwardRenderSystem::BuildRenderProcesses()
{
	m_lisRenderProcessing.push_back(HrMakeSharedPtr<HrForwardProcessing>());
}

void HrForwardRenderSystem::StartRenderProcess()
{
	auto& pRenderModule = HrDirector::Instance()->GetRenderModule();
	pRenderModule->BindFrameBuffer(m_pScreenFrameBuffer);
	pRenderModule->ClearRenderFrame();

	for (auto& pRenderProcessing : m_lisRenderProcessing)
	{
		uint32 nResult = pRenderProcessing->Run(this);
		if (nResult & HrRenderProcessing::RPR_NEED_PRESENT)
		{
			pRenderModule->Present();
		}
	}
}

///////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////

HrDeferredRenderSystem::HrDeferredRenderSystem()
{
	BuildRenderProcesses();

	m_pDeferredFrameBuffer = HrDirector::Instance()->GetRenderModule()->GetRenderFactory()->CreateRenderFrame(HrContextConfig::Instance()->GetRTVWidth()
		, HrContextConfig::Instance()->GetRTVHeight());
	
	m_pScreenQuad = HrSceneObjectFactory::Instance()->CreateQuadNodeP("FinalMapping", HrContextConfig::Instance()->GetRTVWidth(), HrContextConfig::Instance()->GetRTVHeight());
	auto& pRenderableQuad = m_pScreenQuad->GetChildByIndex(0);
	//auto& pDeferredShading = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("HrDeferredShading.json");
	//pRenderableQuad->GetSceneObject()->GetRenderableComponent()->GetRenderable()->SetRenderEffect(pDeferredShading);


}

HrDeferredRenderSystem::~HrDeferredRenderSystem()
{

}

void HrDeferredRenderSystem::StartRenderProcess()
{
	auto& pRenderModule = HrDirector::Instance()->GetRenderModule();
	for (auto& pRenderProcessing : m_lisRenderProcessing)
	{
		uint32 nResult = pRenderProcessing->Run(this);
		if (nResult & HrRenderProcessing::RPR_NEED_PRESENT)
		{
			pRenderModule->Present();
		}
	}
}

const HrRenderFramePtr& HrDeferredRenderSystem::GetDeferredRenderFrame()
{
	return m_pDeferredFrameBuffer;
}


void HrDeferredRenderSystem::BuildRenderProcesses()
{
	m_lisRenderProcessing.push_back(HrMakeSharedPtr<HrDeferredGBufferProcessing>());
	m_lisRenderProcessing.push_back(HrMakeSharedPtr<HrFinalMappingProcessing>());
}

