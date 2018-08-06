#include "HrForwardLighting.h"
#include "HrCore/Include/Config/HrContextConfig.h"
#include "HrCore/Include/Render/HrInstanceBatch.h"

using namespace Hr;

HrForwardLighting::HrForwardLighting()
{
	m_bMoving = false;

	ResetKeyFlag();
}

HrForwardLighting::~HrForwardLighting()
{

}

void HrForwardLighting::ResetKeyFlag()
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

void HrForwardLighting::OnEnter()
{
	HrScene::OnEnter();

	CreateSceneElements();

	CreateInputEvent();

	HrDirector::Instance()->Schedule(HR_CALLBACK_1(HrForwardLighting::SceneUpdate, this), this, "HR_GEOMETRY_MOUSE_UPDATE", 0.01, 0, 0);
}

void HrForwardLighting::CreateSceneElements()
{
	//添加摄像机
	m_pSceneMainCamera = HrSceneObjectFactory::Instance()->CreateCamera("MainCamera", 0, 0, HrContextConfig::Instance()->GetRenderTargetViewWidth(), HrContextConfig::Instance()->GetRenderTargetViewHeight(), 0);
	AddNode(m_pSceneMainCamera);
	m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -300.0f));

	//创建直线光
	auto pDirectionLight = HrSceneObjectFactory::Instance()->CreateLightNode("TestDirectionLight", HrLight::LT_DIRECTIONAL);
	AddNode(pDirectionLight);

	m_pPointLight1 = HrSceneObjectFactory::Instance()->CreateLightNode("TestPointLight1", HrLight::LT_POINT);
	AddNode(m_pPointLight1);
	m_pPointLight1->GetTransform()->SetPosition(Vector3(-50.0f, 0.0f, -60.0f));
	m_pPointLight1->GetSceneObject()->GetComponent<HrLightComponent>()->SetDiffuse(HrColor::Red);
	m_pPointLight1->GetSceneObject()->GetComponent<HrLightComponent>()->SetDiffuse(HrColor::Red);

	m_pPointLight2 = HrSceneObjectFactory::Instance()->CreateLightNode("TestPointLight2", HrLight::LT_POINT);
	AddNode(m_pPointLight2);
	m_pPointLight2->GetTransform()->SetPosition(Vector3(50.0f, 0.0f, -60.0f));
	m_pPointLight2->GetSceneObject()->GetComponent<HrLightComponent>()->SetDiffuse(HrColor::Blue);
	m_pPointLight2->GetSceneObject()->GetComponent<HrLightComponent>()->SetDiffuse(HrColor::Blue);

	m_pPointLight3 = HrSceneObjectFactory::Instance()->CreateLightNode("TestPointLight3", HrLight::LT_POINT);
	AddNode(m_pPointLight3);
	m_pPointLight3->GetTransform()->SetPosition(Vector3(50.0f, -50.0f, -60.0f));
	m_pPointLight3->GetSceneObject()->GetComponent<HrLightComponent>()->SetDiffuse(HrColor::Green);
	m_pPointLight3->GetSceneObject()->GetComponent<HrLightComponent>()->SetDiffuse(HrColor::Green);

	m_pPointLight4 = HrSceneObjectFactory::Instance()->CreateLightNode("TestPointLight3", HrLight::LT_POINT);
	AddNode(m_pPointLight4);
	m_pPointLight4->GetTransform()->SetPosition(Vector3(-50.0f, -50.0f, -60.0f));
	m_pPointLight4->GetSceneObject()->GetComponent<HrLightComponent>()->SetDiffuse(HrColor::Yellow);
	m_pPointLight4->GetSceneObject()->GetComponent<HrLightComponent>()->SetDiffuse(HrColor::Yellow);

	m_pTestRoot = HrMakeSharedPtr<HrSceneNode>("TestRootNode");
	AddNode(m_pTestRoot);

	m_pPlane = HrSceneObjectFactory::Instance()->CreateModelNode("Model/HrTestPlan.model");
	m_pPlane->GetTransform()->SetPosition(Vector3(0.0f, -50.0f, 0.0f));
	m_pTestRoot->AddChild(m_pPlane);

	m_pBox = HrSceneObjectFactory::Instance()->CreateModelNode("Model/HrTestSphere.model");
	//auto pEffSampler = HrDirector::Instance()->GetResourceComponent()->RetriveResource<HrRenderEffect>("HrStandardSampler.json");
	//m_pBox->GetChildByName("Box001")->GetSceneObject()->GetComponent<HrRenderableComponent>()->GetRenderable()->SetRenderEffect(pEffSampler);
	m_pTestRoot->AddChild(m_pBox);



	m_pTestRoot->GetTransform()->SetPosition(Vector3(0.0f, -50.0f, 0.0f));
}

void HrForwardLighting::CreateInputEvent()
{
	HrEventListenerKeyboardPtr pEventListenerKeyboard = HrMakeSharedPtr<HrEventListenerKeyboard>(HR_CALLBACK_2(HrForwardLighting::OnKeyPressed, this)
		, HR_CALLBACK_2(HrForwardLighting::OnKeyReleased, this));
	HrDirector::Instance()->GetEventComponent()->AddEventListener(pEventListenerKeyboard, this);

	HrEventListenerMousePtr pEventListenerMouse = HrMakeSharedPtr<HrEventListenerMouse>(HR_CALLBACK_2(HrForwardLighting::OnMousePressed, this)
		, HR_CALLBACK_2(HrForwardLighting::OnMouseReleased, this), HR_CALLBACK_1(HrForwardLighting::OnMouseMove, this));
	HrDirector::Instance()->GetEventComponent()->AddEventListener(pEventListenerMouse, this);
}

void HrForwardLighting::OnKeyPressed(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent)
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

void HrForwardLighting::OnKeyReleased(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent)
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
		m_bMoving = !m_bMoving;
		break;
	case HrEventKeyboard::EnumKeyCode::KEY_1:
		m_bKey1Pressed = false;
		break;
	default:
		break;
	}
}

void HrForwardLighting::SceneUpdate(float fDelta)
{
	float fSpeed = 1.0f;
	float fRotateSpeed = 5;
	if (m_bKeyAPressed)
	{
		//m_pTestRoot->GetTransform()->Translate(Vector3(-fSpeed, 0, 0));
	}
	else if (m_bKeyWPressed)
	{
		m_pPointLight1->GetTransform()->Translate(Vector3(0.0f, fSpeed, 0.0f));
	}
	else if (m_bKeySPressed)
	{
		m_pPointLight1->GetTransform()->Translate(Vector3(0.0f, -fSpeed, 0.0f));
	}
	else if (m_bKeyDPressed)
	{
		//m_pPlane->GetTransform()->Translate(Vector3(fSpeed, 0.0f, 0.0f));
	}
	else if (m_bKey0Pressed)
	{
		//m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -fSpeed));
	}
	else if (m_bKey1Pressed)
	{
		//m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, fSpeed));
	}

	if (m_bMoving)
	{
		static bool s_bRight;
		if (m_pTestRoot->GetTransform()->GetWorldPosition().x() > 200)
		{
			s_bRight = false;
		}
		else if (m_pTestRoot->GetTransform()->GetWorldPosition().x() < -200)
		{
			s_bRight = true;
		}
		m_pTestRoot->GetTransform()->Translate(Vector3(s_bRight ? fSpeed : -fSpeed, 0.0f, 0.0f));
	}

}

void HrForwardLighting::OnMousePressed(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
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

void HrForwardLighting::OnMouseReleased(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
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

void HrForwardLighting::OnMouseMove(const HrEventPtr& pEvent)
{
	HrEventMousePtr pMouseEvent = HrCheckPointerCast<HrEventMouse>(pEvent);
	static float s_floatX = 0;
	static float s_floatY = 0;

	float x = pMouseEvent->GetX();
	float y = pMouseEvent->GetY();
	float z = pMouseEvent->GetZ();

	float fSpeed = 0.01f;

	if (m_bRightMousePressed)
	{
		//m_pBox->GetTransform()->Translate(Vector3(0, 0, fSpeed * z));
		//m_pSceneMainCamera->GetTransform()->Translate(Vector3(0, 0, fSpeed * z));
		m_pTestRoot->GetTransform()->Translate(Vector3(0, 0, fSpeed * z));
	}

}

