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
#include "Asset/HrRenderEffect.h"
#include "Asset/HrRenderEffectParameter.h"
#include "Render/HrRenderTechnique.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrWindowModule.h"
#include "Kernel/HrResourceModule.h"
#include "Kernel/HrSceneModule.h"
#include "Scene/HrScene.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"

using namespace Hr;

//默认的FrameBuffer
const std::string HrRenderSystem::m_sc_strScreenFrameBufferKey ="ScreenFrameBufferKey";

HrRenderSystem::HrRenderSystem(HrRenderFactoryPtr& pRenderFactory)
{
	m_pRenderFactory = pRenderFactory;
	m_pRenderParameters = HrMakeUniquePtr<HrRenderFrameParameters>();
	m_pShadowMap = HrMakeSharedPtr<HrShadowMap>();

	CreateRender();
	//默认先创建屏幕渲染
	CreateScreenFrameBuffer(HrDirector::Instance()->GetWindowModule()->GetWindowWidth()
		, HrDirector::Instance()->GetWindowModule()->GetWindowHeight());

	//todo shadowmap 先创建一个2048 * 2048的深度图
	m_pShadowMap->CreateShadowTexture(2048, 2048);

	m_pDeferredRender = HrMakeSharedPtr<HrDeferredRender>();
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

const HrRenderFramePtr& HrRenderSystem::GetScreenFrameBuffer()
{
	return m_pScreenFrameBuffer;
}

void HrRenderSystem::BindScreenFrameBuffer()
{
	this->BindFrameBuffer(GetScreenFrameBuffer());
}

const HrRenderFramePtr& HrRenderSystem::GetBindFrameBuffer()
{
	return m_pRender->GetBindFrameBuffer();
}

void HrRenderSystem::CreateRender()
{
	m_pRender = m_pRenderFactory->CreateRender();
	m_pRender->Init();
}

void HrRenderSystem::CreateScreenFrameBuffer(uint32 nWidth, uint32 nHeight)
{
	m_pScreenFrameBuffer = m_pRenderFactory->CreateScreenRenderFrameBuffer(nWidth, nHeight);
	m_mapRenderFrames.insert(std::make_pair(m_sc_strScreenFrameBufferKey, m_pScreenFrameBuffer));
}

void HrRenderSystem::BindFrameBuffer(const HrRenderFramePtr& pRenderFrame)
{
	m_pRender->BindFrameBuffer(pRenderFrame);
}

void HrRenderSystem::ClearRenderTarget()
{
	GetBindFrameBuffer()->ClearTarget();
}

void HrRenderSystem::ClearDepthStencil()
{
	GetBindFrameBuffer()->ClearDepthStencil();
}

void HrRenderSystem::Present()
{
	GetBindFrameBuffer()->Present();
}

void HrRenderSystem::RenderSceneToGBuffers(const HrRenderQueuePtr& pRenderQueue, const HrSceneLightDataPtr& pLightData, const HrRenderFrameParametersPtr& pRenderFrameParam)
{
	//设置RenderTarget
	BindFrameBuffer(m_pDeferredRender->GetDeferredFrameBuffer());
	ClearRenderTarget();
	ClearDepthStencil();

	
	auto pEffMakeGBuffer = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("HrMakeGBuffer.json");
	auto pStandEff = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>();

	auto& mapAllViewPorts = m_pScreenFrameBuffer->GetAllViewPorts();
	for (auto& itemViewPort : mapAllViewPorts)
	{
		const HrViewPortPtr& pViewPort = itemViewPort.second;
		m_pRender->SetViewPort(pViewPort);
		pRenderFrameParam->SetCurrentCamera(pViewPort->GetCamera());

		const std::vector<HrRenderablePtr>& vecRenderables = pRenderQueue->GetRenderables();
		for (auto& iteRenderable : vecRenderables)
		{
			pRenderFrameParam->SetCurrentRenderable(iteRenderable);
			iteRenderable->SetRenderEffect(pEffMakeGBuffer);
			iteRenderable->Render();
		}
	}

	m_pRender->UnbindShader(nullptr);

	RenderGBuffers(pRenderFrameParam);
	//const HrRenderFramePtr& pBindFrameBuffer = m_pRender->GetBindFrameBuffer();
	//if (pBindFrameBuffer)
	//{
	//	auto mapAllViewPorts = pBindFrameBuffer->GetAllViewPorts();
	//	for (auto& itemViewPort : mapAllViewPorts)
	//	{
	//		const HrViewPortPtr& pViewPort = itemViewPort.second;
	//		m_pRender->SetViewPort(pViewPort);
	//		pRenderFrameParam->SetCurrentCamera(pViewPort->GetCamera());

	//		const std::vector<HrRenderablePtr>& vecRenderables = pRenderQueue->GetRenderables();
	//		for (auto& iteRenderable : vecRenderables)
	//		{
	//			pRenderFrameParam->SetCurrentRenderable(iteRenderable);
	//			iteRenderable->Render();
	//		}
	//	}
	//}
}

void HrRenderSystem::RenderGBuffers(const HrRenderFrameParametersPtr& pRenderFrameParam)
{
	this->BindScreenFrameBuffer();
	this->ClearRenderTarget();
	this->ClearDepthStencil();

	auto pEffMakeGBuffer = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("HrDeferredShading.json");
	auto& pScreenQuadRenderable = m_pDeferredRender->GetScreenQuadRenderable();
	auto& pSceneNode = m_pDeferredRender->GetSceneQuadNode();
	HrDirector::Instance()->GetSceneModule()->GetRunningScene()->AddNode(pSceneNode);
	auto& mapAllViewPorts = m_pRender->GetBindFrameBuffer()->GetAllViewPorts();
	for (auto& itemViewPort : mapAllViewPorts)
	{
		const HrViewPortPtr& pViewPort = itemViewPort.second;
		m_pRender->SetViewPort(pViewPort);
		pRenderFrameParam->SetCurrentCamera(pViewPort->GetCamera());
		pRenderFrameParam->SetCurrentRenderable(pScreenQuadRenderable);
		pScreenQuadRenderable->Render();
	}
	pSceneNode->RemoveFromParent();
}

void HrRenderSystem::RenderSceneToShadowMap(const HrRenderQueuePtr& pRenderQueue, const HrSceneLightDataPtr& pLightData, const HrRenderFrameParametersPtr& pRenderFrameParam)
{
	//设置RenderTarget
	m_pRender->BindFrameBuffer(m_pShadowMap->GetDepthStencilFrame());
	this->ClearRenderTarget();
	this->ClearDepthStencil();

	//1.设置ShadowMap视口
	m_pShadowMap->OnStartRenderFrame();

	HrCameraPtr pShadowMapCamera = m_pShadowMap->GetShadowMapCamera();
	//m_pRender->SetViewPort(pShadowMapCamera->GetViewPort());
	pRenderFrameParam->SetCurrentCamera(pShadowMapCamera);

	const HrLightPtr& pPointLight = pLightData->GetLight(HrLight::LT_POINT, 0);
	//Vector3 v3LookAt = pPointLight->GetDirection() + pPointLight->GetPosition();
	//todo 先随便写死角度
	pShadowMapCamera->ViewParams(pPointLight->GetPosition(), Vector3::Zero(), Vector3(1.0f, 0.0f, 0.0f));
	pShadowMapCamera->ProjectParams(HrMath::PIDIV2(), pShadowMapCamera->Aspect(), 0.3f, 1000.0f);

	auto pEffShadowMapDepth = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("HrShadowMapDepth.json");

	const std::vector<HrRenderablePtr>& vecRenderables = pRenderQueue->GetRenderables();
	for (auto& iteRenderable : vecRenderables)
	{
		pRenderFrameParam->SetCurrentRenderable(iteRenderable);
		iteRenderable->SetRenderEffect(pEffShadowMapDepth);
		iteRenderable->Render();
	}

	//重新设置回来
	this->BindScreenFrameBuffer();
	this->ClearRenderTarget();
	this->ClearDepthStencil();
}

void HrRenderSystem::RenderBasicRenderQueue(const HrRenderQueuePtr& pRenderQueue, const HrRenderFrameParametersPtr& pRenderFrameParam)
{
	const HrRenderFramePtr& pBindFrameBuffer = m_pRender->GetBindFrameBuffer();
	if (pBindFrameBuffer)
	{
		auto mapAllViewPorts = pBindFrameBuffer->GetAllViewPorts();
		for (auto& itemViewPort : mapAllViewPorts)
		{
			const HrViewPortPtr& pViewPort = itemViewPort.second;
			m_pRender->SetViewPort(pViewPort);
			pRenderFrameParam->SetCurrentCamera(pViewPort->GetCamera());

			//auto pEffShadowMapDepth = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("HrShadowMap.json");
			//HrRenderEffectParameterPtr pDiffuseTexParam = pEffShadowMapDepth->GetParameterByName("texShadowMap");
			//if (pDiffuseTexParam)
			//{
			//	HrTexturePtr pDepthTex = m_pShadowMap->GetDepthStencilFrame()->GetDepthStencil()->GetDepthStencilSRV();
			//	pDiffuseTexParam->operator = (pDepthTex.get());
			//}
			//HrRenderEffectParameterPtr pViewProjMatrix = pEffShadowMapDepth->GetParameterByName("point_view_proj_matrix");
			//if (pViewProjMatrix)
			//{
			//	*pViewProjMatrix = m_pShadowMap->GetShadowMapCamera()->GetViewProjMatrix();
			//}

			//auto pTech = pEffShadowMapDepth->GetTechniqueByIndex(0);

			//auto pTestEff = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("HrStandard.json");
			//auto pTestTech = pEffShadowMapDepth->GetTechniqueByIndex(0);

			const std::vector<HrRenderablePtr>& vecRenderables = pRenderQueue->GetRenderables();
			for (auto& iteRenderable : vecRenderables)
			{
				pRenderFrameParam->SetCurrentRenderable(iteRenderable);

				//auto pTTT = iteRenderable->GetRenderEffect()->GetTechniqueByIndex(0);
				//auto pTTT = iteRenderable->GetRenderTechnique();
				
				//先屏蔽掉阴影渲染
				//iteRenderable->SetRenderEffect(pEffShadowMapDepth);

				iteRenderable->Render();
			}
		}
	}
}

