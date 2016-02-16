#include "Scene/HrSceneManager.h"
#include "Scene/HrScene.h"
#include "Scene/HrSceneNode.h"
#include "Render/HrRenderQueue.h"
#include "HrUtilTools/Include/HrUtil.h"


using namespace Hr;

HrSceneManager::HrSceneManager()
{
	m_pShareRenderQueue = MakeSharedPtr<HrRenderQueue>();
}

HrSceneManager::~HrSceneManager()
{
}

void HrSceneManager::RunScene(const IScenePtr& pScene)
{
	m_pShareRunningScene = pScene;

	m_pShareRunningScene->OnEnter();
	m_pShareRunningScene->OnEnterDidFinish();
}

void HrSceneManager::UpdateScene()
{
	m_pShareRunningScene->Update();

	m_pShareRenderQueue->PrepareRenderQueue();
	m_pShareRunningScene->FillRenderQueue(m_pShareRenderQueue);
}

