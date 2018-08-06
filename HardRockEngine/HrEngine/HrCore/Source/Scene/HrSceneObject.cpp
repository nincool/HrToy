#include "Scene/HrSceneObject.h"
#include "Scene/HrSceneObjectComponent.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrTransform.h"
#include "Scene/HrScene.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrCoreComponentRender.h"
#include "Kernel/HrCoreComponentScene.h"
#include "Render/HrCamera.h"

using namespace Hr;

HrSceneObject::HrSceneObject()
{
}

HrSceneObject::~HrSceneObject()
{
}

void HrSceneObject::AttachSceneNode(const HrSceneNodePtr& pSceneNode)
{
	m_pContainerNode = pSceneNode;
}

void HrSceneObject::OnEnter()
{
	for (auto& item : m_mapComponents)
	{
		item.second->OnEnter();
	}

	AddCameraToScene();
	
	if (m_pCachedLight)
	{
		AddLightToScene(m_pCachedLight->GetLight());
	}
}

void HrSceneObject::OnExist()
{
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
		pSceneObjCom = HrMakeSharedPtr<HrCameraComponet>("Camera", shared_from_this());
		break;
	case HrSceneObjectComponent::SCT_LIGHT:
		break;
	case HrSceneObjectComponent::SCT_RENDERABLE:
		pSceneObjCom = HrMakeSharedPtr<HrRenderableComponent>("Renderable", shared_from_this());
		break;
	case HrSceneObjectComponent::SCT_INSTANCEBATCH:
		pSceneObjCom = HrMakeSharedPtr<HrInstanceBatchComponent>("InstanceBatch", shared_from_this());
		break;
	case HrSceneObjectComponent::SCT_INSTANCEOBJ:
		pSceneObjCom = HrMakeSharedPtr<HrInstanceObjectComponent>("InstanceObj", shared_from_this());
		break;
	case HrSceneObjectComponent::SCT_TRACKBALLCAMERA:
		pSceneObjCom = HrMakeSharedPtr<HrTrackBallCameraController>("TrackBallCameraController", shared_from_this());
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

	if (!m_pContainerNode.expired())
	{
		if (m_pContainerNode.lock()->IsRunning())
			pSceneObjCom->OnEnter();
	}

	m_mapComponents[comType] = pSceneObjCom;
	m_pSceneObjMutexCom = pSceneObjCom->IsMutex() ? pSceneObjCom : nullptr;

	switch (comType)
	{
	case HrSceneObjectComponent::SCT_CAMERA:
		m_pCachedCamera = HrCheckPointerCast<HrCameraComponet>(pSceneObjCom);
		break;
	}

	return m_mapComponents[comType];
}

void HrSceneObject::AddCameraToScene()
{
	if (m_pCachedCamera)
		HrDirector::Instance()->GetRenderComponent()->AddViewPort(m_pCachedCamera->GetViewPort());
}

void HrSceneObject::AddLightToScene(const HrLightPtr& pLight)
{
	if (!m_pContainerNode.expired())
	{
		HrSceneNodePtr pSceneNode = m_pContainerNode.lock();
		if (pSceneNode->GetEnable())
		{
			HrDirector::Instance()->GetSceneComponent()->GetRunningScene()->GetLightsData()->AddLight(pLight);
		}
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

HrSceneNodePtr HrSceneObject::GetSceneNode()
{
	return m_pContainerNode.lock();
}

