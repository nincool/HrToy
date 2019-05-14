#include "HrGeometryScene.h"
#include "HrCore/Include/Config/HrContextConfig.h"
#include "HrCore/Include/Render/HrSkyBox.h"

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
	m_pSceneMainCamera = HrSceneObjectFactory::Instance()->CreateCamera("MainCamera", HrCamera::CT_PERSPECTIVE);
	AddNode(m_pSceneMainCamera);
	m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -110.0f));
	std::shared_ptr<HrFirstPersonCameraController> pFirstPersonCameraCtrl = std::make_shared<HrFirstPersonCameraController>("TestFirstCameraCtrl", m_pSceneMainCamera->GetSceneObject().get());
	m_pSceneMainCamera->GetSceneObject()->AddComponent(pFirstPersonCameraCtrl);

	//创建直线光
	auto pDirectionLight = HrSceneObjectFactory::Instance()->CreateLightNode("TestDirectionLight", HrLight::LT_DIRECTIONAL);
	AddNode(pDirectionLight);
	pDirectionLight->GetTransform()->Rotate(Vector3(45, 45, 0));

	HrTexturePtr pTextureCube = HrDirector::Instance()->GetResourceModule()->RetriveTexture("\\SkyBox\\SkyBox01.sky", HrTexture::TEX_TYPE_CUBE_MAP);
	auto pSkyBox = HrSceneObjectFactory::Instance()->CreateSkyBoxNode("TestSkyBox", pTextureCube);
	AddNode(pSkyBox);

	auto pReflectEff = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("\\HrReflect.json");
	auto pSphere = HrSceneObjectFactory::Instance()->CreateSphereNode("TestSphere", 50, 30, 30);
	auto pEffParam = pReflectEff->GetParameterByName("texReflectCube");
	pEffParam->operator = (pTextureCube.get());
		
	pSphere->GetChildByIndex(0)->GetSceneObject()->GetRenderableComponent()->SetRenderEffect(pReflectEff);
	AddNode(pSphere);

}

void HrGeometryScene::CreateInputEvent()
{
	HrEventListenerKeyboardPtr pEventListenerKeyboard = HrMakeSharedPtr<HrEventListenerKeyboard>(HR_CALLBACK_2(HrGeometryScene::OnKeyPressed, this)
		, HR_CALLBACK_2(HrGeometryScene::OnKeyReleased, this));
	HrDirector::Instance()->GetEventSystemModule()->AddEventListener(pEventListenerKeyboard, this);

	HrEventListenerMousePtr pEventListenerMouse = HrMakeSharedPtr<HrEventListenerMouse>(HR_CALLBACK_2(HrGeometryScene::OnMousePressed, this)
		, HR_CALLBACK_2(HrGeometryScene::OnMouseReleased, this), HR_CALLBACK_1(HrGeometryScene::OnMouseMove, this));
	HrDirector::Instance()->GetEventSystemModule()->AddEventListener(pEventListenerMouse, this);
}

void HrGeometryScene::OnKeyPressed(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent)
{

}

void HrGeometryScene::OnKeyReleased(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent)
{

}

void HrGeometryScene::SceneUpdate(float fDelta)
{
	//m_pTestNode->GetTransform()->Rotate(Vector3(0, fDelta * 10, 0));
}

void HrGeometryScene::OnMousePressed(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
{

}

void HrGeometryScene::OnMouseReleased(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
{

}

void HrGeometryScene::OnMouseMove(const HrEventPtr& pEvent)
{

}

