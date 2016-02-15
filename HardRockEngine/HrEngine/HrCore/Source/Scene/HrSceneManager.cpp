#include "Scene/HrSceneManager.h"
#include "Scene/HrScene.h"
#include "Scene/HrSceneNode.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrSceneManager::HrSceneManager()
{
	m_pShareRootNode = MakeSharedPtr<HrSceneNode>();
}

HrSceneManager::~HrSceneManager()
{
}

const ISceneNodePtr& HrSceneManager::GetRootNode()
{
	return m_pShareRootNode;
}

void HrSceneManager::RunScene(const IScenePtr& pScene)
{
	m_pShareRunningScene = pScene;

	m_pShareRunningScene->OnEnter();
	m_pShareRunningScene->OnEnterDidFinish();
}


