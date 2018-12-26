#include "Scene/HrSceneManager.h"
#include "Scene/HrScene.h"
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
#include "Kernel/HrLog.h"
#include "Render/HrRenderSystem.h"
#include "Kernel/HrRenderModule.h"

#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrSceneManager::HrSceneManager()
{
	m_bSceneRunning = false;
	m_bDirtyScene = false;

	m_pRenderQueue = HrMakeSharedPtr<HrRenderQueue>();
	m_pRenderQueueManager = HrMakeSharedPtr<HrRenderQueueManager>();
	m_pRenderParameters = HrMakeUniquePtr<HrRenderFrameParameters>();
}

HrSceneManager::~HrSceneManager()
{
	HRLOG("HrSceneManager Destroy!");
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
	m_pRunningScene->Update(fDeltaTime);
}

void HrSceneManager::RenderScene()
{
	if (!CheckSceneRunning())
	{
		return;
	}

	auto& pRenderModule = HrDirector::Instance()->GetRenderModule();
	auto& vecViewPorts = m_pRunningScene->GetViewPortsData()->GetAllViewPorts();
	for (auto& iteViewProt : vecViewPorts)
	{
		const HrViewPortPtr& pViewPort = iteViewProt.second;
		m_pRenderParameters->SetCurViewPort(pViewPort);

		//填充渲染队列
		FindRenderablesToQueue();
		//查找影响到的光源
		FindEffectLights();

		pRenderModule->RenderSceneView(pViewPort);
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

const HrRenderFrameParametersPtr& HrSceneManager::GetRenderFrameParamPtr()
{
	return m_pRenderParameters;
}

void HrSceneManager::RenderVisibleObjects(HrRenderProcessing* pProcessing)
{
	m_pRenderQueueManager->GetRenderQueue(HrRenderQueue::RQ_QUEUE_MAIN)->AcceptRenderProcessing(pProcessing);
}

void HrSceneManager::FindRenderablesToQueue()
{
}

void HrSceneManager::SetSceneDirty()
{
	m_bDirtyScene = true;
}

void HrSceneManager::FindEffectLights()
{
	m_pRenderParameters->SetLightsData(m_pRunningScene->GetLightsData());
}
