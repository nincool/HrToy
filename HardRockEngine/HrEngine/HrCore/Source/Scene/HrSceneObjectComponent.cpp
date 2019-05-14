#include "Scene/HrSceneObjectComponent.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrResourceModule.h"
#include "Kernel/HrSceneModule.h"
#include "Kernel/HrEventSystemModule.h"
#include "Kernel/HrWindowModule.h"
#include "Render/HrCamera.h"
#include "Render/HrInstanceBatchHW.h"
#include "Render/HrInstanceBatchObject.h"
#include "Render/HrMeshRenderable.h"
#include "Render/HrViewPort.h"
#include "Render/HrDataDefine.h"
#include "Render/HrSkyBox.h"
#include "Render/HrRenderCommand.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"
#include "Scene/HrTransform.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrMesh.h"
#include "Asset/HrMeshModel.h"
#include "Event/HrEventListener.h"
#include "UI/HrUIWidget.h"
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

int HrSceneObjectComponent::GetComType()
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

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

HrCameraComponet::HrCameraComponet(const std::string& strName, HrSceneObject* pSceneObj) : HrSceneObjectComponent(strName, pSceneObj)
{
	m_comType = HrSceneObjectComponent::SCT_CAMERA;
	m_pCamera = HrMakeSharedPtr<HrCamera>(strName);
	m_pViewPort = HrMakeSharedPtr<HrViewPort>(m_pCamera);
	auto& pWinCom = HrDirector::Instance()->GetWindowModule();
	uint32 nTopX = pWinCom->GetWindowX();
	uint32 nTopY = pWinCom->GetWindowY();
	uint32 nWidth = pWinCom->GetWindowWidth();
	uint32 nHeight = pWinCom->GetWindowHeight();
	m_pViewPort->SetViewPortAttribute(static_cast<float>(nTopX)
		, static_cast<float>(nTopY)
		, static_cast<float>(nWidth)
		, static_cast<float>(nHeight), 0);
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
	Vector3 vLookAt = pTransform->GetForward() * m_pCamera->GetLookAtDistance();
	Vector3 vUp = pTransform->GetUp();

	std::cout << "222Pitch [" << vUp[0] << "]  [" << vUp[1] << "] [" << vUp[2] << "]" << std::endl;

	m_pCamera->ViewParams(vPosition, vLookAt, vUp);


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

void HrCameraComponet::SetCameraType(HrCamera::EnumCameraType cameraType)
{
	m_pCamera->SetCameraType(cameraType);
}

int HrCameraComponet::GetCameraMaskLayer()
{
	return m_pCamera->GetCameraMaskLayer();
}

void HrCameraComponet::SetCameraMaskLayer(int nMaskLayer)
{
	m_pCamera->SetCameraMaskLayer(nMaskLayer);
}

//////////////////////////////////////////////////////////////////////
//HrTrackBallCameraController
//////////////////////////////////////////////////////////////////////

HrTrackBallCameraController::HrTrackBallCameraController(const std::string& strName, HrSceneObject* pSceneObj)
	: HrSceneObjectComponent(strName, pSceneObj)
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

HrFirstPersonCameraController::HrFirstPersonCameraController(const std::string& strName, HrSceneObject* pSceneObj)
	: HrSceneObjectComponent(strName, pSceneObj)
{
	m_comType = std::hash_value(strName);

	m_fRotationY = 0;
	m_fOldMouseX = m_fOldMouseY = 0;

	m_fForwardSpeed = 0.01f;

	m_bKeyAPressed = false;
	m_bKeyWPressed = false;
	m_bKeySPressed = false;
	m_bKeyDPressed = false;

	CreateInputEvent();
}

void HrFirstPersonCameraController::CreateInputEvent()
{
	HrEventListenerKeyboardPtr pEventListenerKeyboard = HrMakeSharedPtr<HrEventListenerKeyboard>(HR_CALLBACK_2(HrFirstPersonCameraController::OnKeyPressed, this)
		, HR_CALLBACK_2(HrFirstPersonCameraController::OnKeyReleased, this));
	HrDirector::Instance()->GetEventSystemModule()->AddEventListener(pEventListenerKeyboard, this);

	HrEventListenerMousePtr pEventListenerMouse = HrMakeSharedPtr<HrEventListenerMouse>(HR_CALLBACK_2(HrFirstPersonCameraController::OnMousePressed, this)
		, HR_CALLBACK_2(HrFirstPersonCameraController::OnMouseReleased, this), HR_CALLBACK_1(HrFirstPersonCameraController::OnMouseMove, this));
	HrDirector::Instance()->GetEventSystemModule()->AddEventListener(pEventListenerMouse, this);
}

bool HrFirstPersonCameraController::Update(float fDelta)
{
	float fForward = 0, fBack = 0, fLeft = 0, fRight = 0;
	if (m_bKeyWPressed)
		fForward += fDelta * m_fForwardSpeed;
	if (m_bKeySPressed)
		fBack += fDelta * m_fForwardSpeed;
	if (m_bKeyAPressed)
		fLeft += fDelta * m_fForwardSpeed;
	if (m_bKeyDPressed)
		fRight += fDelta * m_fForwardSpeed;

	if (m_bKeyWPressed || m_bKeySPressed || m_bKeyAPressed || m_bKeyDPressed)
	{
		m_pSceneObj->GetSceneNode()->GetTransform()->Translate(Vector3(fRight - fLeft, 0, fForward - fBack), HrTransform::TS_LOCAL);

		return true;
	}
	
	return false;
}

void HrFirstPersonCameraController::OnKeyPressed(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent)
{
	switch (keyCode)
	{
	case HrEventKeyboard::EnumKeyCode::KEY_A:
		m_bKeyAPressed = true;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_D:
		m_bKeyDPressed = true;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_W:
		m_bKeyWPressed = true;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_S:
		m_bKeySPressed = true;
		break;
	default:
		break;
	}
}

void HrFirstPersonCameraController::OnKeyReleased(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent)
{
	switch (keyCode)
	{
	case HrEventKeyboard::EnumKeyCode::KEY_A:
		m_bKeyAPressed = false;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_D:
		m_bKeyDPressed = false;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_W:
		m_bKeyWPressed = false;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_S:
		m_bKeySPressed = false;
		break;
	default:
		break;
	}
}

void HrFirstPersonCameraController::OnMousePressed(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
{
	switch (mouseID)
	{
	case Hr::HrEventMouse::EnumMouseButtonID::MBI_LEFT:
		break;
	case Hr::HrEventMouse::EnumMouseButtonID::MBI_RIGHT:
		break;
	case Hr::HrEventMouse::EnumMouseButtonID::MBI_MIDDLE:
		break;
	default:
		break;
	}
}

void HrFirstPersonCameraController::OnMouseReleased(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
{
	switch (mouseID)
	{
	case Hr::HrEventMouse::EnumMouseButtonID::MBI_LEFT:
		break;
	case Hr::HrEventMouse::EnumMouseButtonID::MBI_RIGHT:
		break;
	case Hr::HrEventMouse::EnumMouseButtonID::MBI_MIDDLE:
		break;
	default:
		break;
	}
}

void HrFirstPersonCameraController::OnMouseMove(const HrEventPtr& pEvent)
{
	HrEventMousePtr pMouseEvent = HrCheckPointerCast<HrEventMouse>(pEvent);

	static float s_x = 0, s_y = 0, s_z = 0;

	float x = pMouseEvent->GetX();
	float y = pMouseEvent->GetY();
	float z = pMouseEvent->GetZ();


	{
		Vector3 vEulerAngle = m_pSceneObj->GetSceneNode()->GetTransform()->GetRotation();
		float fRX = vEulerAngle[1] + (x - m_fOldMouseX);
		
		m_fRotationY += (y - m_fOldMouseY);
		m_fRotationY = HrMath::Clamp(m_fRotationY, -60, 60);
		
		auto ori = HrMath::RotationQuaternionPitchYawRoll(HrMath::Degree2Radian(Vector3(m_fRotationY, fRX, 0)));
		m_pSceneObj->GetSceneNode()->GetTransform()->SetOrientation(ori);

		m_fOldMouseX = x;
		m_fOldMouseY = y;
	}

}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

HrLightComponent::HrLightComponent(const std::string& strName, HrSceneObject* pSceneObj, HrLight::EnumLightType lightType)
	: HrSceneObjectComponent(strName, pSceneObj)
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
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

HrRenderableComponent::HrRenderableComponent(const std::string& strName, HrSceneObject* pSceneObj)
	: HrSceneObjectComponent(strName, pSceneObj)
{

}

HrRenderableComponent::~HrRenderableComponent()
{

}

void HrRenderableComponent::SetRenderable(const HrRenderablePtr& pRenderable)
{
	m_pRenderable = pRenderable;

	HrTransform* pTransform = m_pSceneObj->GetSceneNode()->GetTransform().get();
	pTransform->SetAABBox(m_pRenderable->GetAABBox());
	m_pRenderable->GetRenderCommand()->SetTransform(pTransform);
}

void HrRenderableComponent::SetRenderEffect(const HrRenderEffectPtr& pRenderEffect)
{
	if (m_pRenderable)
		m_pRenderable->SetRenderEffect(pRenderEffect);
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

HrInstanceBatchComponent::HrInstanceBatchComponent(const std::string& strName, HrSceneObject* pSceneObj)
	: HrSceneObjectComponent(strName, pSceneObj)
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
	: HrSceneObjectComponent(strName, pSceneObj)
{
}

HrInstanceObjectComponent::~HrInstanceObjectComponent()
{

}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

HrUICanvasComponent::HrUICanvasComponent(const std::string& strName, HrSceneObject* pSceneObj)
	: HrSceneObjectComponent(strName, pSceneObj)
{
}

HrUICanvasComponent::~HrUICanvasComponent()
{
		
}

void HrUICanvasComponent::OnEnter()
{
	m_pCameraCom = m_pSceneObj->GetComponent<HrCameraComponet>();
	if (!m_pCameraCom)
	{
		HRERROR("HrUICanvasComponent::OnEnter Error!");
	}
	else
	{
		m_pCameraCom->SetCameraMaskLayer(CML_UI);
	}
}


//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

HrUIComponent::HrUIComponent(const std::string& strName, HrSceneObject* pSceneObj)
	: HrSceneObjectComponent(strName, pSceneObj)
{
}

HrUIComponent::~HrUIComponent()
{
}

void HrUIComponent::SetUI(const HrUIWidgetPtr& pUIWidget)
{
	m_pUIWidget = pUIWidget;
	const HrRenderablePtr& pRenderable = pUIWidget->GetRenderable();
	m_pSceneObj->GetSceneNode()->GetTransform()->SetAABBox(pRenderable->GetAABBox());
}

const HrUIWidgetPtr& HrUIComponent::GetUIWidget() const
{
	return m_pUIWidget;
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

HrSkyBoxComponent::HrSkyBoxComponent(const std::string& strName, HrSceneObject* pSceneObj)
	: HrSceneObjectComponent(strName, pSceneObj)
{
	m_pMeshModelSphere = HrMakeSharedPtr<HrMeshModelSpherePTNUV>(200, 30, 30);
	m_pSkyBox = HrMakeSharedPtr<HrSkyBox>(m_pMeshModelSphere->GetMesh()->GetSubMesh(0));
	HrRenderableComponentPtr& pRenderCom = m_pSceneObj->AddComponent<HrRenderableComponent>();
	pRenderCom->SetRenderable(m_pSkyBox);
}

void HrSkyBoxComponent::SetCubeMap(const HrTexturePtr& pCubeMap)
{
	m_pCubeMap = pCubeMap;
	m_pSkyBox->SetCubeMap(m_pCubeMap);
}

