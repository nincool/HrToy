#include "Render/HrRenderProcessing.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrSceneModule.h"
#include "Kernel/HrRenderModule.h"
#include "Kernel/HrResourceModule.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrRenderEffectParameter.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrCamera.h"
#include "Render/HrViewPort.h"
#include "Render/HrRenderFrameParameters.h"
#include "Render/HrRenderSystem.h"
#include "Render/HrRenderable.h"
#include "Render/HrRenderFrame.h"
#include "Render/HrRenderCommand.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"
#include "Scene/HrSceneObjectComponent.h"

using namespace Hr;

HrRenderProcessing::HrRenderProcessing()
{
}

HrRenderProcessing::~HrRenderProcessing()
{
}

void HrRenderProcessing::VisitRenderable(const HrRenderablePtr& pRenderable)
{
}

void HrRenderProcessing::VisitRenderCommand(HrRenderCommand* pRenderCommand)
{
}

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////

HrForwardProcessing::HrForwardProcessing()
{
	m_pDefaultEffect = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>();
}

HrForwardProcessing::~HrForwardProcessing()
{

}

uint32 HrForwardProcessing::Run(HrRenderSystem* pRenderSystem)
{
	HrDirector::Instance()->GetSceneModule()->RenderVisibleObjects(this);

	return RPR_NEED_PRESENT;
}

void HrForwardProcessing::VisitRenderCommand(HrRenderCommand* pRenderCommand)
{
	auto& pRenderFrameParam = HrDirector::Instance()->GetSceneModule()->GetRenderFrameParameters();
	
	pRenderFrameParam->SetTransform(pRenderCommand->GetTransform());
	pRenderFrameParam->SetMaterial(pRenderCommand->GetMaterial());

	pRenderCommand->GetRenderEffect()->UpdateAutoEffectParams(pRenderFrameParam);
	
	pRenderCommand->OnRenderBegin();
	HrDirector::Instance()->GetRenderModule()->DoRender(pRenderCommand);
	pRenderCommand->OnRenderEnd();
}

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////

HrDeferredGBufferProcessing::HrDeferredGBufferProcessing()
{
	//m_pMakeGBuffers = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("HrMakeGBuffer.json");
}

HrDeferredGBufferProcessing::~HrDeferredGBufferProcessing()
{

}

uint32 HrDeferredGBufferProcessing::Run(HrRenderSystem* pRenderSystem)
{
	HrDeferredRenderSystem* pDeferredSystem = HrCheckPointerCast<HrDeferredRenderSystem>(pRenderSystem);
	auto& pRenderParam = HrDirector::Instance()->GetSceneModule()->GetRenderFrameParameters();
	auto& pCurViewPort = pRenderParam->GetViewPort();
	CreateGBuffers(pCurViewPort, pDeferredSystem);
	RenderSceneToGBuffers(pDeferredSystem);
	
	return RPR_NEED_PRESENT;
}

void HrDeferredGBufferProcessing::CreateGBuffers(const HrViewPortPtr& pViewPort, HrDeferredRenderSystem* pDeferredSystem)
{
	auto& pDeferredInfo = pViewPort->GetViewPortDeferredInfo();
	auto& pRenderFactory = HrDirector::Instance()->GetRenderModule()->GetRenderFactory();
	if (!pDeferredInfo->m_arrGBuffers[GBT_POSITION])
	{
		pDeferredInfo->m_arrGBuffers[GBT_POSITION] = pRenderFactory->CreateTexture2D(pViewPort->GetWidth()
			, pViewPort->GetHeight()
			, 1, 1, 0
			, HrTexture::EAH_GPU_READ | HrTexture::EAH_GPU_WRITE
			, HrTexture::TUF_TEX_RENDERTARGETVIEW | HrTexture::TUF_TEX_SHADERRESOURCEVIEW
			, EnumPixelFormat::PF_R32G32B32A32_FLOAT);
		pDeferredInfo->m_arrGBufferRenderTargets[GBT_POSITION] = pRenderFactory->CreateRenderTarget(pDeferredInfo->m_arrGBuffers[GBT_POSITION]);
	}
	pDeferredSystem->GetDeferredRenderFrame()->AttachRenderTarget(HrRenderFrame::RTL_0, pDeferredInfo->m_arrGBufferRenderTargets[GBT_POSITION]);

	if (!pDeferredInfo->m_arrGBuffers[GBT_NORMAL])
	{
		pDeferredInfo->m_arrGBuffers[GBT_NORMAL] = pRenderFactory->CreateTexture2D(pViewPort->GetWidth()
			, pViewPort->GetHeight()
			, 1, 1, 0
			, HrTexture::EAH_GPU_READ | HrTexture::EAH_GPU_WRITE
			, HrTexture::TUF_TEX_RENDERTARGETVIEW | HrTexture::TUF_TEX_SHADERRESOURCEVIEW
			, EnumPixelFormat::PF_R32G32B32A32_FLOAT);
		pDeferredInfo->m_arrGBufferRenderTargets[GBT_NORMAL] = pRenderFactory->CreateRenderTarget(pDeferredInfo->m_arrGBuffers[GBT_NORMAL]);
	}
	pDeferredSystem->GetDeferredRenderFrame()->AttachRenderTarget(HrRenderFrame::RTL_1, pDeferredInfo->m_arrGBufferRenderTargets[GBT_NORMAL]);

	if (!pDeferredInfo->m_arrGBuffers[GBT_ALBEDO])
	{
		pDeferredInfo->m_arrGBuffers[GBT_ALBEDO] = pRenderFactory->CreateTexture2D(pViewPort->GetWidth()
			, pViewPort->GetHeight()
			, 1, 1, 0
			, HrTexture::EAH_GPU_READ | HrTexture::EAH_GPU_WRITE
			, HrTexture::TUF_TEX_RENDERTARGETVIEW | HrTexture::TUF_TEX_SHADERRESOURCEVIEW
			, EnumPixelFormat::PF_R32G32B32A32_FLOAT);
		pDeferredInfo->m_arrGBufferRenderTargets[GBT_ALBEDO] = pRenderFactory->CreateRenderTarget(pDeferredInfo->m_arrGBuffers[GBT_ALBEDO]);
	}
	pDeferredSystem->GetDeferredRenderFrame()->AttachRenderTarget(HrRenderFrame::RTL_2, pDeferredInfo->m_arrGBufferRenderTargets[GBT_ALBEDO]);
}

void HrDeferredGBufferProcessing::RenderSceneToGBuffers(HrDeferredRenderSystem* pDeferredSystem)
{
	auto& pRenderModule = HrDirector::Instance()->GetRenderModule();
	pRenderModule->BindFrameBuffer(pDeferredSystem->GetDeferredRenderFrame());
	pRenderModule->ClearRenderFrame();

	HrDirector::Instance()->GetSceneModule()->RenderVisibleObjects(this);
}

void HrDeferredGBufferProcessing::VisitRenderable(const HrRenderablePtr& pRenderable)
{
	pRenderable->SetRenderEffect(m_pMakeGBuffers);

	//pRenderable->Render();
}

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////
HrFinalMappingProcessing::HrFinalMappingProcessing()
{
	//m_pFinalPresentEffect = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("HrDeferredShading.json");
}

HrFinalMappingProcessing::~HrFinalMappingProcessing()
{

}

uint32 HrFinalMappingProcessing::Run(HrRenderSystem* pRenderSystem)
{
	auto& pRenderModule = HrDirector::Instance()->GetRenderModule();
	pRenderModule->BindFrameBuffer(pRenderSystem->GetScreenFrameBuffer());
	pRenderModule->ClearRenderFrame();

	auto& pQuadRenderable = pRenderSystem->GetScreenQuadRenderable()->GetChildByIndex(0);
	pQuadRenderable->GetSceneObject()->GetRenderableComponent()->GetRenderable()->SetRenderEffect(m_pFinalPresentEffect);
	
	//HrDirector::Instance()->GetSceneModule()->GetRenderFrameParameters()->SetCurrentSceneNode(pQuadRenderable.get());
	auto& pViewPort = HrDirector::Instance()->GetSceneModule()->GetRenderFrameParameters()->GetViewPort();
	auto& pGBufferPosParam = m_pFinalPresentEffect->GetParameterByName("texGBufferPos");
	if (pGBufferPosParam)
		pGBufferPosParam->operator=(pViewPort->GetViewPortDeferredInfo()->m_arrGBuffers[GBT_POSITION].get());

	auto& pGBufferNormalParam = m_pFinalPresentEffect->GetParameterByName("texGBufferNormal");
	if (pGBufferNormalParam)
		pGBufferNormalParam->operator=(pViewPort->GetViewPortDeferredInfo()->m_arrGBuffers[GBT_NORMAL].get());

	auto& pGBufferAlbedoParam = m_pFinalPresentEffect->GetParameterByName("texGBufferAlbedo");
	if (pGBufferAlbedoParam)
		pGBufferAlbedoParam->operator=(pViewPort->GetViewPortDeferredInfo()->m_arrGBuffers[GBT_ALBEDO].get());

	//pQuadRenderable->GetSceneObject()->GetRenderableComponent()->GetRenderable()->Render();

	return RPR_NEED_PRESENT;
}

