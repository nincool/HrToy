#include "Kernel/HrCoreComponentScene.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrCoreComponentEvent.h"
#include "Kernel/HrLog.h"
#include "Event/HrEvent.h"
#include "Scene/HrSceneManager.h"

using namespace Hr;

HrCoreComponentScene::HrCoreComponentScene(EnumSceneManagerType sceneManagerType)
{
	CreateSceneManager(sceneManagerType);

	m_pEventUpdateBegin = HrMakeSharedPtr<HrEventCustom>(HrEvent::scEventBeginUpdateScene);
	m_pEventUpdateEnd = HrMakeSharedPtr<HrEventCustom>(HrEvent::scEventEndUpdateScene);
}

HrCoreComponentScene::~HrCoreComponentScene()
{
	HRLOG("HrCoreComponentScene Destroy!");
}

bool HrCoreComponentScene::Update(float fDelta)
{
	HrDirector::Instance()->GetEventComponent()->DispatcherEvent(m_pEventUpdateBegin);

	m_pSceneManager->UpdateScene(fDelta);

	HrDirector::Instance()->GetEventComponent()->DispatcherEvent(m_pEventUpdateEnd);

	return true;
}

bool HrCoreComponentScene::CreateSceneManager(EnumSceneManagerType sceneManagerType)
{
	switch (sceneManagerType)
	{
	case HrCoreComponentScene::EnumSceneManagerType::SMT_NORMAL:
	{
		m_pSceneManager = HrMakeSharedPtr<HrSceneManager>();
		break;
	}
	default:

		return false;
	}

	return true;
}

void HrCoreComponentScene::RunScene(const HrScenePtr& pScene)
{
	m_pSceneManager->RunScene(pScene);
}

void HrCoreComponentScene::StopScene()
{
	m_pSceneManager->StopScene();
}

void HrCoreComponentScene::RenderScene()
{
	//todo
	m_pSceneManager->RenderScene();
}

void HrCoreComponentScene::Destroy()
{
	m_pSceneManager->Destroy();
}

const HrScenePtr& HrCoreComponentScene::GetRunningScene() const
{
	return m_pSceneManager->GetRunningScene();
}

