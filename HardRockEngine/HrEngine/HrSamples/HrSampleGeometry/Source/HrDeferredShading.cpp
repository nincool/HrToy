#include "HrDeferredShading.h"
#include "HrCore/Include/Config/HrContextConfig.h"

using namespace Hr;

HrDeferredShading::HrDeferredShading()
{
	ResetKeyFlag();
}

HrDeferredShading::~HrDeferredShading()
{

}

void HrDeferredShading::ResetKeyFlag()
{
	m_bKeyAPressed = false;
	m_bKeyWPressed = false;
	m_bKeySPressed = false;
	m_bKeyDPressed = false;
	m_bKey0Pressed = false;
	m_bKey1Pressed = false;

	m_bLeftMousePressed = false;
	m_bRightMousePressed = false;
}

void HrDeferredShading::OnEnter()
{
	HrScene::OnEnter();

	CreateSceneElements();

	CreateInputEvent();

	HrDirector::Instance()->Schedule(HR_CALLBACK_1(HrDeferredShading::SceneUpdate, this), this, "HR_GEOMETRY_MOUSE_UPDATE", 0.01, 0, 0);
}

void HrDeferredShading::CreateSceneElements()
{
	//添加摄像机
	m_pSceneMainCamera = HrSceneObjectFactory::Instance()->CreateCamera("MainCamera", 0, 0, HrContextConfig::Instance()->GetRTVWidth(), HrContextConfig::Instance()->GetRTVHeight(), 0);
	AddNode(m_pSceneMainCamera);
	m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 100.0f, -300.0f));
	m_pSceneMainCamera->GetTransform()->SetRotation(Vector3(30, 0, 0));
	m_pTrackBallCameraCtrl = m_pSceneMainCamera->GetSceneObject()->AddComponent<HrTrackBallCameraController>();

	//创建直线光
	auto pDirectionLight = HrSceneObjectFactory::Instance()->CreateLightNode("SceneDirectionLight", HrLight::LT_DIRECTIONAL);
	AddNode(pDirectionLight);

	m_pBuildingRoot = HrMakeSharedPtr<HrSceneNode>("Building_Root");
	AddNode(m_pBuildingRoot);
	m_pBuildingRoot->GetTransform()->SetPosition(Vector3(0.0f, -100.0f, 0.0f));

	HrPrefabDataPtr pPrefabData = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrPrefabData>("Building1/Building1.hrpref", true, true);
	HrSceneNodePtr pBuildingNode = pPrefabData->CreateSceneNode();
	m_pBuildingRoot->AddChild(pBuildingNode);

	HrSceneNodePtr pPlane = HrSceneObjectFactory::Instance()->CreateQuadNodePN("Ground", 1000, 1000);
	AddNode(pPlane);
	pPlane->GetTransform()->SetPosition(Vector3(0, -100, 0));
	pPlane->GetTransform()->SetRotation(Vector3(90, 0, 0));
}

void HrDeferredShading::CreateInputEvent()
{
	HrEventListenerKeyboardPtr pEventListenerKeyboard = HrMakeSharedPtr<HrEventListenerKeyboard>(HR_CALLBACK_2(HrDeferredShading::OnKeyPressed, this)
		, HR_CALLBACK_2(HrDeferredShading::OnKeyReleased, this));
	HrDirector::Instance()->GetEventSystemModule()->AddEventListener(pEventListenerKeyboard, this);

	HrEventListenerMousePtr pEventListenerMouse = HrMakeSharedPtr<HrEventListenerMouse>(HR_CALLBACK_2(HrDeferredShading::OnMousePressed, this)
		, HR_CALLBACK_2(HrDeferredShading::OnMouseReleased, this), HR_CALLBACK_1(HrDeferredShading::OnMouseMove, this));
	HrDirector::Instance()->GetEventSystemModule()->AddEventListener(pEventListenerMouse, this);
}

void HrDeferredShading::OnKeyPressed(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent)
{
	ResetKeyFlag();
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
	case HrEventKeyboard::EnumKeyCode::KEY_KP_LEFT:
		m_bKey0Pressed = true;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_KP_RIGHT:
		m_bKey1Pressed = true;
		break;
	default:
		break;
	}
}

void HrDeferredShading::OnKeyReleased(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent)
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
	case HrEventKeyboard::EnumKeyCode::KEY_KP_LEFT:
		m_bKey0Pressed = false;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_KP_RIGHT:
		m_bKey1Pressed = false;
		break;
	default:
		break;
	}
}

void HrDeferredShading::SceneUpdate(float fDelta)
{
	float fSpeed = 1.0f;
	float fRotateSpeed = 5;
	if (m_bKeyAPressed)
	{
		m_pBuildingRoot->GetTransform()->Rotate(Vector3(0, -fSpeed, 0));
	}
	else if (m_bKeyWPressed)
	{
		m_pBuildingRoot->GetTransform()->Rotate(Vector3(fSpeed, 0, 0.0f));
	}
	else if (m_bKeySPressed)
	{
		m_pBuildingRoot->GetTransform()->Rotate(Vector3(-fSpeed, 0, 0.0f));
	}
	else if (m_bKeyDPressed)
	{
		m_pBuildingRoot->GetTransform()->Rotate(Vector3(0, fSpeed, 0.0f));
	}
	else if (m_bKey0Pressed)
	{
		m_pBuildingRoot->GetTransform()->Translate(Vector3(-fSpeed, 0, 0.0f));
	}
	else if (m_bKey1Pressed)
	{
		m_pBuildingRoot->GetTransform()->Translate(Vector3(fSpeed, 0, 0.0f));
	}
}

void HrDeferredShading::OnMousePressed(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
{
	switch (mouseID)
	{
	case Hr::HrEventMouse::EnumMouseButtonID::MBI_LEFT:
		m_bLeftMousePressed = true;
		break;
	case Hr::HrEventMouse::EnumMouseButtonID::MBI_RIGHT:
		m_bRightMousePressed = true;
		break;
	case Hr::HrEventMouse::EnumMouseButtonID::MBI_MIDDLE:
		break;
	default:
		break;
	}
}

void HrDeferredShading::OnMouseReleased(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
{
	switch (mouseID)
	{
	case Hr::HrEventMouse::EnumMouseButtonID::MBI_LEFT:
		m_bLeftMousePressed = false;
		break;
	case Hr::HrEventMouse::EnumMouseButtonID::MBI_RIGHT:
		m_bRightMousePressed = false;
		break;
	case Hr::HrEventMouse::EnumMouseButtonID::MBI_MIDDLE:
		break;
	default:
		break;
	}
}

void HrDeferredShading::OnMouseMove(const HrEventPtr& pEvent)
{
	HrEventMousePtr pMouseEvent = HrCheckPointerCast<HrEventMouse>(pEvent);
	static float s_floatX = 0;
	static float s_floatY = 0;

	float x = pMouseEvent->GetX();
	float y = pMouseEvent->GetY();
	float z = pMouseEvent->GetZ();

	static float fFrameWidth = HrDirector::Instance()->GetRenderModule()->GetRenderFrameBuffer()->GetFrameWidth();
	static float fFrameHeight = HrDirector::Instance()->GetRenderModule()->GetRenderFrameBuffer()->GetFrameHeight();

	float fProjX = x;
	float fProjY = fFrameHeight - y;

	static float fOldMouseX = 0;
	static float fOldMouseY = 0;

	float fDiffValueX = fProjX - fOldMouseX;
	float fDiffValueY = fProjY - fOldMouseY;

	fOldMouseX = fProjX;
	fOldMouseY = fProjY;

	float fRotateSpeed = x - s_floatX > 0 ? 3.0f : -3.0f;
	s_floatX = x;

	if (m_bRightMousePressed)
	{
		if (std::abs(fDiffValueX) > HrMath::EPSILON || std::abs(fDiffValueY) > HrMath::EPSILON)
		{
			m_pTrackBallCameraCtrl->Rotate(Vector3(fDiffValueX * 2, fDiffValueY * 2, 0));
		}
	}
}

