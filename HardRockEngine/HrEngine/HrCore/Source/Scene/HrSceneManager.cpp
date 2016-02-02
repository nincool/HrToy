#include "Scene/HrSceneManager.h"
#include "Scene/HrScene.h"

using namespace Hr;


HrSceneManager::HrSceneManager()
{

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
