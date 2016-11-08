#include "HrGeometryScene.h"
#include "HrCore/Include/Asset/HrGeometryFactory.h"
#include "HrCore/Include/Asset/HrGeometryBox.h"
#include "HrCore/Include/Scene/HrCameraNode.h"
#include "HrCore/Include/Scene/HrTransform.h"
#include "HrCore/Include/Asset/HrComponentFactory.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrCore/Include/Kernel/HrScheduler.h"

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

	HrDirector::Instance()->GetScheduler()->Schedule(HR_CALLBACK_1(HrGeometryScene::MouseUpdate, this), this, "HR_GEOMETRY_MOUSE_UPDATE", 0.01, 0, 0);
}

void HrGeometryScene::CreateSceneElements()
{
	//Ìí¼ÓÉãÏñ»ú
	m_pSceneMainCamera = HrDirector::Instance()->GetComponentFactory()->CreateCamera();
	AddSceneNode(m_pSceneMainCamera);

	HrSceneNode* pBox = HrDirector::Instance()->GetComponentFactory()->CreateBox();
	AddSceneNode(pBox);
}

void HrGeometryScene::CreateInputEvent()
{
	HrEventListenerKeyboardPtr pEventListenerKeyboard = MakeSharedPtr<HrEventListenerKeyboard>(HR_CALLBACK_2(HrGeometryScene::OnKeyPressed, this)
		, HR_CALLBACK_2(HrGeometryScene::OnKeyReleased, this));

	HrEventDispatcher::Instance()->AddEventListener(CheckPointerCast<HrEventListener>(pEventListenerKeyboard));
}

void HrGeometryScene::OnKeyPressed(HrEventKeyboard::EnumKeyCode keyCode, HrEvent* pEvent)
{
	ResetKeyFlag();
	switch (keyCode)
	{
	case Hr::HrEventKeyboard::EnumKeyCode::KEY_A:
		m_bKeyAPressed = true;
		break;
	case Hr::HrEventKeyboard::EnumKeyCode::KEY_D:
		m_bKeyDPressed = true;
		break;
	case Hr::HrEventKeyboard::EnumKeyCode::KEY_W:
		m_bKeyWPressed = true;
		break;
	case Hr::HrEventKeyboard::EnumKeyCode::KEY_S:
		m_bKeySPressed = true;
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
	default:
		break;
	}
}

void HrGeometryScene::MouseUpdate(float fDelta)
{
	std::cout << "MouseUpdate" << std::endl;
	if (m_bKeyAPressed)
	{
		m_pSceneMainCamera->GetTransfrom()->Translate(Vector3(-0.1, 0, 0));
	}
	else if (m_bKeyWPressed)
	{
		m_pSceneMainCamera->GetTransfrom()->Translate(Vector3(0.0, 0.1, 0));
	}
	else if (m_bKeySPressed)
	{
		m_pSceneMainCamera->GetTransfrom()->Translate(Vector3(0.0f, -0.1f, 0));
	}
	else if (m_bKeyDPressed)
	{
		m_pSceneMainCamera->GetTransfrom()->Translate(Vector3(0.1f, 0.0f, 0.0f));
	}
}

