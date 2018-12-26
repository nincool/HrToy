#include "Kernel/HrSceneModule.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrEventSystemModule.h"
#include "Kernel/HrLog.h"
#include "Event/HrEvent.h"
#include "Scene/HrSceneManager.h"
#include "Scene/HrOctreeSceneManager.h"

using namespace Hr;

HrSceneModule::HrSceneModule()
{
	CreateSceneManager(HrSceneModule::EnumSceneManagerType::SMT_OCTREE);

	m_pEventUpdateBegin = HrMakeSharedPtr<HrEventCustom>(HrEvent::scEventBeginUpdateScene);
	m_pEventUpdateEnd = HrMakeSharedPtr<HrEventCustom>(HrEvent::scEventEndUpdateScene);
}

HrSceneModule::~HrSceneModule()
{
	HRLOG("HrSceneModule Destroy!");
}

bool HrSceneModule::Update(float fDelta)
{
	HrDirector::Instance()->GetEventSystemModule()->DispatcherEvent(m_pEventUpdateBegin);

	m_pSceneManager->UpdateScene(fDelta);

	HrDirector::Instance()->GetEventSystemModule()->DispatcherEvent(m_pEventUpdateEnd);

	return true;
}

bool HrSceneModule::CreateSceneManager(EnumSceneManagerType sceneManagerType)
{
	switch (sceneManagerType)
	{
	case HrSceneModule::EnumSceneManagerType::SMT_NORMAL:
	{
		m_pSceneManager = HrMakeSharedPtr<HrSceneManager>();
		break;
	}
	case HrSceneModule::EnumSceneManagerType::SMT_OCTREE:
	{
		m_pSceneManager = HrMakeSharedPtr<HrOctreeSceneManager>();
		break;
	}
	default:

		return false;
	}

	return true;
}

void HrSceneModule::RunScene(const HrScenePtr& pScene)
{
	m_pSceneManager->RunScene(pScene);
}

void HrSceneModule::StopScene()
{
	m_pSceneManager->StopScene();
}

void HrSceneModule::RenderScene()
{
	m_pSceneManager->RenderScene();
}

void HrSceneModule::Destroy()
{
	m_pSceneManager->Destroy();
}

const HrScenePtr& HrSceneModule::GetRunningScene() const
{
	return m_pSceneManager->GetRunningScene();
}

const HrRenderFrameParametersPtr& HrSceneModule::GetRenderFrameParameters()
{
	return m_pSceneManager->GetRenderFrameParamPtr();
}

void HrSceneModule::DirtyScene()
{
	m_pSceneManager->SetSceneDirty();
}

void HrSceneModule::FindRenderablesToQueue(const HrCameraPtr& pCamera)
{
	m_pSceneManager->FindRenderablesToQueue();
}

void HrSceneModule::RenderVisibleObjects(HrRenderProcessing* pProcessing)
{
	m_pSceneManager->RenderVisibleObjects(pProcessing);
}

