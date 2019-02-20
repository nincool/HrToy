#include "Scene/HrSceneObjectComponent.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrResourceModule.h"
#include "Kernel/HrSceneModule.h"
#include "Kernel/HrEventSystemModule.h"
#include "Event/HrEvent.h"
#include "Render/HrCamera.h"
#include "Render/HrInstanceBatchHW.h"
#include "Render/HrInstanceBatchObject.h"
#include "Render/HrMeshRenderable.h"
#include "Render/HrViewPort.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"
#include "Scene/HrTransform.h"
#include "Asset/HrRenderEffect.h"
#include <iostream>

using namespace Hr;

HrSceneObjectComponent::HrSceneObjectComponent(const std::string& strName, HrSceneObject* pSceneObj) : m_strName(strName)
{
	m_pSceneObj = pSceneObj;
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

HrSceneObject* HrSceneObjectComponent::GetAttachSceneObject()
{
	return m_pSceneObj;
}

void HrSceneObjectComponent::UpdateTransform(const HrTransformPtr& pTransform)
{

}

HrSceneObjectMutexCom::HrSceneObjectMutexCom(const std::string& strName, HrSceneObject* pSceneObj) : HrSceneObjectComponent(strName, pSceneObj)
{
}

HrSceneObjectMutexCom::~HrSceneObjectMutexCom()
{
}

HrSceneObjectSharedCom::HrSceneObjectSharedCom(const std::string& strName, HrSceneObject* pSceneObj) : HrSceneObjectComponent(strName, pSceneObj)
{
}

HrSceneObjectSharedCom::~HrSceneObjectSharedCom()
{
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

HrCameraComponet::HrCameraComponet(const std::string& strName, HrSceneObject* pSceneObj) : HrSceneObjectMutexCom(strName, pSceneObj)
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
	HrTransformPtr pTrans = m_pSceneObj->GetSceneNode()->GetTransform();
	Vector3 vWorldPos = pTrans->GetWorldPosition();
	m_pCamera->ViewParams(vWorldPos, pTrans->GetForward() * 1.0f, pTrans->GetUp());

	HrDirector::Instance()->GetEventSystemModule()->AddEventCustomListener(HrEvent::scEventEndRenderScene, std::bind(&HrCameraComponet::OnEndRenderScene, this, std::placeholders::_1), this);
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

	//todo
	HrDirector::Instance()->GetSceneModule()->DirtyScene();
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

void HrCameraComponet::OnEndRenderScene(const HrEventPtr& pEvent)
{

}

//////////////////////////////////////////////////////////////////////
//HrTrackBallCameraController
//////////////////////////////////////////////////////////////////////

HrTrackBallCameraController::HrTrackBallCameraController(const std::string& strName, HrSceneObject* pSceneObj)
	: HrSceneObjectSharedCom(strName, pSceneObj)
{
	m_fRotationScaler = 0.0005;
	m_fMoveScaler = 0.0005;
	m_fZoomScaler = 0.01;

	m_vTarget = Vector3::Zero();
}

HrTrackBallCameraController::~HrTrackBallCameraController()
{
}

void HrTrackBallCameraController::OnEnter()
{
	//校验是否有其他CameraController
	m_pCameraCom = m_pSceneObj->GetComponent<HrCameraComponet>();
	if (!m_pCameraCom)
	{
		HRERROR("HrTrackBallCameraController::OnEnter Error!");
	}
	else
	{
		m_vRight = m_pCameraCom->GetCamera()->GetRight();

		HrTransformPtr pTrans = m_pSceneObj->GetSceneNode()->GetTransform();
		Vector3 vWorldPos = pTrans->GetWorldPosition();

		if (HrMath::CompareApproximately(m_vTarget, vWorldPos))
		{
			m_vTarget += pTrans->GetForward() * 0.01;
		}

		Vector3 vLookDir = m_vTarget - vWorldPos;
		Vector3 vUpDir = HrMath::Cross(vLookDir, m_vRight);
		Quaternion orientation = HrMath::ToQuaternion(HrMath::LookRotationToMatrix(vLookDir, vUpDir));
		m_pSceneObj->GetSceneNode()->GetTransform()->SetOrientation(orientation);
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
	vUpDir = HrMath::Normalize(vUpDir);

	m_pSceneObj->GetSceneNode()->GetTransform()->SetPosition(vPos2);
	Quaternion orientation = HrMath::ToQuaternion(HrMath::LookRotationToMatrix(vLookDir, vUpDir));
	m_pSceneObj->GetSceneNode()->GetTransform()->SetOrientation(orientation);
	
}

void HrTrackBallCameraController::Forward(float fZ)
{
	//假如无限接近的话，那么不运动
	float fLookAtDistance = m_pCameraCom->GetCamera()->GetLookAtDistance();
	if (fZ > 0 && fLookAtDistance <= 5.0f)
	{
		return;
	}

	//计算距离
	m_pSceneObj->GetSceneNode()->GetTransform()->Translate(Vector3(0, 0, fZ * m_fZoomScaler), HrTransform::TS_LOCAL);
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

HrLightComponent::HrLightComponent(const std::string& strName, HrSceneObject* pSceneObj, HrLight::EnumLightType lightType)
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
	m_pLight->SetPosition(pTransform->GetWorldPosition());
	m_pLight->SetDirection(pTransform->GetWorldForward());
	//auto vLightPosition = m_pLight->GetPosition();
	//std::cout << "LightPosition x:" << vLightPosition[0] << " y:" << vLightPosition[1] << " z:" << vLightPosition[2] << std::endl;
	//auto vWorldForward = m_pLight->GetDirection();
	//std::cout << "LightForward  x:" << vWorldForward[0] << " y:" << vWorldForward[1] << " z:" << vWorldForward[2] << std::endl;

}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

HrRenderableComponent::HrRenderableComponent(const std::string& strName, HrSceneObject* pSceneObj) : HrSceneObjectMutexCom(strName, pSceneObj)
{

}

HrRenderableComponent::~HrRenderableComponent()
{

}

void HrRenderableComponent::SetRenderable(const HrRenderablePtr& pRenderable)
{
	m_pRenderable = pRenderable;
	m_pSceneObj->GetSceneNode()->GetTransform()->SetAABBox(m_pRenderable->GetAABBox());
}


//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

HrInstanceBatchComponent::HrInstanceBatchComponent(const std::string& strName, HrSceneObject* pSceneObj)
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
	//m_pInsBatch->SetSubMesh(pSubMesh);
	m_pInsBatch->SetRenderEffect(HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("Media/HrShader/HrInstanceEffect.json"));
	//m_pInsBatch->SetAttachSceneObject(GetAttachSceneObject());
}

HrSceneNodePtr HrInstanceBatchComponent::CreateInstance(const std::string& strName)
{
	//todo instance

		//HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
		//HrSceneObjectPtr pSceneObj = m_pInsBatch->CreateInstance();
		//pSceneNode->SetSceneObject(pSceneObj);

		//HrSceneObjectPtr pParentObj = m_pAttachSceneObj.lock();
		//HrSceneNodePtr pAttachSceneNode = pParentObj->GetSceneNode();
		//if (pAttachSceneNode)
		//{
		//	pAttachSceneNode->AddChild(pSceneNode);
		//}

		//return pSceneNode;
	

	return nullptr;
}

const HrInstanceBatchPtr& HrInstanceBatchComponent::GetInstanceBatch()
{
	return m_pInsBatch;
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////


HrInstanceObjectComponent::HrInstanceObjectComponent(const std::string& strName, HrSceneObject* pSceneObj)
	: HrSceneObjectMutexCom(strName, pSceneObj)
{
}

HrInstanceObjectComponent::~HrInstanceObjectComponent()
{

}

