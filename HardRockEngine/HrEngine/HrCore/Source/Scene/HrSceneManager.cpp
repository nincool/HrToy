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
#include "Kernel/HrRenderCoreComponent.h"

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

void HrSceneManager::UpdateScene(float fDelta)
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
	
	HrDirector::Instance()->GetRenderCoreComponent()->GetRenderSystem()->GetRender()->ClearRenderTargetView();
	HrDirector::Instance()->GetRenderCoreComponent()->GetRenderSystem()->GetRender()->ClearDepthStencilView();
	
	//HrDirector::Instance()->GetRenderCoreComponent()->GetRenderSystem()->GetRenderTarget()->

	//Lights
	m_pRenderParameters->SetCurrentScene(m_pRunningScene);

	std::map<int, HrViewPort*>& mapViewPorts = HrDirector::Instance()->GetRenderCoreComponent()->GetRenderSystem()->GetRenderTarget()->GetViewPorts();
	for (auto& itemViewPorts : mapViewPorts)
	{
		HrViewPort* pViewPort = itemViewPorts.second;
		HrDirector::Instance()->GetRenderCoreComponent()->GetRenderSystem()->GetRender()->SetCurrentViewPort(pViewPort);

		//transfrom current camera
		pViewPort->GetCamera()->GetAttachCameraNode()->UpdateNode();
		m_pRenderParameters->SetCurrentCamera(pViewPort->GetCamera());

		m_pRenderQueue->PrepareRenderQueue();
		m_pRunningScene->FillRenderQueue(m_pRenderQueue);

		FlushScene();
	}

	//todo
	HrDirector::Instance()->GetRenderCoreComponent()->GetRenderSystem()->GetRender()->SwapChain();
}

void HrSceneManager::FlushScene()
{
	if (!CheckSceneRunning())
	{
		return;
	}

	HrRenderable* pRenderable = nullptr;
	HrSceneNode* pSceneNode = nullptr;

	std::unordered_map<HrRenderable*, HrSceneNode*>& mapRenderables = m_pRenderQueue->GetRenderables();
	for (auto& itemMapRenderable : mapRenderables)
	{
		pRenderable = itemMapRenderable.first;
		pSceneNode = itemMapRenderable.second;

		pSceneNode->UpdateNode();
		pSceneNode->UpdateRenderParamData(*(m_pRenderParameters.get()));

		HrRenderLayout* pRenderLayout = pRenderable->GetRenderLayout();
		HrRenderTechnique* pRenderTechnique = pRenderable->GetRenderTechnique();

		HrDirector::Instance()->GetRenderCoreComponent()->GetRenderSystem()->GetRender()->Render(pRenderTechnique, pRenderLayout);
	}
}

void HrSceneManager::Destroy()
{
	StopScene();
}

bool HrSceneManager::CheckSceneRunning()
{
	return m_bSceneRunning;
}

