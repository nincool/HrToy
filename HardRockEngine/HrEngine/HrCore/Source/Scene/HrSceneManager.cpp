#include "Scene/HrSceneManager.h"
#include "Scene/HrScene.h"
#include "Scene/HrSceneNode.h"
#include "Render/HrRender.h"
#include "Render/HrRenderQueue.h"
#include "Render/HrRenderable.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderFrameParameters.h"
#include "Render/HrRenderTarget.h"
#include "Render/HrCamera.h"
#include "Render/HrViewPort.h"
#include "HrDirector.h"
#include "HrUtilTools/Include/HrUtil.h"


using namespace Hr;

HrSceneManager::HrSceneManager()
{
	m_bSceneRunning = false;

	m_pRenderQueue = MakeSharedPtr<HrRenderQueue>();
	m_pRenderParameters = MakeUniquePtr<HrRenderFrameParameters>();

	m_pCurrentCamera = nullptr;
}

HrSceneManager::~HrSceneManager()
{
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

void HrSceneManager::UpdateScene()
{
	if (!CheckSceneRunning())
	{
		return;
	}
	m_pRunningScene->Update();
}

void HrSceneManager::RenderScene(HrRenderTargetPtr& renderTarget)
{
	HrDirector::Instance()->GetRenderEngine()->ClearRenderTargetView();
	HrDirector::Instance()->GetRenderEngine()->ClearDepthStencilView();

	std::map<int, HrViewPort*>& mapViewPorts = renderTarget->GetViewPorts();
	for (auto& itemViewPorts : mapViewPorts)
	{
		HrViewPort* pViewPort = itemViewPorts.second;
		m_pCurrentCamera = pViewPort->GetCamera();
		HrDirector::Instance()->GetRenderEngine()->SetCurrentViewPort(pViewPort);
		m_pRenderParameters->SetCurrentCamera(m_pCurrentCamera);

		m_pRenderQueue->PrepareRenderQueue();
		m_pRunningScene->FillRenderQueue(m_pRenderQueue);

		FlushScene();
	}
	HrDirector::Instance()->GetRenderEngine()->SwapChain();
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

		m_pRenderParameters->SetCurrentRenderable(pRenderable);
		pSceneNode->UpdateNode(*(m_pRenderParameters.get()));

		HrRenderable* pRenderable = pSceneNode->GetRenderable();
		HrRenderLayout* pRenderLayout = pRenderable->GetRenderLayout();
		HrRenderTechnique* pRenderTechnique = pRenderable->GetRenderTechnique();

		HrDirector::Instance()->GetRenderEngine()->Render(pRenderTechnique, pRenderLayout);
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

