#include "HrTestScene.h"

using namespace Hr;

HrTestScene::HrTestScene()
{

}

HrTestScene::~HrTestScene()
{

}


void HrTestScene::CreateSceneFromData()
{
	HrSceneImported::CreateSceneFromData();
}

void HrTestScene::OnEnter()
{
	HrSceneImported::OnEnter();

	CreateInputEvent();

	HrDirector::Instance()->GetScheduler()->Schedule(HR_CALLBACK_1(HrTestScene::MouseUpdate, this), this, "HR_GEOMETRY_MOUSE_UPDATE", 0.01, 0, 0);
}


void HrTestScene::CreateInputEvent()
{
	HrEventListenerKeyboardPtr pEventListenerKeyboard = MakeSharedPtr<HrEventListenerKeyboard>(HR_CALLBACK_2(HrTestScene::OnKeyPressed, this)
		, HR_CALLBACK_2(HrTestScene::OnKeyReleased, this));
	HrEventDispatcher::Instance()->AddEventListener(CheckPointerCast<HrEventListener>(pEventListenerKeyboard));

	HrEventListenerMousePtr pEventListenerMouse = MakeSharedPtr<HrEventListenerMouse>(HR_CALLBACK_2(HrTestScene::OnMousePressed, this)
		, HR_CALLBACK_2(HrTestScene::OnMouseReleased, this), HR_CALLBACK_1(HrTestScene::OnMouseMove, this));
	HrEventDispatcher::Instance()->AddEventListener(CheckPointerCast<HrEventListener>(pEventListenerMouse));
}

void HrTestScene::ResetKeyFlag()
{
	m_bKeyAPressed = false;
	m_bKeyWPressed = false;
	m_bKeySPressed = false;
	m_bKeyDPressed = false;

	m_bKey0Pressed = false;
	m_bKey1Pressed = false;

	m_bKeyF1Pressed = false;
	m_bKeyF2Pressed = false;

	m_bLeftMousePressed = false;
	m_bRightMousePressed = false;

	m_bKeyLeftPressed = false;
	m_bKeyRightPressed = false;
	m_bKeyUpPressed = false;
	m_bKeyDownPressed = false;
}

void HrTestScene::OnKeyPressed(HrEventKeyboard::EnumKeyCode keyCode, HrEvent* pEvent)
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
	case HrEventKeyboard::EnumKeyCode::KEY_0:
		m_bKey0Pressed = true;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_1:
		m_bKey1Pressed = true;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_F1:
		m_bKeyF1Pressed = true;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_F2:
		m_bKeyF2Pressed = true;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_KP_LEFT:
		m_bKeyLeftPressed = true;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_KP_RIGHT:
		m_bKeyRightPressed = true;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_KP_UP:
		m_bKeyUpPressed = true;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_KP_DOWN:
		m_bKeyDownPressed = true;
		break;
	default:
		break;
	}
}

void HrTestScene::OnKeyReleased(HrEventKeyboard::EnumKeyCode keyCode, HrEvent* pEvent)
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
	case HrEventKeyboard::EnumKeyCode::KEY_F1:
		m_bKeyF1Pressed = false;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_F2:
		m_bKeyF2Pressed = false;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_KP_LEFT:
		m_bKeyLeftPressed = false;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_KP_RIGHT:
		m_bKeyRightPressed = false;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_KP_UP:
		m_bKeyUpPressed = false;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_KP_DOWN:
		m_bKeyDownPressed = false;
		break;
	default:
		break;
	}
}

void HrTestScene::MouseUpdate(float fDelta)
{
	float fSpeed = 0.5f;
	if (m_bKeyAPressed)
	{
	}
	else if (m_bKeyWPressed)
	{
	}
	else if (m_bKeySPressed)
	{
	}
	else if (m_bKeyDPressed)
	{
	}
	else if (m_bKey0Pressed)
	{
	}
	else if (m_bKey1Pressed)
	{
	}
	else if (m_bKeyF1Pressed)
	{
	}
	else if (m_bKeyF2Pressed)
	{

	}
	else if (m_bKeyLeftPressed)
	{
	}
	else if (m_bKeyRightPressed)
	{
	}
	else if (m_bKeyUpPressed)
	{
	}
	else if (m_bKeyDownPressed)
	{
	}
}

void HrTestScene::OnMousePressed(HrEventMouse::EnumMouseButtonID mouseID, HrEvent* pEvent)
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

void HrTestScene::OnMouseReleased(HrEventMouse::EnumMouseButtonID mouseID, HrEvent* pEvent)
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

void HrTestScene::OnMouseMove(HrEvent* pEvent)
{
	static float s_floatX = 0;
	static float s_floatY = 0;
	HrEventMouse* pMouseEvnet = (HrEventMouse*)pEvent;
	float x = pMouseEvnet->GetX();
	float y = pMouseEvnet->GetY();

	if (m_bLeftMousePressed)
	{

	}

	s_floatX = x;
	s_floatY = y;
}

