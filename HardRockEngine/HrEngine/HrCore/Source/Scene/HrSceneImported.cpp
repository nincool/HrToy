#include "Scene/HrSceneImported.h"

#include "Asset/HrStreamData.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"

#include "HrCore/Include/Asset/HrGeometryFactory.h"
#include "HrCore/Include/Scene/HrEntityNode.h"
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

	m_sceneDataInfo.ambientColor = HrMath::MakeColor(HrStringUtil::GetUInt8VectorFromString(sceneRootInfo["AMBIENT_LIGHT_COLOR"].GetString()));

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
			
			const rapidjson::Value& nodeEntityValue = sceneNodeValue["ENTITY"];
			nodeInfo.nEntityType = (HrSceneInfo::EnumEntityType)nodeEntityValue["ENTITY_TYPE"].GetInt();
			switch (nodeInfo.nEntityType)
			{
			case HrSceneInfo::ET_LIGHT:
			{
				nodeInfo.sceneLightInfo.nLightType = nodeEntityValue["LIGHT_TYPE"].GetInt();
				nodeInfo.sceneLightInfo.strLightName = nodeEntityValue["LIGHT_NAME"].GetString();
				nodeInfo.sceneLightInfo.vPosition = HrStringUtil::GetFloat3FromString(nodeEntityValue["LIGHT_POSITION"].GetString());
				nodeInfo.sceneLightInfo.vDirection = HrStringUtil::GetFloat3FromString(nodeEntityValue["LIGHT_DIRECTION"].GetString());
				nodeInfo.sceneLightInfo.diffuseColor = HrMath::MakeColor(HrStringUtil::GetUInt8VectorFromString(nodeEntityValue["LIGHT_DIFFUSE_COLOR"].GetString()));
				nodeInfo.sceneLightInfo.specularColor = HrMath::MakeColor(HrStringUtil::GetUInt8VectorFromString(nodeEntityValue["LIGHT_SPECULAR_COLOR"].GetString()));
				break;
			}
			case HrSceneInfo::ET_PREFAB:
			{
				nodeInfo.strEntityResource = nodeEntityValue["PREFAB"].GetString();
				break;
			}
			default:
			{
				break;
			}
			}
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
	m_pSceneMainCamera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -100.0f));

	SetAmbientLight(m_sceneDataInfo.ambientColor);

	//创建Entity节点
	CreateSceneNode(m_pRootNode, m_sceneDataInfo.vecSceneNodeInfo);
}

void HrSceneImported::CreateSceneNode(HrSceneNode* pParent, std::vector<HrSceneInfo::HrSceneNodeInfo>& vecSceneNodeInfo)
{ 
	for (auto& itemSceneNode : vecSceneNodeInfo)
	{
		HrSceneNode* pSceneNode = nullptr;
		switch (itemSceneNode.nEntityType)
		{
		case HrSceneInfo::ET_LIGHT:
		{
			switch (itemSceneNode.sceneLightInfo.nLightType)
			{
			case HrLight::LT_DIRECTIONAL:
			{
				pSceneNode = HrSceneObjectFactory::Instance()->CreateDirectionalLight(itemSceneNode.sceneLightInfo.vDirection
					, itemSceneNode.sceneLightInfo.diffuseColor
					, itemSceneNode.sceneLightInfo.specularColor);
				break;
			}
			}
			break;
		}
		case HrSceneInfo::ET_PREFAB:
		{
			pSceneNode = HrSceneObjectFactory::Instance()->CreateModel(itemSceneNode.strEntityResource);

			break;
		}
		}
		pSceneNode->GetTransform()->SetScale(itemSceneNode.v3Scale);
		pSceneNode->GetTransform()->SetOrientation(HrMath::RotationQuaternionPitchYawRoll(HrMath::Degree2Radian(itemSceneNode.v3Rotation)));
		pSceneNode->GetTransform()->SetPosition(itemSceneNode.v3Position);
		if (itemSceneNode.vecChildrenSceneNode.size() > 0)
		{
			CreateSceneNode(pSceneNode, itemSceneNode.vecChildrenSceneNode);
		}
		pParent->AddChild(pSceneNode);

	}
}

