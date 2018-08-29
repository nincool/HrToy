#include "Scene/HrSceneObjectComponent.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrCoreComponentResource.h"
#include "Render/HrCamera.h"
#include "Render/HrInstanceBatchHW.h"
#include "Render/HrInstanceBatchObject.h"
#include "Render/HrMeshRenderable.h"
#include "Render/HrViewPort.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"
#include "Scene/HrTransform.h"
#include "Scene/HrSceneObjectComponent.h"
#include "Asset/HrRenderEffect.h"
#include <iostream>

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

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

HrCameraComponet::HrCameraComponet(const std::string& strName, const HrSceneObjectPtr& pSceneObj) : HrSceneObjectMutexCom(strName, pSceneObj)
{
	m_comType = HrSceneObjectComponent::SCT_CAMERA;
	m_pCamera = HrMakeSharedPtr<HrCamera>(strName);
	m_pViewPort = HrMakeSharedPtr<HrViewPort>(m_pCamera);
}

HrCameraComponet::~HrCameraComponet()
{
	
}

void HrCameraComponet::OnEnter()
{
	auto pSceneObj = m_pAttachSceneObj.lock();
	HrTransformPtr pTrans = pSceneObj->GetSceneNode()->GetTransform();
	Vector3 vWorldPos = pTrans->GetWorldPosition();

	m_pCamera->ViewParams(vWorldPos, pTrans->GetForward() * 1.0f, pTrans->GetUp());
}

const HrCameraPtr& HrCameraComponet::GetCamera()
{
	return m_pCamera;
}

void HrCameraComponet::UpdateTransform(const HrTransformPtr& pTransform)
{
	Vector3 vPosition = pTransform->GetWorldPosition();
	Vector3 vLookAt = m_pCamera->GetLookAt();
	Vector3 vUp = pTransform->GetUp();
	m_pCamera->ViewParams(vPosition, vLookAt, vUp);
}

const HrViewPortPtr& HrCameraComponet::GetViewPort()
{
	return m_pViewPort;
}

void HrCameraComponet::SetFov(float fFov)
{
	m_pCamera->ProjectParams(fFov, m_pCamera->Aspect(), m_pCamera->NearPlane(), m_pCamera->FarPlane());
}

void HrCameraComponet::SetAspect(float fAspect)
{
	m_pCamera->ProjectParams(m_pCamera->FOV(), fAspect, m_pCamera->NearPlane(), m_pCamera->FarPlane());
}

void HrCameraComponet::SetNearPlane(float fNear)
{
	m_pCamera->ProjectParams(m_pCamera->FOV(), m_pCamera->Aspect(), fNear, m_pCamera->FarPlane());
}

void HrCameraComponet::SetFarPlane(float fFar)
{
	m_pCamera->ProjectParams(m_pCamera->FOV(), m_pCamera->Aspect(), m_pCamera->NearPlane(), fFar);
}

//////////////////////////////////////////////////////////////////////
//HrTrackBallCameraController
//////////////////////////////////////////////////////////////////////

HrTrackBallCameraController::HrTrackBallCameraController(const std::string& strName, const HrSceneObjectPtr& pSceneObj) 
	: HrSceneObjectSharedCom(strName, pSceneObj)
{
	m_fRotationScaler = 0.0005;
	m_fMoveScaler = 0.0005;
	m_fZoomScaler = 0.005;

	m_vTarget = Vector3::Zero();
}

HrTrackBallCameraController::~HrTrackBallCameraController()
{
}

void HrTrackBallCameraController::OnEnter()
{
	auto pSceneObj = m_pAttachSceneObj.lock();

	//校验是否有其他CameraController
	m_pCameraCom = pSceneObj->GetComponent<HrCameraComponet>();
	if (!m_pCameraCom)
	{
		HRERROR("HrTrackBallCameraController::OnEnter Error!");
	}
	else
	{
		m_vRight = m_pCameraCom->GetCamera()->GetRight();

		HrTransformPtr pTrans = pSceneObj->GetSceneNode()->GetTransform();
		Vector3 vWorldPos = pTrans->GetWorldPosition();

		if (HrMath::CompareApproximately(m_vTarget, vWorldPos))
		{
			m_vTarget += pTrans->GetForward() * 0.01;
		}

		Vector3 vLookDir = m_vTarget - vWorldPos;
		Vector3 vUpDir = HrMath::Cross(vLookDir, m_vRight);
		Quaternion orientation = HrMath::ToQuaternion(HrMath::LookRotationToMatrix(vLookDir, vUpDir));
		pSceneObj->GetSceneNode()->GetTransform()->SetOrientation(orientation);
	}
}

void HrTrackBallCameraController::Rotate(const Vector3& v)
{
	Quaternion q1 = HrMath::RotationAxis(m_vRight, v[1] * m_fRotationScaler);
	Matrix4 mat1 = HrMath::RotationAroundTarget(m_vTarget, q1);
	Vector3 vPos1 = HrMath::TransformCoord(m_pCameraCom->GetCamera()->GetEyePos(), mat1);

	Quaternion q2 = HrMath::RotationAxis(float3(0.0f, HrMath::Sgn(m_pCameraCom->GetCamera()->GetUp().y()), 0.0), v[0] * m_fRotationScaler);
	Matrix4 mat2 = HrMath::RotationAroundTarget(m_vTarget, q2);
	Vector3 vPos2 = HrMath::TransformCoord(vPos1, mat2);

	m_vRight = HrMath::TransformQuat(m_vRight, q2); //按y轴旋转

	//LookAt 点
	Vector3 vLookDir = m_vTarget - vPos2;
	float fDist = HrMath::Length(vLookDir);

	Vector3 vUpDir = HrMath::Cross(vLookDir, m_vRight);

	if (!m_pAttachSceneObj.expired())
	{
		HrSceneObjectPtr pSceneObj = m_pAttachSceneObj.lock();
		pSceneObj->GetSceneNode()->GetTransform()->SetPosition(vPos2);
		Quaternion orientation = HrMath::ToQuaternion(HrMath::LookRotationToMatrix(vLookDir, vUpDir));
		pSceneObj->GetSceneNode()->GetTransform()->SetOrientation(orientation);
	}
}

void HrTrackBallCameraController::Zoom(float fZ)
{
	//假如无限接近的话，那么不运动
	float fLookAtDistance = m_pCameraCom->GetCamera()->GetLookAtDistance();
	std::cout << " TrackBallCamera Distance:" << fLookAtDistance << std::endl;
	if (fZ > 0 && fLookAtDistance <= 3.0f)
	{
		return;
	}

	//计算距离
	HrSceneObjectPtr pSceneObj = m_pAttachSceneObj.lock();
	HrTransformPtr pTrans = pSceneObj->GetSceneNode()->GetTransform();
	pTrans->Translate(Vector3(0, 0, fZ * m_fZoomScaler));
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

HrLightComponent::HrLightComponent(const std::string& strName, const HrSceneObjectPtr& pSceneObj, HrLight::EnumLightType lightType)
	: HrSceneObjectMutexCom(strName, pSceneObj)
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

void HrLightComponent::SetColor(const HrColor& color)
{
	m_pLight->SetColor(color);
}

const HrColor& HrLightComponent::GetColor() const
{
	return m_pLight->GetColor();
}

void HrLightComponent::UpdateTransform(const HrTransformPtr& pTransform)
{
	m_pLight->SetPosition(pTransform->GetPosition());
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

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
	m_pInsBatch->SetRenderEffect(HrDirector::Instance()->GetResourceComponent()->RetriveResource<HrRenderEffect>("Media/HrShader/HrInstanceEffect.json"));
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

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////


HrInstanceObjectComponent::HrInstanceObjectComponent(const std::string& strName, const HrSceneObjectPtr& pSceneObj)
	: HrSceneObjectMutexCom(strName, pSceneObj)
{
}

HrInstanceObjectComponent::~HrInstanceObjectComponent()
{

}

