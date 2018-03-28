#include "HrGeometryScene.h"
#include "HrCore/Include/Config/HrContextConfig.h"

using namespace Hr;

HrGeometryScene::HrGeometryScene()
{
	ResetKeyFlag();
}

HrGeometryScene::~HrGeometryScene()
{

}

void HrGeometryScene::ResetKeyFlag()
{
	m_bKeyAPressed = false;
	m_bKeyWPressed = false;
	m_bKeySPressed = false;
	m_bKeyDPressed = false;
}

void HrGeometryScene::OnEnter()
{
	HrScene::OnEnter();

	CreateSceneElements();
	
	CreateInputEvent();

	HrDirector::Instance()->Schedule(HR_CALLBACK_1(HrGeometryScene::SceneUpdate, this), this, "HR_GEOMETRY_MOUSE_UPDATE", 0.01, 0, 0);
}

void HrGeometryScene::CreateSceneElements()
{
	//添加摄像机
	m_pSceneMainCamera = HrSceneObjectFactory::Instance()->CreateCamera("MainCamera", 0, 0, HrContextConfig::Instance()->GetRenderTargetViewWidth(), HrContextConfig::Instance()->GetRenderTargetViewHeight(), 0);
	AddNode(m_pSceneMainCamera);
	m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -10.0f));

	//创建直线光
	auto pDirectionLight = HrSceneObjectFactory::Instance()->CreateLightNode("TestDirectionLight", HrLight::LT_DIRECTIONAL);
	AddNode(pDirectionLight);

	//auto pRenderEffect = HrCheckPointerCast<HrRenderEffect>(HrResourceManager::Instance()->RetriveOrLoadResource("Media/HrShader/HrSimple.json", HrResource::RT_EFFECT));
	//BOOST_ASSERT(pRenderEffect);

	//m_pTestNode = HrSceneObjectFactory::Instance()->CreateModel("PrefabModel/HrPrefab3.prefab");
	//m_pTestNode->GetChildByName("Box01")->GetSceneObject()->GetRenderable()->SetRenderEffect(pRenderEffect);
	//AddNode(m_pTestNode);
}

void HrGeometryScene::CreateInputEvent()
{
	HrEventListenerKeyboardPtr pEventListenerKeyboard = HrMakeSharedPtr<HrEventListenerKeyboard>(HR_CALLBACK_2(HrGeometryScene::OnKeyPressed, this)
		, HR_CALLBACK_2(HrGeometryScene::OnKeyReleased, this));
	HrDirector::Instance()->GetEventComponent()->AddEventListener(pEventListenerKeyboard, this);

	HrEventListenerMousePtr pEventListenerMouse = HrMakeSharedPtr<HrEventListenerMouse>(HR_CALLBACK_2(HrGeometryScene::OnMousePressed, this)
		, HR_CALLBACK_2(HrGeometryScene::OnMouseReleased, this), HR_CALLBACK_1(HrGeometryScene::OnMouseMove, this));
	HrDirector::Instance()->GetEventComponent()->AddEventListener(pEventListenerMouse, this);
}

void HrGeometryScene::OnKeyPressed(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent)
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
	default:
		break;
	}
}

void HrGeometryScene::OnKeyReleased(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent)
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

void HrGeometryScene::SceneUpdate(float fDelta)
{
	float fSpeed = 0.2f;
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
	//else if (m_bKey0Pressed)
	//{
	//	m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -fSpeed));
	//}
	//else if (m_bKey1Pressed)
	//{
	//	m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, fSpeed));
	//}
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

void HrGeometryScene::OnMousePressed(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
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

void HrGeometryScene::OnMouseReleased(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
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

void HrGeometryScene::OnMouseMove(const HrEventPtr& pEvent)
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

