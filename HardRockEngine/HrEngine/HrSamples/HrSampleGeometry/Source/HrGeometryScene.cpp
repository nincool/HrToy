#include "HrGeometryScene.h"

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

void HrGeometryScene::OnEnter()
{
	HrScene::OnEnter();

	CreateSceneElements();
	
	CreateInputEvent();

	HrDirector::Instance()->GetScheduler()->Schedule(HR_CALLBACK_1(HrGeometryScene::MouseUpdate, this), this, "HR_GEOMETRY_MOUSE_UPDATE", 0.01, 0, 0);
}

void HrGeometryScene::CreateSceneElements()
{
	//添加摄像机
	m_pSceneMainCamera = HrSceneObjectFactory::Instance()->CreateCamera();
	AddSceneNode(m_pSceneMainCamera);
	m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -300.0f));

	//设置环境光
	//SetAmbientLight(HrMath::MakeColor(120.0f, 120.0f, 120.0f, 255.0f));

	//m_pTestSceneNode = HrSceneObjectFactory::Instance()->CreatePlane(1000.0f, 1000.0f);
	//AddSceneNode(m_pTestSceneNode);
	//m_pTestSceneNode->GetTransform()->SetPosition(Vector3(0.0f, -10.0f, 0.0f));
	//m_pTestSceneNode->GetTransform()->SetRotation(Vector3(90.0f, 0.0f, 0.0f));

	m_pTestSceneNode = HrSceneObjectFactory::Instance()->CreateBox(100.0f);
	AddSceneNode(m_pTestSceneNode);
	m_pTestSceneNode->GetTransform()->SetPosition(Vector3::Zero());
	
	//创建灯光
	auto pLight = HrSceneObjectFactory::Instance()->CreateDirectionalLight(Vector3(1.0f, -1.0f, 1.0f), HrColor::Green, HrColor::Blue);
	AddSceneNode(pLight);
	pLight->GetTransform()->SetPosition(Vector3::Zero());

	//auto pLight = HrSceneObjectFactory::Instance()->CreatePointLight(HrColor::Blue, HrColor::Green, 10000, 0.2, 0.0005, 0.000005);
	//AddSceneNode(pLight);
	//pLight->GetTransform()->SetPosition(Vector3(200, 0, 0));

	//m_pTestSceneNode = HrSceneObjectFactory::Instance()->CreateSkyBox();
	//AddSceneNode(m_pTestSceneNode);
	//m_pTestSceneNode->GetTransform()->Translate(Vector3(20, 0, 0));

	//m_pTestSceneNode = HrSceneObjectFactory::Instance()->CreateModel("PrefabModel/HrPrefab2.prefab");
	//AddSceneNode(m_pTestSceneNode);
	//m_pTestSceneNode->GetTransform()->Translate(Vector3(0, 0, 0));

	//m_pTestSceneNode2 = HrSceneObjectFactory::Instance()->CreateModel("tests/56Por1.FBX");
	//m_pTestSceneNode->AddChild(m_pTestSceneNode2);
	//m_pTestSceneNode2->GetTransform()->Translate(Vector3(30, 0, 0));
	//AddSceneNode(m_pTestSceneNode2);

	//HrSceneNode* pBox = HrSceneObjectFactory::Instance()->CreateBox();
	//AddSceneNode(pBox);
}

void HrGeometryScene::CreateInputEvent()
{
	HrEventListenerKeyboardPtr pEventListenerKeyboard = HrMakeSharedPtr<HrEventListenerKeyboard>(HR_CALLBACK_2(HrGeometryScene::OnKeyPressed, this)
		, HR_CALLBACK_2(HrGeometryScene::OnKeyReleased, this));
	HrEventDispatcher::Instance()->AddEventListener(HrCheckPointerCast<HrEventListener>(pEventListenerKeyboard));

	HrEventListenerMousePtr pEventListenerMouse = HrMakeSharedPtr<HrEventListenerMouse>(HR_CALLBACK_2(HrGeometryScene::OnMousePressed, this)
		, HR_CALLBACK_2(HrGeometryScene::OnMouseReleased, this), HR_CALLBACK_1(HrGeometryScene::OnMouseMove, this));
	HrEventDispatcher::Instance()->AddEventListener(HrCheckPointerCast<HrEventListener>(pEventListenerMouse));
}

void HrGeometryScene::OnKeyPressed(HrEventKeyboard::EnumKeyCode keyCode, HrEvent* pEvent)
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

void HrGeometryScene::OnKeyReleased(HrEventKeyboard::EnumKeyCode keyCode, HrEvent* pEvent)
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

void HrGeometryScene::MouseUpdate(float fDelta)
{
	float fSpeed = 0.5f;
	float fRotateSpeed = 5;
	if (m_bKeyAPressed)
	{
		//m_pSceneMainCamera->GetTransform()->Translate(Vector3(-fSpeed, 0, 0));
		m_pTestSceneNode->GetTransform()->Translate(Vector3(-fSpeed, 0, 0));
	}
	else if (m_bKeyWPressed)
	{
		//m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0, fSpeed, 0));
		m_pTestSceneNode->GetTransform()->Translate(Vector3(0.0f, fSpeed, 0.0f));
	}
	else if (m_bKeySPressed)
	{
		//m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, -fSpeed, 0));
		m_pTestSceneNode->GetTransform()->Translate(Vector3(0.0f, -fSpeed, 0.0f));
	}
	else if (m_bKeyDPressed)
	{
		//m_pSceneMainCamera->GetTransform()->Translate(Vector3(fSpeed, 0.0f, 0.0f));
		m_pTestSceneNode->GetTransform()->Translate(Vector3(fSpeed, 0.0f, 0.0f));
	}
	else if (m_bKey0Pressed)
	{
		m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -fSpeed));
	}
	else if (m_bKey1Pressed)
	{
		m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, fSpeed));
	}
	else if (m_bKeyF1Pressed)
	{
		m_pSceneMainCamera->GetTransform()->Rotate(Vector3(fRotateSpeed, 0.0f, 0.0f));
	}
	else if (m_bKeyF2Pressed)
	{

	}
	else if (m_bKeyLeftPressed)
	{
		m_pTestSceneNode->GetTransform()->Rotate(Vector3(0.0f, -fRotateSpeed, 0.0f));

	}
	else if (m_bKeyRightPressed)
	{
		m_pTestSceneNode->GetTransform()->Rotate(Vector3(0.0f, fRotateSpeed, 0.0f));

	}
	else if (m_bKeyUpPressed)
	{
		m_pTestSceneNode->GetTransform()->Rotate(Vector3(fRotateSpeed, 0.0f, 0.0f));

	}
	else if (m_bKeyDownPressed)
	{
		m_pTestSceneNode->GetTransform()->Rotate(Vector3(-fRotateSpeed, 0.0f, 0.0f));

	}
}

void HrGeometryScene::OnMousePressed(HrEventMouse::EnumMouseButtonID mouseID, HrEvent* pEvent)
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

void HrGeometryScene::OnMouseReleased(HrEventMouse::EnumMouseButtonID mouseID, HrEvent* pEvent)
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

void HrGeometryScene::OnMouseMove(HrEvent* pEvent)
{
	static float s_floatX = 0;
	static float s_floatY = 0;
	HrEventMouse* pMouseEvnet = (HrEventMouse*)pEvent;
	float x = pMouseEvnet->GetX();
	float y = pMouseEvnet->GetY();

	if (m_bLeftMousePressed)
	{
		if (x - s_floatX > 0)
		{
			//m_pSceneMainCamera->GetTransform()->Rotate(Vector3(HrMath::PI() / 100, 0.0f, 0.0f));
			//m_pTestSceneNode->GetTransform()->Rotate(Vector3(HrMath::PI() / 100, 0.0f, 0.0f));
		}
		else
		{
			//m_pTestSceneNode->GetTransform()->Rotate(Vector3(-HrMath::PI() / 100, 0.0f, 0.0f));
		}
		
		if (y - s_floatY)
		{
			//m_pTestSceneNode->GetTransform()->Rotate(Vector3(0.0f, HrMath::PI() / 100, 0.0f));
		}
	}

	s_floatX = x;
	s_floatY = y;
}

