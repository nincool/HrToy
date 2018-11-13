#include "HrInstanceBatchTest.h"
#include "HrCore/Include/Config/HrContextConfig.h"
#include "HrCore/Include/Render/HrInstanceBatch.h"

using namespace Hr;

HrInstanceBatchTest::HrInstanceBatchTest()
{
	ResetKeyFlag();
}

HrInstanceBatchTest::~HrInstanceBatchTest()
{

}

void HrInstanceBatchTest::ResetKeyFlag()
{
	m_bKeyAPressed = false;
	m_bKeyWPressed = false;
	m_bKeySPressed = false;
	m_bKeyDPressed = false;
}

void HrInstanceBatchTest::OnEnter()
{
	HrScene::OnEnter();

	CreateSceneElements();

	CreateInputEvent();

	HrDirector::Instance()->Schedule(HR_CALLBACK_1(HrInstanceBatchTest::SceneUpdate, this), this, "HR_GEOMETRY_MOUSE_UPDATE", 0.01, 0, 0);
}

void HrInstanceBatchTest::CreateSceneElements()
{
	//添加摄像机
	m_pSceneMainCamera = HrSceneObjectFactory::Instance()->CreateCamera("MainCamera", 0, 0, HrContextConfig::Instance()->GetRenderTargetViewWidth(), HrContextConfig::Instance()->GetRenderTargetViewHeight(), 0);
	AddNode(m_pSceneMainCamera);
	m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -10.0f));

	//创建直线光
	auto pDirectionLight = HrSceneObjectFactory::Instance()->CreateLightNode("TestDirectionLight", HrLight::LT_DIRECTIONAL);
	AddNode(pDirectionLight);

	HrRenderEffectPtr pRenderEffect = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("Media/HrShader/HrSimple.json", true, true);
	BOOST_ASSERT(pRenderEffect);

	//m_pTestNode = HrSceneObjectFactory::Instance()->CreateModelNode("Model/HrPrefab3.model");
	//m_pTestNode->GetChildByName("Box01")->GetSceneObject()->GetComponent<HrRenderableComponent>()->GetRenderable()->SetRenderEffect(pRenderEffect);
	//AddNode(m_pTestNode);

	//HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
	//HrRenderableComponentPtr pRenderableCom = pSceneObj->AddComponent<HrRenderableComponent>();
	//const HrRenderablePtr& pRenderable = pRenderableCom->CreateRenderable();
	//pRenderable->SetSubMesh(pModel->GetMesh()->GetSubMesh(i));
	//pRenderable->SetRenderEffect(HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>());

	//HrSceneNodePtr pNode = HrMakeSharedPtr<HrSceneNode>(pModel->GetMesh()->GetSubMesh(i)->GetName());
	//pNode->SetSceneObject(pSceneObj);
	//pSceneNode->AddChild(pNode);

	//尝试创建一个InstanceBatch节点
	//SubMesh 限定只能有一个
	//HrModelPtr pModel = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrModel>("Model/HrPrefab3.model", true, true);
	//BOOST_ASSERT(pModel->GetMesh()->GetSubMeshNum() == 1);

	//HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
	//HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
	//pSceneNode->SetSceneObject(pSceneObj);
	//HrRenderableComponentPtr pRenderableCom = pSceneObj->AddComponent<HrRenderableComponent>();
	//HrRenderablePtr pRenderable = HrMakeSharedPtr<HrStaticMeshRenderable>(pModel->GetMesh()->GetSubMesh(0));
	//pRenderableCom->SetRenderable(pRenderable);

	//HrInstanceBatchComponentPtr pInsBatchCom = pSceneObj->AddComponent<HrInstanceBatchComponent>();
	//auto pInsSceneNode = pInsBatchCom->CreateInstance();
	//pInsSceneNode->GetTransform()->Translate(Vector3(-5, 3.0, 0.0));
	//pInsSceneNode = pInsBatchCom->CreateInstance();
	//pInsSceneNode->GetTransform()->Translate(Vector3(5, 3.0, 0.0));
	//pInsSceneNode = pInsBatchCom->CreateInstance();
	//pInsSceneNode->GetTransform()->Translate(Vector3(-5, 0.0, 0.0));
	//pInsSceneNode = pInsBatchCom->CreateInstance();
	//pInsSceneNode->GetTransform()->Translate(Vector3(5, 0.0, 0.0));
	//pInsSceneNode = pInsBatchCom->CreateInstance();
	//pInsSceneNode->GetTransform()->Translate(Vector3(-5, -3.0, 0.0));
	//pInsSceneNode = pInsBatchCom->CreateInstance();
	//pInsSceneNode->GetTransform()->Translate(Vector3(5, -3.0, 0.0));
	//m_pTestNode = pInsSceneNode;

	//AddNode(pSceneNode);
}

//HrSceneNodePtr HrSceneObjectFactory::CreateModelNode(const std::string& strName)
//{
//	HrModelPtr pPrefabModel = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrModel>(strName, true, true);
//	if (pPrefabModel == nullptr)
//	{
//		BOOST_ASSERT(false);
//		return nullptr;
//	}
//
//	return CreateSceneNode(pPrefabModel);
//}
//
//HrSceneNodePtr HrSceneObjectFactory::CreateSceneNode(HrModelPtr& pModel)
//{
//	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
//	HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
//	pSceneNode->SetSceneObject(pSceneObj);
//
//	for (size_t i = 0; i < pModel->GetMesh()->GetSubMeshNum(); ++i)
//	{
//		HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
//		HrRenderableComponentPtr pRenderableCom = pSceneObj->AddComponent<HrRenderableComponent>();
//		const HrRenderablePtr& pRenderable = pRenderableCom->CreateRenderable();
//		pRenderable->SetSubMesh(pModel->GetMesh()->GetSubMesh(i));
//		pRenderable->SetRenderEffect(HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>());
//
//		HrSceneNodePtr pNode = HrMakeSharedPtr<HrSceneNode>(pModel->GetMesh()->GetSubMesh(i)->GetName());
//		pNode->SetSceneObject(pSceneObj);
//		pSceneNode->AddChild(pNode);
//	}
//
//	return pSceneNode;
//}

void HrInstanceBatchTest::CreateInputEvent()
{
	HrEventListenerKeyboardPtr pEventListenerKeyboard = HrMakeSharedPtr<HrEventListenerKeyboard>(HR_CALLBACK_2(HrInstanceBatchTest::OnKeyPressed, this)
		, HR_CALLBACK_2(HrInstanceBatchTest::OnKeyReleased, this));
	HrDirector::Instance()->GetEventSystemModule()->AddEventListener(pEventListenerKeyboard, this);

	HrEventListenerMousePtr pEventListenerMouse = HrMakeSharedPtr<HrEventListenerMouse>(HR_CALLBACK_2(HrInstanceBatchTest::OnMousePressed, this)
		, HR_CALLBACK_2(HrInstanceBatchTest::OnMouseReleased, this), HR_CALLBACK_1(HrInstanceBatchTest::OnMouseMove, this));
	HrDirector::Instance()->GetEventSystemModule()->AddEventListener(pEventListenerMouse, this);
}

void HrInstanceBatchTest::OnKeyPressed(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent)
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

void HrInstanceBatchTest::OnKeyReleased(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent)
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

void HrInstanceBatchTest::SceneUpdate(float fDelta)
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
}

void HrInstanceBatchTest::OnMousePressed(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
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

void HrInstanceBatchTest::OnMouseReleased(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent)
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

void HrInstanceBatchTest::OnMouseMove(const HrEventPtr& pEvent)
{
	HrEventMousePtr pMouseEvent = HrCheckPointerCast<HrEventMouse>(pEvent);
	static float s_floatX = 0;
	static float s_floatY = 0;

	float x = pMouseEvent->GetX();
	float y = pMouseEvent->GetY();
	float z = pMouseEvent->GetZ();

	float fSpeed = 0.01f;
	//m_pTestNode->GetTransform()->Translate(Vector3(0, 0, fSpeed * z));
}

