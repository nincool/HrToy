#include "Scene/HrSceneManager.h"
#include "Scene/HrScene.h"
#include "Scene/HrSceneNode.h"
#include "Render/IRender.h"
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

	m_pShareRenderQueue = MakeSharedPtr<HrRenderQueue>();
	m_pUniqueRenderParameters = MakeUniquePtr<HrRenderFrameParameters>();

	m_pCurrentCamera = nullptr;
}

HrSceneManager::~HrSceneManager()
{
}

void HrSceneManager::RunScene(const IScenePtr& pScene)
{
	if (m_pShareRunningScene)
	{
		m_pShareRunningScene->OnExit();
		m_pShareRunningScene->ClearSceneNode();
	}
	m_pShareRunningScene = pScene;

	m_pShareRunningScene->OnEnter();
	m_pShareRunningScene->OnEnterDidFinish();

	m_bSceneRunning = true;
}

void HrSceneManager::StopScene()
{
	if (m_pShareRunningScene)
	{
		m_pShareRunningScene->OnExit();
		m_pShareRunningScene->ClearSceneNode();
	}

	m_bSceneRunning = false;
}

void HrSceneManager::UpdateScene()
{
	if (!CheckSceneRunning())
	{
		return;
	}
	m_pShareRunningScene->Update();
}

void HrSceneManager::RenderScene(IRenderTargetPtr& renderTarget)
{
	HrDirector::GetInstance().GetRenderer()->ClearRenderTargetView();
	HrDirector::GetInstance().GetRenderer()->ClearDepthStencilView();

	std::map<int, HrViewPort*>& mapViewPorts = renderTarget->GetViewPorts();
	for (auto& itemViewPorts : mapViewPorts)
	{
		HrViewPort* pViewPort = itemViewPorts.second;
		m_pCurrentCamera = pViewPort->GetCamera();
		HrDirector::GetInstance().GetRenderer()->SetCurrentViewPort(pViewPort);
		m_pUniqueRenderParameters->SetCurrentCamera(m_pCurrentCamera);

		m_pShareRenderQueue->PrepareRenderQueue();
		m_pShareRunningScene->FillRenderQueue(m_pShareRenderQueue);

		FlushScene();
	}
	HrDirector::GetInstance().GetRenderer()->SwapChain();
}

void HrSceneManager::FlushScene()
{
	if (!CheckSceneRunning())
	{
		return;
	}

	IRenderable* pRenderable = nullptr;
	HrSceneNode* pSceneNode = nullptr;

	std::unordered_map<IRenderable*, HrSceneNode*>& mapRenderables = m_pShareRenderQueue->GetRenderables();
	for (auto& itemMapRenderable : mapRenderables)
	{
		pRenderable = itemMapRenderable.first;
		pSceneNode = itemMapRenderable.second;

		m_pUniqueRenderParameters->SetCurrentRenderable(pRenderable);
		itemMapRenderable.second->UpdateNode(*(m_pUniqueRenderParameters.get()));

		IRenderable* pRenderable = itemMapRenderable.second->GetRenderable();
		IRenderLayout* pRenderLayout = pRenderable->GetRenderLayout();
		IRenderTechnique* pRenderTechnique = pRenderable->GetRenderTechnique();

		HrDirector::GetInstance().GetRenderer()->Render(pRenderTechnique, pRenderLayout);
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

