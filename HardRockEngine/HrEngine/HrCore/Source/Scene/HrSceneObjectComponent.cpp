#include "Scene/HrSceneObjectComponent.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrCoreComponentResource.h"
#include "Render/HrCamera.h"
#include "Render/HrInstanceBatchHW.h"
#include "Render/HrInstanceBatchObject.h"
#include "Render/HrMeshRenderable.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"
#include "Scene/HrTransform.h"
#include "Scene/HrSceneObjectComponent.h"
#include "Asset/HrRenderEffect.h"

using namespace Hr;

HrSceneObjectComponent::HrSceneObjectComponent(const std::string& strName, const HrSceneObjectPtr& pSceneObj) : m_strName(strName)
{
	m_pAttachSceneObj = pSceneObj;
}

HrSceneObjectComponent::~HrSceneObjectComponent()
{

}

bool HrSceneObjectComponent::InitComponent()
{
	return true;
}

bool HrSceneObjectComponent::Update(float fDelta)
{
	return true;
}

const std::string& HrSceneObjectComponent::GetName()
{
	return m_strName;
}

HrSceneObjectComponent::EnumSceneComponentType HrSceneObjectComponent::GetComType()
{
	return m_comType;
}

HrSceneObjectPtr HrSceneObjectComponent::GetAttachSceneObject()
{
	if (!m_pAttachSceneObj.expired())
	{
		return m_pAttachSceneObj.lock();
	}

	return nullptr;
}

void HrSceneObjectComponent::UpdateTransform(const HrTransformPtr& pTransform)
{

}

HrSceneObjectMutexCom::HrSceneObjectMutexCom(const std::string& strName, const HrSceneObjectPtr& pSceneObj) : HrSceneObjectComponent(strName, pSceneObj)
{
}

HrSceneObjectMutexCom::~HrSceneObjectMutexCom()
{
}

HrSceneObjectSharedCom::HrSceneObjectSharedCom(const std::string& strName, const HrSceneObjectPtr& pSceneObj) : HrSceneObjectComponent(strName, pSceneObj)
{
}

HrSceneObjectSharedCom::~HrSceneObjectSharedCom()
{
}


/////////////////////////////////////////////
//
/////////////////////////////////////////////
HrCameraComponet::HrCameraComponet(const std::string& strName, const HrSceneObjectPtr& pSceneObj) : HrSceneObjectMutexCom(strName, pSceneObj)
{
	m_comType = HrSceneObjectComponent::SCT_CAMERA;
	m_pCamera = HrMakeSharedPtr<HrCamera>(strName);
}

HrCameraComponet::~HrCameraComponet()
{
	
}

const HrCameraPtr& HrCameraComponet::GetCamera()
{
	return m_pCamera;
}

void HrCameraComponet::UpdateTransform(const HrTransformPtr& pTransform)
{
	m_pCamera->ViewParams(pTransform->GetWorldPosition(), m_pCamera->GetLookAt(), m_pCamera->GetUp());
}

/////////////////////////////////////////////
//
/////////////////////////////////////////////
HrLightComponent::HrLightComponent(const std::string& strName, const HrSceneObjectPtr& pSceneObj, HrLight::EnumLightType lightType) : HrSceneObjectMutexCom(strName, pSceneObj)
{
	m_comType = HrSceneObjectComponent::SCT_LIGHT;

	switch (lightType)
	{
	case HrLight::LT_AMBIENT:
		m_pLight = HrMakeSharedPtr<HrAmbientLight>();
		break;
	case HrLight::LT_DIRECTIONAL:
		m_pLight = HrMakeSharedPtr<HrDirectionalLight>();
		break;
	case HrLight::LT_POINT:
		m_pLight = HrMakeSharedPtr<HrPointLight>();
		break;
	case HrLight::LT_SPOTLIGHT:
		break;
	}
}

HrLightComponent::~HrLightComponent()
{

}

const HrLightPtr& HrLightComponent::GetLight()
{
	return m_pLight;
}


void Hr::HrLightComponent::SetDiffuse(const HrColor& diffuse)
{
	m_pLight->SetDiffuse(diffuse);
}

const HrColor& HrLightComponent::GetDiffuse() const
{
	return m_pLight->GetDiffuse();
}

void HrLightComponent::SetSpecular(const HrColor& specular)
{
	m_pLight->SetSpecular(specular);
}

const HrColor& HrLightComponent::GetSpecular() const
{
	return m_pLight->GetSpecular();
}

void HrLightComponent::UpdateTransform(const HrTransformPtr& pTransform)
{
	m_pLight->SetPosition(pTransform->GetPosition());
}

/////////////////////////////////////////////
//
/////////////////////////////////////////////

HrRenderableComponent::HrRenderableComponent(const std::string& strName, const HrSceneObjectPtr& pSceneObj) : HrSceneObjectMutexCom(strName, pSceneObj)
{

}

HrRenderableComponent::~HrRenderableComponent()
{

}

void HrRenderableComponent::SetRenderable(const HrRenderablePtr& pRenderable)
{
	m_pRenderable = pRenderable;
	m_pRenderable->SetAttachSceneObject(GetAttachSceneObject());
}

/////////////////////////////////////////////
//
/////////////////////////////////////////////

HrInstanceBatchComponent::HrInstanceBatchComponent(const std::string& strName, const HrSceneObjectPtr& pSceneObj)
	: HrSceneObjectSharedCom(strName, pSceneObj)
{
	const HrRenderableComponentPtr pRenderCom = pSceneObj->GetComponent<HrRenderableComponent>();
	if (pRenderCom)
	{
		const HrRenderablePtr& pRenderable = pRenderCom->GetRenderable();
		CreateInstanceBatch(pRenderable->GetSubMesh());
	}
}

HrInstanceBatchComponent::~HrInstanceBatchComponent()
{
}

void HrInstanceBatchComponent::CreateInstanceBatch(const HrSubMeshPtr& pSubMesh)
{
	if (m_pInsBatch)
	{
		TRE("Can not create InstanceBatchManager again!");
	}

	m_pInsBatch = HrMakeSharedPtr<HrInstanceBatchHW>();
	m_pInsBatch->SetSubMesh(pSubMesh);
	m_pInsBatch->SetRenderEffect(HrDirector::Instance()->GetResCoreComponent()->RetriveResource<HrRenderEffect>("Media/HrShader/HrInstanceEffect.json"));
	m_pInsBatch->SetAttachSceneObject(GetAttachSceneObject());
}

HrSceneNodePtr HrInstanceBatchComponent::CreateInstance(const std::string& strName)
{
	if (!m_pAttachSceneObj.expired())
	{
		HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
		HrSceneObjectPtr pSceneObj = m_pInsBatch->CreateInstance();
		pSceneNode->SetSceneObject(pSceneObj);

		HrSceneObjectPtr pParentObj = m_pAttachSceneObj.lock();
		HrSceneNodePtr pAttachSceneNode = pParentObj->GetSceneNode();
		if (pAttachSceneNode)
		{
			pAttachSceneNode->AddChild(pSceneNode);
		}

		return pSceneNode;
	}

	return nullptr;
}

const HrInstanceBatchPtr& HrInstanceBatchComponent::GetInstanceBatch()
{
	return m_pInsBatch;
}

/////////////////////////////////////////////
//
/////////////////////////////////////////////

HrInstanceObjectComponent::HrInstanceObjectComponent(const std::string& strName, const HrSceneObjectPtr& pSceneObj)
	: HrSceneObjectMutexCom(strName, pSceneObj)
{
}

HrInstanceObjectComponent::~HrInstanceObjectComponent()
{

}
