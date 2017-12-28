#include "Kernel/HrSceneCoreComponent.h"
#include "Scene/HrSceneManager.h"

using namespace Hr;

HrSceneCoreComponent::HrSceneCoreComponent(EnumSceneManagerType sceneManagerType)
{
	CreateSceneManager(sceneManagerType);
}

HrSceneCoreComponent::~HrSceneCoreComponent()
{

}

bool HrSceneCoreComponent::Update(float fDelta)
{
	if (m_pSceneManager)
	{
		m_pSceneManager->UpdateScene(fDelta);
	}
	return true;
}

bool HrSceneCoreComponent::CreateSceneManager(EnumSceneManagerType sceneManagerType)
{
	switch (sceneManagerType)
	{
	case HrSceneCoreComponent::EnumSceneManagerType::SMT_NORMAL:
	{
		m_pSceneManager = HrMakeSharedPtr<HrSceneManager>();
		break;
	}
	default:

		return false;
	}

	return true;
}

void HrSceneCoreComponent::RunScene(const HrScenePtr& pScene)
{
	m_pSceneManager->RunScene(pScene);
}

void HrSceneCoreComponent::StopScene()
{
	m_pSceneManager->StopScene();
}

void HrSceneCoreComponent::RenderScene()
{
	m_pSceneManager->RenderScene();
}

void HrSceneCoreComponent::Destroy()
{
	m_pSceneManager->Destroy();
}

const HrScenePtr& HrSceneCoreComponent::GetRunningScene() const
{
	return m_pSceneManager->GetRunningScene();
}

