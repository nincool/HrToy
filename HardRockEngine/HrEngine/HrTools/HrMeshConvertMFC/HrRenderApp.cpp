#include "stdafx.h"
#include "HrRenderApp.h"

#include <sstream>
#include "HrEngine.h"
#include "HrConvertUtil.h"

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
		pVertexBuff[0].position = Vector3(0, 0, 0);
		pVertexBuff[0].color = Vector3(1, 0, 0);
		pVertexBuff[1].position = Vector3(fLineLength, 0, 0);
		pVertexBuff[1].color = Vector3(1, 0, 0);
		pVertexBuff[2].position = Vector3(0, 0, 0);
		pVertexBuff[2].color = Vector3(0, 1, 0);
		pVertexBuff[3].position = Vector3(0, fLineLength, 0);
		pVertexBuff[3].color = Vector3(0, 1, 0);
		pVertexBuff[4].position = Vector3(0, 0, 0);
		pVertexBuff[4].color = Vector3(0, 0, 1);
		pVertexBuff[5].position = Vector3(0, 0, fLineLength);
		pVertexBuff[5].color = Vector3(0, 0, 1);

		std::vector<HrVertexElement> vecVertexElement;
		vecVertexElement.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
		vecVertexElement.push_back(HrVertexElement(VEU_COLOR, VET_FLOAT3));

		pSubMesh->GetRenderLayout()->BindVertexBuffer((char*)pVertexBuff
			, sizeof(pVertexBuff)
			, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
			, vecVertexElement);

		pSubMesh->SetMeshAABB(AABBox(Vector3(0, 0, 0), Vector3(fLineLength, fLineLength, fLineLength)));
	}

	pSubMesh->GetRenderLayout()->SetTopologyType(TT_LINELIST);

	auto pMaterial = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrMaterial>(m_strFileName, true, true);
	m_mapMaterials[pSubMesh->GetName()] = pMaterial;
	pSubMesh->SetMaterial(pMaterial);
}

///////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////

HrEditorScene::HrEditorScene() 
{
	m_bCameraMatrixDirty = false;
	m_pConvertUtil = std::make_shared<HrConvertUtil>();
}

HrEditorScene::~HrEditorScene()
{

}

void HrEditorScene::OnEnter()
{
	HrScene::OnEnter();

	m_fFrameWidth = HrContextConfig::Instance()->GetRTVWidth();
	m_fFrameHeight = HrContextConfig::Instance()->GetRTVHeight();
	m_bRButtonDown = false;

	CreateSceneElements();
}

void HrEditorScene::CreateSceneElements()
{
	//添加摄像机
	m_pGodCamera = HrSceneObjectFactory::Instance()->CreateCamera("GodCamera");
	AddNode(m_pGodCamera);
	m_pGodCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -200.0f));
	m_pCameraCom = m_pGodCamera->GetSceneObject()->GetComponent<HrCameraComponet>();
	m_pCameraCom->SetFarPlane(1000.0f);
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

	UpdateAxisPos();
}

const HrModelDataInfo& HrEditorScene::LoadOriginalMeshData(const std::string& strFileName)
{
	if (m_pModel)
	{
		m_pEleRoot->RemoveChild(m_pModel);
	}

	bool bHrMesh = false;
	if (HrFileUtils::Instance()->GetFileSuffix(strFileName) == "hrmesh")
	{
		m_pModel = HrSceneObjectFactory::Instance()->CreateModelNode(strFileName);
		bHrMesh = true;
	}
	else
	{
		m_pConvertUtil->LoadOriginalData(strFileName);
		m_pModel = m_pConvertUtil->CreateSceneNode();
	}

	if (m_pModel)
	{
		m_pModel->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		m_pEleRoot->AddChild(m_pModel);
	}

	if (bHrMesh)
	{
		HrMeshModelObjectPtr pPrefabModel = HrCheckPointerCast<HrMeshModelObject>(HrDirector::Instance()->GetResourceModule()->RetriveResource<HrMeshModel>(strFileName));
		return pPrefabModel->GetModelLoader()->GetModelDataInfo();
	}
	else
	{
		return m_pConvertUtil->GetModelDataInfo();
	}
}

void HrEditorScene::CreateAxisNode()
{
	m_pAxisModel = std::make_shared<HrRenderAxis>();

	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
	pSceneNode->SetName("AxisRoot");

	for (uint32 i = 0; i < m_pAxisModel->GetMesh()->GetSubMeshNum(); ++i)
	{
		HrSceneNodePtr pNode = HrMakeSharedPtr<HrSceneNode>(m_pAxisModel->GetMesh()->GetSubMesh(i)->GetName());

		HrSceneObjectPtr pSceneObj = pNode->GetSceneObject();
		HrRenderableComponentPtr pRenderableCom = pSceneObj->AddComponent<HrRenderableComponent>();
		HrRenderablePtr pRenderable = HrMakeSharedPtr<HrStaticMeshRenderable>(m_pAxisModel->GetMesh()->GetSubMesh(i));
		pRenderableCom->SetRenderable(pRenderable);

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
	if (!m_pAxisNode)
	{
		return;
	}
	
	uint32 nFrameWidth = HrContextConfig::Instance()->GetRTVWidth();
	uint32 nFrameHeight = HrContextConfig::Instance()->GetRTVHeight();

	float fAxisXPos = -1 + 100 / (static_cast<float>(nFrameWidth));
	float fAxisYPos = -1 + 100 / (static_cast<float>(nFrameHeight));
	float fAxisZPos = 0.1f;

	Vector3 vWorldPos = HrMath::TransformCoord(Vector3(fAxisXPos, fAxisYPos, fAxisZPos), m_pCameraCom->GetCamera()->GetInverseViewProjMatrix());
	m_pAxisNode->GetTransform()->SetPosition(vWorldPos);

	float fAxisXOrigin = -1 + 95 / (static_cast<float>(nFrameWidth));
	float fAxisZOrigin = 0.1f;
	Vector3 vWorldOrigin = HrMath::TransformCoord(Vector3(fAxisXOrigin, fAxisYPos, fAxisZOrigin), m_pCameraCom->GetCamera()->GetInverseViewProjMatrix());

	float fLength = HrMath::Length(vWorldOrigin - vWorldPos) * 0.3;
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
	m_pTrackBallCameraCtrl->Forward(fDelta);

	m_bCameraMatrixDirty = true;
}

void HrEditorScene::SaveConvertMeshData(const std::string& strFileName)
{
	m_pConvertUtil->WriteModelDataToFile(strFileName);
}

////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////

HrRenderApp::HrRenderApp(HWND hWnd)
{
	m_hWnd = hWnd;
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
	HrDirector::Instance()->GetSceneModule()->RunScene(m_pEditorScene);
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

const HrModelDataInfo& HrRenderApp::LoadOriginalMeshData(const std::string& strFileName)
{
	return m_pEditorScene->LoadOriginalMeshData(strFileName);
}

void HrRenderApp::SaveConvertMeshData(const std::string& strFileName)
{
	m_pEditorScene->SaveConvertMeshData(strFileName);
}

