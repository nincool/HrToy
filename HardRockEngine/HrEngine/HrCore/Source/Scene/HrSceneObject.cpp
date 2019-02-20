#include "Scene/HrSceneObject.h"
#include "Scene/HrSceneObjectComponent.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrTransform.h"
#include "Scene/HrScene.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrRenderModule.h"
#include "Kernel/HrSceneModule.h"
#include "Render/HrCamera.h"

using namespace Hr;

HrSceneObject::HrSceneObject(HrSceneNode* pSceneNode)
{
	m_pContainerNode = pSceneNode;
}

HrSceneObject::~HrSceneObject()
{
}

void HrSceneObject::OnEnter()
{
	for (auto& item : m_mapComponents)
	{
		item.second->OnEnter();
	}

	AddCameraToScene();
	AddLightToScene();
}

void HrSceneObject::OnExist()
{
	for (auto& item : m_mapComponents)
	{
		item.second->OnExist();
	}
}

void HrSceneObject::Update(float fDelta)
{
}

void HrSceneObject::OnNodeTransformDirty(const HrTransformPtr& pTrans)
{
	for (auto& iteCom : m_mapComponents)
	{
		iteCom.second->UpdateTransform(pTrans);
	}
}

void HrSceneObject::AddComponent(const HrSceneObjectComponentPtr& pSceneObjComponent)
{
	if (pSceneObjComponent->IsMutex() && m_pSceneObjMutexCom)
	{
		TRE("Can't add mutex component again!");
		return;
	}
	m_pSceneObjMutexCom = pSceneObjComponent->IsMutex() ? pSceneObjComponent : nullptr;

	auto comType = pSceneObjComponent->GetComType();
	switch (comType)
	{
	case HrSceneObjectComponent::SCT_NORMAL:
		break;
	case HrSceneObjectComponent::SCT_CAMERA:
	{
		if (!m_pCachedCamera)
		{
			m_mapComponents[comType] = pSceneObjComponent;
			m_pCachedCamera = HrCheckPointerCast<HrCameraComponet>(pSceneObjComponent);
			break;
		}
		else
		{
			HRERROR("HrSceneObject::AddComponent Error! Can not add a camera again!");
		}
	}
	case HrSceneObjectComponent::SCT_LIGHT:
	{
		if (!m_pCachedLight)
		{
			m_mapComponents[comType] = pSceneObjComponent;
			m_pCachedLight = HrCheckPointerCast<HrLightComponent>(pSceneObjComponent);
		}
		else
		{
			HRERROR("HrSceneObject::AddComponent Error! Can not add a light again!");
		}
		break;
	}
	default:
	{
		if (m_mapComponents.find(comType) != m_mapComponents.end())
		{
			HRLOG("HrSceneObject::AddComponent Error! Type[%d]", comType);
			return;
		}
		m_mapComponents[comType] = pSceneObjComponent;
		break;
	}
	}
}

HrSceneObjectComponentPtr HrSceneObject::AddComponent(HrSceneObjectComponent::EnumSceneComponentType comType)
{
	auto iteCom = m_mapComponents.find(comType);
	if (iteCom != m_mapComponents.end())
	{
		return iteCom->second;
	}

	HrSceneObjectComponentPtr pSceneObjCom = nullptr;

	switch (comType)
	{
	case HrSceneObjectComponent::SCT_NORMAL:
		break;
	case HrSceneObjectComponent::SCT_CAMERA:
		pSceneObjCom = HrMakeSharedPtr<HrCameraComponet>("Camera", this);
		break;
	case HrSceneObjectComponent::SCT_LIGHT:
		break;
	case HrSceneObjectComponent::SCT_RENDERABLE:
		pSceneObjCom = HrMakeSharedPtr<HrRenderableComponent>("Renderable", this);
		break;
	case HrSceneObjectComponent::SCT_INSTANCEBATCH:
		pSceneObjCom = HrMakeSharedPtr<HrInstanceBatchComponent>("InstanceBatch", this);
		break;
	case HrSceneObjectComponent::SCT_INSTANCEOBJ:
		pSceneObjCom = HrMakeSharedPtr<HrInstanceObjectComponent>("InstanceObj", this);
		break;
	case HrSceneObjectComponent::SCT_TRACKBALLCAMERA:
		pSceneObjCom = HrMakeSharedPtr<HrTrackBallCameraController>("TrackBallCameraController", this);
		break;
	case HrSceneObjectComponent::SCT_COM_COUNT:
		break;
	default:
		break;
	}

	if (pSceneObjCom->IsMutex() && m_pSceneObjMutexCom)
	{
		TRE("Can't add mutex component again!");
		return nullptr;
	}

	if (!pSceneObjCom->InitComponent())
	{
		TRE("component construct failed");
		return nullptr;
	}

	if (m_pContainerNode->IsRunning())
		pSceneObjCom->OnEnter();

	m_mapComponents[comType] = pSceneObjCom;
	m_pSceneObjMutexCom = pSceneObjCom->IsMutex() ? pSceneObjCom : nullptr;

	switch (comType)
	{
	case HrSceneObjectComponent::SCT_CAMERA:
		m_pCachedCamera = HrCheckPointerCast<HrCameraComponet>(pSceneObjCom);
		break;
	case HrSceneObjectComponent::SCT_RENDERABLE:
		m_pCachedRenderable = HrCheckPointerCast<HrRenderableComponent>(pSceneObjCom);
		break;
	}

	return m_mapComponents[comType];
}

void HrSceneObject::AddCameraToScene()
{
	if (m_pCachedCamera)
	{
		HrDirector::Instance()->GetSceneModule()->GetRunningScene()->GetViewPortsData()->AddViewPort(m_pCachedCamera->GetViewPort());
	}
}

void HrSceneObject::AddLightToScene()
{
	if (m_pCachedLight)
	{
		HrDirector::Instance()->GetSceneModule()->GetRunningScene()->GetLightsData()->AddLight(m_pCachedLight->GetLight());
	}
}

HrSceneObjectComponentPtr HrSceneObject::GetComponent(HrSceneObjectComponent::EnumSceneComponentType comType)
{
	auto iteCom = m_mapComponents.find(comType);
	if (iteCom != m_mapComponents.end())
	{
		return iteCom->second;
	}

	return nullptr;
}

const HrSceneNode* HrSceneObject::GetSceneNode() const
{
	return m_pContainerNode;
}

const HrRenderableComponentPtr& HrSceneObject::GetRenderableComponent()
{
	return m_pCachedRenderable;
}

