#include "Scene/HrSceneObject.h"
#include "Scene/HrSceneObjectComponent.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrTransform.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrCoreComponentRender.h"
#include "Render/HrCamera.h"

using namespace Hr;

HrSceneObject::HrSceneObject()
{
}


HrSceneObject::HrSceneObject(const HrRenderablePtr& pRenderable)
{
	m_pRenderable = pRenderable;
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
	for (auto& iteCamera : m_lisCameras)
	{
		AddCameraToScene(iteCamera);
	}
}

void HrSceneObject::OnExist()
{
}

void HrSceneObject::Update(float fDelta, const HrTransformPtr& pTrans)
{
	if (pTrans->GetTransformDirty())
	{
		for (auto& iteCamera : m_lisCameras)
		{
			iteCamera->ViewParams(pTrans->GetWorldPosition(), iteCamera->GetLookAt(), iteCamera->GetUp());
		}
	}
}

void HrSceneObject::SetRenderable(const HrRenderablePtr& pRenderable)
{
	if (!m_pRenderable)
	{
		BOOST_ASSERT(false);
	}

	m_pRenderable = pRenderable;
}

const HrRenderablePtr& HrSceneObject::GetRenderable()
{
	return m_pRenderable;
}

void HrSceneObject::AddComponent(EnumSceneComponentType comType, const HrSceneObjectComponentPtr& pSceneObjComponent)
{
	switch (comType)
	{
	case HrSceneObject::SCT_NORMAL:
		break;
	case HrSceneObject::SCT_CAMERA:
	{
		HrCameraPtr pCamera = HrCheckPointerCast<HrCamera>(pSceneObjComponent);
		m_lisCameras.push_back(pCamera);
		AddCameraToScene(pCamera);
		break;
	}
	default:
		break;
	}
	m_lisComponents.push_back(pSceneObjComponent);
}

void HrSceneObject::AddCameraToScene(const HrCameraPtr& pCamera)
{
	if (!m_pContainerNode.expired())
	{
		HrSceneNodePtr pSceneNode = m_pContainerNode.lock();
		if (pSceneNode->GetEnable())
		{
			HrDirector::Instance()->GetRenderCoreComponent()->AddViewPort(pCamera->GetViewPort());
		}
	}
}

