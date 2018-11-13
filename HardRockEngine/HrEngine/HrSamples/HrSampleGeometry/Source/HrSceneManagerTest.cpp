#include "HrSceneManagerTest.h"
#include "HrCore/Include/Config/HrContextConfig.h"

using namespace Hr;

HrSceneManagerTest::HrSceneManagerTest()
{
	ResetKeyFlag();
}

HrSceneManagerTest::~HrSceneManagerTest()
{

}

void HrSceneManagerTest::ResetKeyFlag()
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

void HrSceneManagerTest::OnEnter()
{
	HrScene::OnEnter();

	CreateSceneElements();

	CreateInputEvent();

	HrDirector::Instance()->Schedule(HR_CALLBACK_1(HrSceneManagerTest::SceneUpdate, this), this, "HR_GEOMETRY_MOUSE_UPDATE", 0.01, 0, 0);
}

void HrSceneManagerTest::CreateSceneElements()
{
	//添加摄像机
	m_pSceneMainCamera = HrSceneObjectFactory::Instance()->CreateCamera("MainCamera", 0, 0, HrContextConfig::Instance()->GetRenderTargetViewWidth(), HrContextConfig::Instance()->GetRenderTargetViewHeight(), 0);
	AddNode(m_pSceneMainCamera);
	m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -300.0f));

	//创建直线光
	auto pDirectionLight = HrSceneObjectFactory::Instance()->CreateLightNode("SceneDirectionLight", HrLight::LT_DIRECTIONAL);
	AddNode(pDirectionLight);

	m_pBuildingRoot = HrMakeSharedPtr<HrSceneNode>("Building_Root");
	AddNode(m_pBuildingRoot);
	m_pBuildingRoot->GetTransform()->SetPosition(Vector3(0.0f, -100.0f, 0.0f));

	m_pAddon1 = HrSceneObjectFactory::Instance()->CreateModelNode("Model/Building/Addon1Ex.hrmesh");
	m_pBuildingRoot->AddChild(m_pAddon1);
	m_pAddon1->GetTransform()->SetPosition(Vector3::Zero());

	m_pAddon2_2 = HrSceneObjectFactory::Instance()->CreateModelNode("Model/Building/Addon2bEx.hrmesh");
	m_pBuildingRoot->AddChild(m_pAddon2_2);
	m_pAddon2_2->GetTransform()->SetPosition(Vector3(0, 7, -100));
}

void HrSceneManagerTest::CreateInputEvent()
{
	HrEventListenerKeyboardPtr pEventListenerKeyboard = HrMakeSharedPtr<HrEventListenerKeyboard>(HR_CALLBACK_2(HrSceneManagerTest::OnKeyPressed, this)
		, HR_CALLBACK_2(HrSceneManagerTest::OnKeyReleased, this));
	HrDirector::Instance()->GetEventSystemModule()->AddEventListener(pEventListenerKeyboard, this);

	HrEventListenerMousePtr pEventListenerMouse = HrMakeSharedPtr<HrEventListenerMouse>(HR_CALLBACK_2(HrSceneManagerTest::OnMousePressed, this)
		, HR_CALLBACK_2(HrSceneManagerTest::OnMouseReleased, this), HR_CALLBACK_1(HrSceneManagerTest::OnMouseMove, this));
	HrDirector::Instance()->GetEventSystemModule()->AddEventListener(pEventListenerMouse, this);
}

void HrSceneManagerTest::OnKeyPressed(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent)
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

void HrSceneManagerTest::OnKeyReleased(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent)
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

void HrSceneManagerTest::SceneUpdate(float fDelta)
{
	float fSpeed = 1.0f;
	float fRotateSpeed = 5;
	if (m_bKeyAPressed)
	{
		m_pAddon2_2->GetTransform()->Translate(Vector3(-fSpeed, 0, 0));
	}
	else if (m_bKeyWPressed)
	{
		m_pAddon2_2->GetTransform()->Translate(Vector3(0.0f, fSpeed, 0.0f));
	}
	else if (m_bKeySPressed)
	{
		m_pAddon2_2->GetTransform()->Translate(Vector3(0.0f, -fSpeed, 0.0f));
	}
	else if (m_bKeyDPressed)
	{
		m_pAddon2_2->GetTransform()->Translate(Vector3(fSpeed, 0.0f, 0.0f));
	}
	else if (m_bKey0Pressed)
	{
		m_pAddon2_2->GetTransform()->Translate(Vector3(0.0f, 0.0f, -fSpeed));
	}
	else if (m_bKey1Pressed)
	{
		m_pAddon2_2->GetTransform()->Translate(Vector3(0.0f, 0.0f, fSpeed));
	}
}

void HrSceneManagerTest::OnMousePressed(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
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

void HrSceneManagerTest::OnMouseReleased(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
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

void HrSceneManagerTest::OnMouseMove(const HrEventPtr& pEvent)
{
	HrEventMousePtr pMouseEvent = HrCheckPointerCast<HrEventMouse>(pEvent);
	static float s_floatX = 0;
	static float s_floatY = 0;

	float x = pMouseEvent->GetX();
	float y = pMouseEvent->GetY();
	float z = pMouseEvent->GetZ();

	float fRotateSpeed = x - s_floatX > 0 ? 3.0f : -3.0f;
	s_floatX = x;

	if (abs(z) > 0.01f)
	{
		float fSpeed = 0.01f;
		m_pBuildingRoot->GetTransform()->Translate(Vector3(0, 0, fSpeed * z));
	}
	else if (m_bRightMousePressed)
	{
		m_pBuildingRoot->GetTransform()->Rotate(Vector3(0.0f, fRotateSpeed, 0.0f));
	}
}

