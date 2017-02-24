#include "Scene/HrSceneImported.h"

#include "Asset/HrStreamData.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"

#include "HrCore/Include/Asset/HrGeometryFactory.h"
#include "HrCore/Include/Scene/HrCameraNode.h"
#include "HrCore/Include/Scene/HrTransform.h"
#include "HrCore/Include/Asset/HrResourceManager.h"
#include "HrCore/Include/Asset/HrSceneObjectFactory.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrCore/Include/Kernel/HrScheduler.h"

#include "HrUtilTools/Include/HrStringUtil.h"

#include <boost/format.hpp>

using namespace Hr;

HrSceneImported::HrSceneImported()
{

}

HrSceneImported::~HrSceneImported()
{

}

bool HrSceneImported::LoadScene(const std::string& strSceneName)
{
	std::string strFullPath = HrFileUtils::Instance()->GetFullPathForFileName(strSceneName);
	if (strFullPath.length() <= 0)
	{
		HRERROR("HrSceneImported::LoadScene Error! SceneName[%s]", strSceneName.c_str());
		return false;
	}
	HrStreamDataPtr pStreamData = HrFileUtils::Instance()->GetFileData(strFullPath);
	rapidjson::Document d;
	d.Parse<0>(pStreamData->GetBufferPoint());
	if (d.HasParseError())
	{
		int nErrorCode = d.GetParseError();
		int nOffset = d.GetErrorOffset();
		HRERROR("HrSceneImported::LoadScene Error! ParseJsonFile Error! ErrorCode[%d] Offset[%d]", nErrorCode, nOffset);
		return false;
	}
	
	const rapidjson::Value& sceneRootInfo = d["SCENE_ROOT"];
	
	LoadSceneNode(sceneRootInfo, m_sceneDataInfo.vecSceneNodeInfo);

	CreateSceneFromData();

	HRLOG("HrSceneImported::LoadScene[%s] success!", strSceneName.c_str());
}

void HrSceneImported::LoadSceneNode(const rapidjson::Value& jsonValue, std::vector<HrSceneInfo::HrSceneNodeInfo>& vecSceneNodeInfo)
{
	int nTempIndex = 0;
	while (true)
	{
		boost::format fmt("SCENE_NODE_%1%");
		std::string strItemName = (fmt % nTempIndex).str();
		if (jsonValue.HasMember(strItemName.c_str()))
		{
			vecSceneNodeInfo.emplace_back();
			HrSceneInfo::HrSceneNodeInfo& nodeInfo = vecSceneNodeInfo.back();
			const rapidjson::Value& sceneNodeValue = jsonValue[strItemName.c_str()];
			nodeInfo.strName = sceneNodeValue["NAME"].GetString();
			nodeInfo.strEntityResource = sceneNodeValue["ENTITY"].GetString();
			nodeInfo.v3Position = HrStringUtil::GetFloat3FromString(sceneNodeValue["POSITION"].GetString());
			nodeInfo.v3Rotation = HrStringUtil::GetFloat3FromString(sceneNodeValue["ROTATION"].GetString());
			nodeInfo.v3Scale = HrStringUtil::GetFloat3FromString(sceneNodeValue["SCALE"].GetString());
			
			if (sceneNodeValue.HasMember("CHILDREN"))
			{
				const rapidjson::Value& childrenNodeInfo = sceneNodeValue["CHILDREN"];
				LoadSceneNode(childrenNodeInfo, nodeInfo.vecChildrenSceneNode);
			}
		}
		else
		{
			break;
		}

		++nTempIndex;
	}
}

void HrSceneImported::CreateSceneFromData()
{
	//添加摄像机
	m_pSceneMainCamera = HrSceneObjectFactory::Instance()->CreateCamera();
	AddSceneNode(m_pSceneMainCamera);
	m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -200.0f));

	//创建Entity节点
	CreateSceneNode(m_pRootNode, m_sceneDataInfo.vecSceneNodeInfo);

}

void HrSceneImported::CreateSceneNode(HrSceneNode* pParent, std::vector<HrSceneInfo::HrSceneNodeInfo>& vecSceneNodeInfo)
{
	for (auto& itemSceneNode : vecSceneNodeInfo)
	{
		auto pSceneNode = HrSceneObjectFactory::Instance()->CreateModel(itemSceneNode.strEntityResource);
		pSceneNode->GetTransform()->SetPosition(itemSceneNode.v3Position);
		pSceneNode->GetTransform()->SetOrientation(HrMath::RotationQuaternionYawPitchRoll(itemSceneNode.v3Rotation));
		if (itemSceneNode.vecChildrenSceneNode.size() > 0)
		{
			CreateSceneNode(pSceneNode, itemSceneNode.vecChildrenSceneNode);
		}
		pParent->AddChild(pSceneNode);

	}
}

