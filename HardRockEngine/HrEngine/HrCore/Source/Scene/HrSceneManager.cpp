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
#include "Kernel/HrCoreComponentRender.h"

#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrSceneManager::HrSceneManager()
{
	m_bSceneRunning = false;

	m_pRenderQueue = HrMakeSharedPtr<HrRenderQueue>();
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

	//设置灯光数据
	m_pRenderParameters->SetLightsData(m_pRunningScene->GetLightsData());

	//准备渲染队列
	m_pRenderQueue->PrepareRenderQueue();
	m_pRunningScene->FillRenderQueue(m_pRenderQueue);

	//渲染
	pRenderComponent->RenderBindFrameBuffer(m_pRenderQueue, m_pRenderParameters);
	pRenderComponent->Present();

	pRenderComponent->OnRenderFrameEnd();
}

void HrSceneManager::Destroy()
{
	StopScene();
}

bool HrSceneManager::CheckSceneRunning()
{
	return m_bSceneRunning;
}

