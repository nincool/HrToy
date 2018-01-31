#include "Scene/HrSceneManager.h"
#include "Scene/HrScene.h"
#include "Scene/HrEntityNode.h"
#include "Render/HrRender.h"
#include "Render/HrRenderQueue.h"
#include "Render/HrRenderable.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderFrameParameters.h"
#include "Render/HrRenderTarget.h"
#include "Render/HrCamera.h"
#include "Render/HrViewPort.h"
#include "Kernel/HrDirector.h"

#include "Render/HrRenderSystem.h"
#include "Kernel/HrCoreComponentRender.h"

#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrSceneManager::HrSceneManager()
{
	m_bSceneRunning = false;

	m_pRenderQueue = HrMakeSharedPtr<HrRenderQueue>();
	m_pRenderParameters = HrMakeUniquePtr<HrRenderFrameParameters>();

	m_pCurrentCamera = nullptr;
}

HrSceneManager::~HrSceneManager()
{
}

const HrScenePtr& HrSceneManager::GetRunningScene()
{
	return m_pRunningScene;
}

void HrSceneManager::RunScene(const HrScenePtr& pScene)
{
	if (m_pRunningScene)
	{
		m_pRunningScene->OnExit();
	}
	m_pRunningScene = pScene;

	m_pRunningScene->OnEnter();
	m_pRunningScene->OnEnterDidFinish();

	m_bSceneRunning = true;
}

void HrSceneManager::StopScene()
{
	if (m_pRunningScene)
	{
		m_pRunningScene->OnExit();
	}

	m_bSceneRunning = false;
}

void HrSceneManager::UpdateScene(float fDeltaTime)
{
	if (!CheckSceneRunning())
	{
		return;
	}
	m_pRunningScene->Update();
}

void HrSceneManager::RenderScene()
{
	if (!CheckSceneRunning())
	{
		return;
	}
	
	const HrCoreComponentRenderPtr& pRenderComponent = HrDirector::Instance()->GetRenderCoreComponent();
	
	pRenderComponent->OnRenderFrameBegin();

	m_pRenderQueue->PrepareRenderQueue();
	m_pRunningScene->FillRenderQueue(m_pRenderQueue);

	pRenderComponent->RenderBindFrameBuffer(m_pRenderQueue, m_pRenderParameters);
	pRenderComponent->Present();

	pRenderComponent->OnRenderFrameEnd();


	//pRenderComponent->RenderCurrentFrameBuffer();
	//const std::map<int, HrViewPortPtr>& mapViewPorts = pRenderTarget->GetViewPorts();
	//for (auto& itemViewPort : mapViewPorts)
	//{
	//	const HrViewPortPtr& pViewPort = itemViewPort.second;
	//	
	//}

	//std::map<int, HrViewPort*>& mapViewPorts = HrDirector::Instance()->GetRenderCoreComponent()->GetRenderSystem()->GetScreenRenderTarget()->GetViewPorts();
	//for (auto& itemViewPorts : mapViewPorts)
	//{
	//	HrViewPort* pViewPort = itemViewPorts.second;
	//	HrDirector::Instance()->GetRenderCoreComponent()->GetRenderSystem()->GetRender()->SetCurrentViewPort(pViewPort);

	//	//transfrom current camera
	//	//pViewPort->GetCamera()->GetAttachCameraNode()->UpdateNode();
	//	m_pRenderParameters->SetCurrentCamera(pViewPort->GetCamera().get());

	//	m_pRenderQueue->PrepareRenderQueue();
	//	m_pRunningScene->FillRenderQueue(m_pRenderQueue);

	//	FlushScene();
	//}

	//pRenderComponent->SwapChain();
}

//void HrSceneManager::FlushScene()
//{
//	HrRenderable* pRenderable = nullptr;
//	HrSceneNode* pSceneNode = nullptr;
//
//	std::unordered_map<HrRenderable*, HrSceneNode*>& mapRenderables = m_pRenderQueue->GetRenderables();
//	for (auto& itemMapRenderable : mapRenderables)
//	{
//		pRenderable = itemMapRenderable.first;
//		pSceneNode = itemMapRenderable.second;
//
//		pSceneNode->UpdateNode();
//		pSceneNode->UpdateRenderParamData(*(m_pRenderParameters.get()));

		//HrRenderLayout* pRenderLayout = pRenderable->GetRenderLayout();
		//HrRenderTechnique* pRenderTechnique = pRenderable->GetRenderTechnique();

		//HrDirector::Instance()->GetRenderCoreComponent()->GetRenderSystem()->GetRender()->Render(pRenderTechnique, pRenderLayout);
//	}
//}

void HrSceneManager::Destroy()
{
	StopScene();
}

bool HrSceneManager::CheckSceneRunning()
{
	return m_bSceneRunning;
}

