#include "stdafx.h"
#include "HrRenderApp.h"

#include <sstream>
#include "HrEngine.h"


using namespace Hr;


///////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////
HrRenderAxis::HrRenderAxis()
{
	CreateAxisMesh();
}

HrRenderAxis::~HrRenderAxis()
{

}

void HrRenderAxis::CreateAxisMesh()
{
	m_pMesh = HrMakeSharedPtr<HrMesh>();
	auto pSubMesh = m_pMesh->AddSubMesh("0_Axis");
	{
		float fLineLength = 100.0f;
		SAxisVertex pVertexBuff[6];
		pVertexBuff[0].position = Vector4(0, 0, 0, 1);
		pVertexBuff[0].color = Vector4(1, 0, 0, 1);
		pVertexBuff[1].position = Vector4(fLineLength, 0, 0, 1);
		pVertexBuff[1].color = Vector4(1, 0, 0, 1);
		pVertexBuff[2].position = Vector4(0, 0, 0, 1);
		pVertexBuff[2].color = Vector4(0, 1, 0, 1);;
		pVertexBuff[3].position = Vector4(0, fLineLength, 0, 1);
		pVertexBuff[3].color = Vector4(0, 1, 0, 1);
		pVertexBuff[4].position = Vector4(0, 0, 0, 1);
		pVertexBuff[4].color = Vector4(0, 0, 1, 1);
		pVertexBuff[5].position = Vector4(0, 0, fLineLength, 1);
		pVertexBuff[5].color = Vector4(0, 0, 1, 1);

		std::vector<HrVertexElement> vecVertexElement;
		vecVertexElement.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT4));
		vecVertexElement.push_back(HrVertexElement(VEU_COLOR, VET_FLOAT4));

		pSubMesh->GetRenderLayout()->BindVertexBuffer((char*)pVertexBuff
			, sizeof(pVertexBuff)
			, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
			, vecVertexElement);
	}

	pSubMesh->GetRenderLayout()->SetTopologyType(TT_LINELIST);

	auto pMaterial = HrDirector::Instance()->GetResourceComponent()->RetriveResource<HrMaterial>();
	m_mapMaterials[pSubMesh->GetName()] = pMaterial;
	pSubMesh->SetMaterial(pMaterial);
}

///////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////

HrEditorScene::HrEditorScene() 
{
	m_bCameraMatrixDirty = false;
}

HrEditorScene::~HrEditorScene()
{

}

void HrEditorScene::OnEnter()
{
	HrScene::OnEnter();

	m_fFrameWidth = HrDirector::Instance()->GetRenderComponent()->GetRenderFrameBuffer()->GetFrameWidth();
	m_fFrameHeight = HrDirector::Instance()->GetRenderComponent()->GetRenderFrameBuffer()->GetFrameHeight();
	m_bRButtonDown = false;

	CreateSceneElements();
}

void HrEditorScene::CreateSceneElements()
{
	//添加摄像机
	m_pGodCamera = HrSceneObjectFactory::Instance()->CreateCamera("GodCamera");
	AddNode(m_pGodCamera);
	m_pGodCamera->GetTransform()->Translate(Vector3(0.0f, 100.0f, -30.0f));
	m_pGodCamera->GetTransform()->SetRotation(Vector3(20.0f, 0.0f, 0.0f));
	m_pCameraCom = m_pGodCamera->GetSceneObject()->GetComponent<HrCameraComponet>();
	m_pCameraCom->SetFarPlane(300.0f);
	m_pTrackBallCameraCtrl = m_pGodCamera->GetSceneObject()->AddComponent<HrTrackBallCameraController>();

	//创建直线光
	auto pDirectionLight = HrSceneObjectFactory::Instance()->CreateLightNode("TestDirectionLight", HrLight::LT_DIRECTIONAL);
	AddNode(pDirectionLight);
	
	CreateAxisNode();

	m_pEleRoot = HrMakeSharedPtr<HrSceneNode>("TestRootNode");
	AddNode(m_pEleRoot);

	auto pGridNode = HrSceneObjectFactory::Instance()->CreateGridPlan();
	m_pEleRoot->AddChild(pGridNode);
	pGridNode->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

	m_pBox = HrSceneObjectFactory::Instance()->CreateModelNode("Model/HrTestSphere.model");
	m_pBox->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	m_pBox->GetTransform()->SetScale(Vector3(0.1f, 0.1f, 0.1f));
	m_pEleRoot->AddChild(m_pBox);

	UpdateAxisPos();
}

void HrEditorScene::CreateAxisNode()
{
	auto pRenderEffect = HrDirector::Instance()->GetResourceComponent()->RetriveResource<HrRenderEffect>("Media/Effect/Hlsl/HrMeshConvert.json");

	m_pAxisModel = std::make_shared<HrRenderAxis>();

	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
	HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
	pSceneNode->SetSceneObject(pSceneObj);
	pSceneNode->SetName("AxisRoot");

	for (size_t i = 0; i < m_pAxisModel->GetMesh()->GetSubMeshNum(); ++i)
	{
		HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
		HrRenderableComponentPtr pRenderableCom = pSceneObj->AddComponent<HrRenderableComponent>();
		HrRenderablePtr pRenderable = HrMakeSharedPtr<HrStaticMeshRenderable>();
		pRenderableCom->SetRenderable(pRenderable);
		pRenderable->SetSubMesh(m_pAxisModel->GetMesh()->GetSubMesh(i));
		pRenderable->SetRenderEffect(pRenderEffect);

		HrSceneNodePtr pNode = HrMakeSharedPtr<HrSceneNode>(m_pAxisModel->GetMesh()->GetSubMesh(i)->GetName());
		pNode->SetSceneObject(pSceneObj);
		pSceneNode->AddChild(pNode);
	}

	AddNode(pSceneNode);
	pSceneNode->GetTransform()->SetPosition(Vector3(0, 0, 0));

	m_pAxisNode = pSceneNode;
}

void HrEditorScene::Update(float fDelta)
{
	HrScene::Update(fDelta);
	if (m_bCameraMatrixDirty)
	{
		UpdateAxisPos();
		m_bCameraMatrixDirty = false;
	}
}


void HrEditorScene::UpdateAxisPos()
{
	HrRenderFramePtr pRenderFrame = HrDirector::Instance()->GetRenderComponent()->GetRenderFrameBuffer();
	uint32 nFrameWidth = pRenderFrame->GetFrameWidth();
	uint32 nFrameHeight = pRenderFrame->GetFrameHeight();

	float fAxisXPos = -1 + 100 / (static_cast<float>(nFrameWidth));
	float fAxisYPos = -1 + 100 / (static_cast<float>(nFrameHeight));
	float fAxisZPos = 0.1f;

	Vector3 vWorldPos = HrMath::TransformCoord(Vector3(fAxisXPos, fAxisYPos, fAxisZPos), m_pCameraCom->GetCamera()->GetInverseViewProjMatrix());
	m_pAxisNode->GetTransform()->SetPosition(vWorldPos);

	float fAxisXOrigin = -1 + 95 / (static_cast<float>(nFrameWidth));
	float fAxisZOrigin = 0.1f;
	Vector3 vWorldOrigin = HrMath::TransformCoord(Vector3(fAxisXOrigin, fAxisYPos, fAxisZOrigin), m_pCameraCom->GetCamera()->GetInverseViewProjMatrix());

	float fLength = HrMath::Length(vWorldOrigin - vWorldPos);
	m_pAxisNode->GetTransform()->SetScale(Vector3(fLength, fLength, fLength));
}

void HrEditorScene::OnMouseMove(float fX, float fY)
{
	float fProjX = Convert2ScreenPosX(fX);
	float fProjY = Convert2ScreenPosY(fY);

	float fDiffValueX = fProjX - m_fOldMouseX;
	float fDiffValueY = fProjY - m_fOldMouseY;

	m_fOldMouseX = fProjX;
	m_fOldMouseY = fProjY;

	if (m_bRButtonDown)
	{
		if (std::abs(fDiffValueX) > HrMath::EPSILON || std::abs(fDiffValueY) > HrMath::EPSILON)
		{
			m_bCameraMatrixDirty = true;
			m_pTrackBallCameraCtrl->Rotate(Vector3(fDiffValueX, fDiffValueY, 0));
		}
	}
}

void HrEditorScene::OnRMouseButtonDown(float fX, float fY)
{
	m_bRButtonDown = true;
}

void HrEditorScene::OnRMouseButtonUp(float fX, float fY)
{
	m_bRButtonDown = false;
}

float HrEditorScene::Convert2ProjPosX(float fX)
{
	return fX - m_fFrameWidth / 2;
}

float HrEditorScene::Convert2ProjPosY(float fY)
{
	return m_fFrameHeight / 2 - fY;
}

float HrEditorScene::Convert2ScreenPosX(float fX)
{
	return fX;
}

float HrEditorScene::Convert2ScreenPosY(float fY)
{
	return m_fFrameHeight - fY;
}

void HrEditorScene::OnMouseWheel(float fDelta)
{
	m_pTrackBallCameraCtrl->Zoom(fDelta);

	m_bCameraMatrixDirty = true;
}

////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////

HrRenderApp::HrRenderApp(HWND hWnd)
{
	m_hWnd = hWnd;



#pragma warning(push)
#pragma warning(disable: 4996) 
	if (!AllocConsole() || !freopen("CONOUT$", "w", stdout))
		AfxMessageBox(_T("InitConsoleWindow Failed!")); //分配控制台在重定向输出流至控制台
#pragma warning(pop)
}

HrRenderApp::~HrRenderApp()
{
}

bool HrRenderApp::ApplicationDidFinishLaunching()
{
	LoadAssets();
	CreateScene();

	return true;
}

void HrRenderApp::ApplicationDidEnterBackground()
{
}

void HrRenderApp::ApplicationWillEnterForeground()
{
}

bool HrRenderApp::Destroy()
{
	bool bRet = HrAppWindows::Destroy();

	return bRet;
}

void HrRenderApp::LoadAssets()
{
}

void HrRenderApp::CreateScene()
{
	m_pEditorScene = HrMakeSharedPtr<HrEditorScene>();
	HrDirector::Instance()->GetSceneComponent()->RunScene(m_pEditorScene);
}

void HrRenderApp::Run()
{
	if (!HrDirector::Instance()->Init(m_hWnd))
	{
		HRERROR(_T("Application Run Error!"));
	}
	else
	{
		ApplicationDidFinishLaunching();
	}
}

void HrRenderApp::RenderOnce()
{
	HrDirector::Instance()->LoopOnce();
}

void HrRenderApp::OnMouseMove(float fX, float fY)
{
	m_pEditorScene->OnMouseMove(fX, fY);
}

void HrRenderApp::OnRMouseButtonDown(float fX, float fY)
{
	m_pEditorScene->OnRMouseButtonDown(fX, fY);
}

void HrRenderApp::OnRMouseButtonUp(float fX, float fY)
{
	m_pEditorScene->OnRMouseButtonUp(fX, fY);
}

void HrRenderApp::OnMouseWheel(float fDelta)
{
	m_pEditorScene->OnMouseWheel(fDelta);
}



