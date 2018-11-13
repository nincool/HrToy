#include "stdafx.h"
#include "HrRenderApp.h"

#include <sstream>
#include "HrEngine.h"
#include "HrConvertUtil.h"
#include <experimental/filesystem>
#include <iostream>
#include <fstream>

using namespace Hr;
using namespace std::experimental;

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
		pVertexBuff[0].color = Vector4(1, 0, 0, 1);
		pVertexBuff[1].position = Vector3(fLineLength, 0, 0);
		pVertexBuff[1].color = Vector4(1, 0, 0, 1);
		pVertexBuff[2].position = Vector3(0, 0, 0);
		pVertexBuff[2].color = Vector4(0, 1, 0, 1);;
		pVertexBuff[3].position = Vector3(0, fLineLength, 0);
		pVertexBuff[3].color = Vector4(0, 1, 0, 1);
		pVertexBuff[4].position = Vector3(0, 0, 0);
		pVertexBuff[4].color = Vector4(0, 0, 1, 1);
		pVertexBuff[5].position = Vector3(0, 0, fLineLength);
		pVertexBuff[5].color = Vector4(0, 0, 1, 1);

		std::vector<HrVertexElement> vecVertexElement;
		vecVertexElement.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
		vecVertexElement.push_back(HrVertexElement(VEU_COLOR, VET_FLOAT4));

		pSubMesh->GetRenderLayout()->BindVertexBuffer((char*)pVertexBuff
			, sizeof(pVertexBuff)
			, HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE
			, vecVertexElement);
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
	//m_pConvertUtil = std::make_shared<HrConvertUtil>();
}

HrEditorScene::~HrEditorScene()
{

}

void HrEditorScene::OnEnter()
{
	HrScene::OnEnter();

	m_fFrameWidth = HrDirector::Instance()->GetRenderModule()->GetRenderFrameBuffer()->GetFrameWidth();
	m_fFrameHeight = HrDirector::Instance()->GetRenderModule()->GetRenderFrameBuffer()->GetFrameHeight();
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
	m_pCameraCom->SetFarPlane(500.0f);
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

	m_pModelRoot = HrMakeSharedPtr<HrSceneNode>("ModelRoot");
	m_pEleRoot->AddChild(m_pModelRoot);
	m_pModelRoot->GetTransform()->SetPosition(Vector3::Zero());
}

void HrEditorScene::LoadOriginalMeshData(const std::string& strFileName)
{
	if (HrFileUtils::Instance()->GetFileSuffix(strFileName) == "hrmesh")
	{
		HrMeshModelPtr pPrefabModel = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrMeshModel>(strFileName, true, true);
		if (pPrefabModel == nullptr)
		{
			BOOST_ASSERT(false);
			return;
		}
		HrSceneNodePtr pSceneNode = HrSceneObjectFactory::Instance()->CreateMeshModelNode(pPrefabModel);
		m_pModelRoot->AddChild(pSceneNode);
		m_vecModelNodes.push_back(pSceneNode);

		HrMeshModelObjectPtr pModelObj = HrCheckPointerCast<HrMeshModelObject>(pPrefabModel);
		const HrModelDataInfo& modelDataInfo = pModelObj->GetModelLoader()->GetModelDataInfo();
		const HrModelDataInfo* pModelDataInfo = &modelDataInfo;
		m_vecModelDataInfos.push_back(pModelDataInfo);
	}
}

void HrEditorScene::LoadPrefabData(const std::string& strFileName)
{
	m_pModelRoot->RemoveChildren();
	m_vecModelDataInfos.clear();

	if (HrFileUtils::Instance()->GetFileSuffix(strFileName) == "hrpref")
	{
		std::string strContentData = HrFileUtils::Instance()->GetFileString(strFileName);
		rapidjson::Document d;
		d.Parse<0>(strContentData.c_str());
		if (d.HasParseError())
		{
			int nErrorCode = d.GetParseError();
			int nOffset = d.GetErrorOffset();

			return;
		}
		const rapidjson::Value& modelsInfo = d["Models"];
		int nModelCount = modelsInfo["ModelCount"].GetInt();
		for (int i = 0; i < nModelCount; ++i)
		{
			const std::string strModelRoot = HrStringUtil::StringFormat("Node_%d", i);
			const rapidjson::Value& nodeInfo = modelsInfo[strModelRoot.c_str()];
			std::string strModelFile = nodeInfo["File"].GetString();
			
			std::string strLocationPath = HrFileUtils::Instance()->GetFilePath(strFileName);
			filesystem::path locationPath(strLocationPath);
			filesystem::path filePath = locationPath / strModelFile;
			if (!filesystem::exists(filePath))
			{
				BOOST_ASSERT(false);
				return;
			}

			Vector3 v3Position = HrStringUtil::GetFloat3FromString(nodeInfo["Position"].GetString(), ",");
			Vector3 v3Rotate = HrStringUtil::GetFloat3FromString(nodeInfo["Rotate"].GetString(), ",");
			Vector3 v3Scale = HrStringUtil::GetFloat3FromString(nodeInfo["Scale"].GetString(), ",");

			HrDirector::Instance()->GetResourceModule()->RemoveResource<HrMeshModel>(filePath.string());

			HrMeshModelPtr pPrefabModel = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrMeshModel>(filePath.string(), true, true);
			if (pPrefabModel == nullptr)
			{
				BOOST_ASSERT(false);
				return;
			}
			//todo remove resource

			HrSceneNodePtr pSceneNode = HrSceneObjectFactory::Instance()->CreateMeshModelNode(pPrefabModel);
			m_pModelRoot->AddChild(pSceneNode);
			pSceneNode->GetTransform()->SetPosition(v3Position);
			pSceneNode->GetTransform()->SetRotation(v3Rotate);
			pSceneNode->GetTransform()->SetScale(v3Scale);
			m_vecModelNodes.push_back(pSceneNode);
			
			HrMeshModelObjectPtr pModelObj = HrCheckPointerCast<HrMeshModelObject>(pPrefabModel);
			const HrModelDataInfo& modelDataInfo = pModelObj->GetModelLoader()->GetModelDataInfo();
			const HrModelDataInfo* pModelDataInfo = &modelDataInfo;
			m_vecModelDataInfos.push_back(pModelDataInfo);
		}
	}
}

void HrEditorScene::CreateAxisNode()
{
	auto pRenderEffect = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("Media/Effect/Hlsl/HrMeshConvert.json");

	m_pAxisModel = std::make_shared<HrRenderAxis>();

	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();

	pSceneNode->SetName("AxisRoot");

	for (uint32 i = 0; i < m_pAxisModel->GetMesh()->GetSubMeshNum(); ++i)
	{
		HrSceneNodePtr pNode = HrMakeSharedPtr<HrSceneNode>(m_pAxisModel->GetMesh()->GetSubMesh(i)->GetName());

		HrSceneObjectPtr pSceneObj = pNode->GetSceneObject();
		HrRenderableComponentPtr pRenderableCom = pSceneObj->AddComponent<HrRenderableComponent>();
		HrRenderablePtr pRenderable = HrMakeSharedPtr<HrStaticMeshRenderable>();
		pRenderableCom->SetRenderable(pRenderable);
		pRenderable->SetSubMesh(m_pAxisModel->GetMesh()->GetSubMesh(i));
		pRenderable->SetRenderEffect(pRenderEffect);

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
	HrRenderFramePtr pRenderFrame = HrDirector::Instance()->GetRenderModule()->GetRenderFrameBuffer();
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
	m_pTrackBallCameraCtrl->Zoom(fDelta);

	m_bCameraMatrixDirty = true;
}

void HrEditorScene::SaveConvertMeshData(const std::string& strFileName)
{

}

const std::vector<Hr::HrSceneNodePtr>& HrEditorScene::GetModelNodes()
{
	return m_vecModelNodes;
}

const std::vector<const HrModelDataInfo*>& HrEditorScene::GetModelDataInfos()
{
	return m_vecModelDataInfos;
}

void HrEditorScene::SavePrefabData(const std::string& strFileName)
{
	if (!m_vecModelDataInfos.empty())
	{

		rapidjson::Document doc;
		doc.SetObject();

		WritePrefabModelInfo(doc);

		FlushDataToFile(strFileName, doc);
	}
}

void HrEditorScene::WritePrefabModelInfo(rapidjson::Document& doc)
{
	rapidjson::Value prefabObj(rapidjson::kObjectType);

	rapidjson::Value prefabModelCountValueObj(rapidjson::kNumberType);
	prefabModelCountValueObj.SetUint(m_vecModelNodes.size());
	prefabObj.AddMember(rapidjson::StringRef("ModelCount"), prefabModelCountValueObj, doc.GetAllocator());

	for (size_t nModelIndex = 0; nModelIndex < m_vecModelNodes.size(); ++nModelIndex)
	{
		const HrModelDataInfo* pModelDataInfo = m_vecModelDataInfos[nModelIndex];
		HrSceneNodePtr pModelNode = m_vecModelNodes[nModelIndex];

		rapidjson::Value modelDataKeyObj(rapidjson::kStringType);
		std::string strModeRoot = "Node_" + std::to_string(nModelIndex);
		modelDataKeyObj.SetString(strModeRoot.c_str(), doc.GetAllocator());

		rapidjson::Value modelNodeValueObj(rapidjson::kObjectType);
		{
			rapidjson::Value fileValueObj(rapidjson::kStringType);
			std::string strFilePath = HrFileUtils::Instance()->GetFileNameWithSuffix(pModelDataInfo->strFilePath);
			fileValueObj.SetString(strFilePath.c_str(), doc.GetAllocator());
			modelNodeValueObj.AddMember(rapidjson::StringRef("File"), fileValueObj, doc.GetAllocator());

			std::string strPosition = MakeFloat3String(pModelNode->GetTransform()->GetPosition());
			rapidjson::Value nodePosValueObj(rapidjson::kObjectType);
			nodePosValueObj.SetString(strPosition.c_str(), doc.GetAllocator());
			modelNodeValueObj.AddMember(rapidjson::StringRef("Position"), nodePosValueObj, doc.GetAllocator());

			std::string strRotate = MakeFloat3String(pModelNode->GetTransform()->GetRotation());
			rapidjson::Value nodeRotateValueObj(rapidjson::kObjectType);
			nodeRotateValueObj.SetString(strRotate.c_str(), doc.GetAllocator());
			modelNodeValueObj.AddMember(rapidjson::StringRef("Rotate"), nodeRotateValueObj, doc.GetAllocator());

			std::string strScale = MakeFloat3String(pModelNode->GetTransform()->GetScale());
			rapidjson::Value nodeScaleValueObj(rapidjson::kObjectType);
			nodeScaleValueObj.SetString(strScale.c_str(), doc.GetAllocator());
			modelNodeValueObj.AddMember(rapidjson::StringRef("Scale"), nodeScaleValueObj, doc.GetAllocator());
		}

		prefabObj.AddMember(modelDataKeyObj, modelNodeValueObj, doc.GetAllocator());
	}

	doc.AddMember(rapidjson::StringRef("Models"), prefabObj, doc.GetAllocator());
}

void HrEditorScene::FlushDataToFile(const std::string& strOutputFile, rapidjson::Document& doc)
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	std::string strJsonContent = std::string(buffer.GetString());
	strJsonContent = FormatJsonData(strJsonContent);

	std::string strRootPath = HrFileUtils::Instance()->GetFilePath(strOutputFile);
	std::string strFileName = HrFileUtils::Instance()->GetFileName(strOutputFile);
	std::string strSuffix = HrFileUtils::Instance()->GetFileSuffix(strOutputFile);
	filesystem::path filePath(strRootPath);

	std::string strRealOutputFilePath = strOutputFile;
	HrFileUtils::Instance()->WriteDataToFile(strRealOutputFilePath, strJsonContent);
}

std::string HrEditorScene::FormatJsonData(const std::string& strContent)
{
	std::string strRt;
	strRt.reserve(strContent.size() * 2);

	int nCharIndex = 0;
	int nIndentCount = 0;
	while (nCharIndex < strContent.length())
	{
		char c = strContent[nCharIndex];
		if (c == '{' || c == '[')
		{
			strRt.push_back(c);
			strRt.push_back('\n');
			++nIndentCount;
			for (int i = 0; i < nIndentCount; ++i)
			{
				strRt.push_back('\t');
			}
		}
		else if (c == '}' || c == ']')
		{
			strRt.push_back('\n');
			--nIndentCount;
			for (int i = 0; i < nIndentCount; ++i)
			{
				strRt.push_back('\t');
			}
			strRt.push_back(c);
		}
		else if (c == ',')
		{
			// ,",
			if (strContent[nCharIndex + 1] == '"' && strContent[nCharIndex + 2] != ',')
			{
				strRt.push_back(c);
				strRt.push_back('\n');
				for (int i = 0; i < nIndentCount; ++i)
				{
					strRt.push_back('\t');
				}
			}
			else
			{
				strRt.push_back(c);
			}
		}
		else
		{
			strRt.push_back(c);
		}
		++nCharIndex;
	}

	return strRt;
}

std::string HrEditorScene::MakeFloat3StringWithEndMark(const float3& v)
{
	std::string strRet;
	char cTemp[50];
	std::sprintf(cTemp, "%.2f", v[0]);
	strRet += cTemp;
	strRet += ",";
	std::sprintf(cTemp, "%.2f", v[1]);
	strRet += cTemp;
	strRet += ",";
	std::sprintf(cTemp, "%.2f", v[2]);
	strRet += cTemp;
	strRet += "|";

	return strRet;
}

std::string HrEditorScene::MakeFloat3String(const float3& v)
{
	std::string strRet;
	char cTemp[50];
	std::sprintf(cTemp, "%.2f", v[0]);
	strRet += cTemp;
	strRet += ",";
	std::sprintf(cTemp, "%.2f", v[1]);
	strRet += cTemp;
	strRet += ",";
	std::sprintf(cTemp, "%.2f", v[2]);
	strRet += cTemp;

	return strRet;
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

void HrRenderApp::LoadOriginalMeshData(const std::string& strFileName)
{
	m_pEditorScene->LoadOriginalMeshData(strFileName);
}

void HrRenderApp::SaveTextFile(const std::string& strFileName)
{
	m_pEditorScene->SavePrefabData(strFileName);
}

void HrRenderApp::LoadPrefabData(const std::string& strFileName)
{
	m_pEditorScene->LoadPrefabData(strFileName);
}

