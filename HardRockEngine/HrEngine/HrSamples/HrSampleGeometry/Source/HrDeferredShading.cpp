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
	m_pSceneMainCamera = HrSceneObjectFactory::Instance()->CreateCamera("MainCamera");
	AddNode(m_pSceneMainCamera);
	m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -300.0f));

	//创建直线光
	auto pDirectionLight = HrSceneObjectFactory::Instance()->CreateLightNode("TestDirectionLight", HrLight::LT_DIRECTIONAL);
	AddNode(pDirectionLight);

	m_pTestNode = HrSceneObjectFactory::Instance()->CreateModelNode("Model/Basic/MySphere003/MySphere003.hrmesh");
	AddNode(m_pTestNode);
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
	case HrEventKeyboard::EnumKeyCode::KEY_Z:

		break;
	case HrEventKeyboard::EnumKeyCode::KEY_0:
		m_bKey0Pressed = true;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_1:
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
	case HrEventKeyboard::EnumKeyCode::KEY_0:
		m_bKey0Pressed = false;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_1:
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
		m_pTestNode->GetTransform()->Translate(Vector3(-fSpeed, 0, 0));
	}
	else if (m_bKeyWPressed)
	{
		m_pTestNode->GetTransform()->Translate(Vector3(0.0f, fSpeed, 0.0f));
	}
	else if (m_bKeySPressed)
	{
		m_pTestNode->GetTransform()->Translate(Vector3(0.0f, -fSpeed, 0.0f));
	}
	else if (m_bKeyDPressed)
	{
		m_pTestNode->GetTransform()->Translate(Vector3(fSpeed, 0.0f, 0.0f));
	}
	else if (m_bKey0Pressed)
	{
		m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -fSpeed));
	}
	else if (m_bKey1Pressed)
	{
		m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, fSpeed));
	}
	//else if (m_bKeyF1Pressed)
	//{
	//	m_pSceneMainCamera->GetTransform()->Rotate(Vector3(fRotateSpeed, 0.0f, 0.0f));
	//}
	//else if (m_bKeyF2Pressed)
	//{

	//}
	//else if (m_bKeyLeftPressed)
	//{
	//	m_pTestSceneNode->GetTransform()->Rotate(Vector3(0.0f, -fRotateSpeed, 0.0f));

	//}
	//else if (m_bKeyRightPressed)
	//{
	//	m_pTestSceneNode->GetTransform()->Rotate(Vector3(0.0f, fRotateSpeed, 0.0f));

	//}
	//else if (m_bKeyUpPressed)
	//{
	//	m_pTestSceneNode->GetTransform()->Rotate(Vector3(fRotateSpeed, 0.0f, 0.0f));

	//}
	//else if (m_bKeyDownPressed)
	//{
	//	m_pTestSceneNode->GetTransform()->Rotate(Vector3(-fRotateSpeed, 0.0f, 0.0f));

	//}
}

void HrDeferredShading::OnMousePressed(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
{
	//switch (mouseID)
	//{
	//case Hr::HrEventMouse::EnumMouseButtonID::MBI_LEFT:
	//	m_bLeftMousePressed = true;
	//	break;
	//case Hr::HrEventMouse::EnumMouseButtonID::MBI_RIGHT:
	//	m_bRightMousePressed = true;
	//	break;
	//case Hr::HrEventMouse::EnumMouseButtonID::MBI_MIDDLE:
	//	break;
	//default:
	//	break;
	//}
}

void HrDeferredShading::OnMouseReleased(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
{
	//switch (mouseID)
	//{
	//case Hr::HrEventMouse::EnumMouseButtonID::MBI_LEFT:
	//	m_bLeftMousePressed = false;
	//	break;
	//case Hr::HrEventMouse::EnumMouseButtonID::MBI_RIGHT:
	//	m_bRightMousePressed = false;
	//	break;
	//case Hr::HrEventMouse::EnumMouseButtonID::MBI_MIDDLE:
	//	break;
	//default:
	//	break;
	//}
}

void HrDeferredShading::OnMouseMove(const HrEventPtr& pEvent)
{
	HrEventMousePtr pMouseEvent = HrCheckPointerCast<HrEventMouse>(pEvent);
	static float s_floatX = 0;
	static float s_floatY = 0;

	float x = pMouseEvent->GetX();
	float y = pMouseEvent->GetY();
	float z = pMouseEvent->GetZ();

	float fSpeed = 0.01f;
	m_pTestNode->GetTransform()->Translate(Vector3(0, 0, fSpeed * z));
}

