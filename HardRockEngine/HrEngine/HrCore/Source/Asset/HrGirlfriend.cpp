#include "Asset/HrGirlfriend.h"
#include "Asset/Loader/HrMeshUtils.h"
#include "Asset/HrMeshModel.h"
#include "Asset/HrSceneObjectFactory.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrResourceModule.h"
#include "Scene/HrSceneNode.h"

#include "HrUtilTools/Include/HrStringUtil.h"
#include "ThirdParty/rapidjson/include/rapidjson/document.h"
#include <experimental/filesystem>

using namespace Hr;
using namespace std::experimental;

HrPrefabData::HrPrefabData()
{
	
}

HrPrefabData::~HrPrefabData()
{

}

size_t HrPrefabData::CreateHashName(const std::string& strHashValue)
{
	return HrHashValue(strHashValue);
}

void HrPrefabData::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFilePath = strFilePath;
	m_strFileName = strFileName;
	m_resType = HrResource::RT_PREFAB;
	m_resStatus = HrResource::RS_DECLARED;

	m_nHashID = CreateHashName(m_strFilePath);
}

bool HrPrefabData::LoadImpl()
{
	if (HrFileUtils::Instance()->GetFileSuffix(m_strFilePath) == "hrpref")
	{
		std::string strContentData = HrFileUtils::Instance()->GetFileString(m_strFilePath);
		rapidjson::Document d;
		d.Parse<0>(strContentData.c_str());
		if (d.HasParseError())
		{
			int nErrorCode = d.GetParseError();
			int nOffset = d.GetErrorOffset();

			return false;
		}
		const rapidjson::Value& modelsInfo = d["Models"];
		int nModelCount = modelsInfo["ModelCount"].GetInt();
		for (int i = 0; i < nModelCount; ++i)
		{
			const std::string strModelRoot = HrStringUtil::StringFormat("Node_%d", i);
			const rapidjson::Value& nodeInfo = modelsInfo[strModelRoot.c_str()];
			std::string strModelFile = nodeInfo["File"].GetString();

			std::string strLocationPath = HrFileUtils::Instance()->GetFilePath(m_strFilePath);
			filesystem::path locationPath(strLocationPath);
			filesystem::path filePath = locationPath / strModelFile;
			if (!filesystem::exists(filePath))
			{
				BOOST_ASSERT(false);
				return false;
			}

			Vector3 v3Position = HrStringUtil::GetFloat3FromString(nodeInfo["Position"].GetString(), ",");
			Vector3 v3Rotate = HrStringUtil::GetFloat3FromString(nodeInfo["Rotate"].GetString(), ",");
			Vector3 v3Scale = HrStringUtil::GetFloat3FromString(nodeInfo["Scale"].GetString(), ",");

			HrMeshModelPtr pPrefabModel = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrMeshModel>(filePath.string(), true, true);
			if (pPrefabModel == nullptr)
			{
				BOOST_ASSERT(false);
				return false;
			}

			m_vecPrefabModelInfo.emplace_back(pPrefabModel, v3Position, v3Rotate, v3Scale);
			m_resStatus = HrResource::RS_LOADED;
		}

		return true;
	}

	return false;
}

bool HrPrefabData::UnloadImpl()
{
	return true;
}

const HrSceneNodePtr HrPrefabData::CreateSceneNode()
{
	if (m_resStatus != HrResource::RS_LOADED)
	{
		return nullptr;
	}
	HrSceneNodePtr pRootNode = HrMakeSharedPtr<HrSceneNode>(m_strFileName);
	for (size_t i = 0; i < m_vecPrefabModelInfo.size(); ++i)
	{
		HrSceneNodePtr pSceneNode = HrSceneObjectFactory::Instance()->CreateMeshModelNode(m_vecPrefabModelInfo[i].m_pMeshModel);
		pRootNode->AddChild(pSceneNode);
		pSceneNode->GetTransform()->SetPosition(m_vecPrefabModelInfo[i].m_vPosition);
		pSceneNode->GetTransform()->SetRotation(m_vecPrefabModelInfo[i].m_vRotate);
		pSceneNode->GetTransform()->SetScale(m_vecPrefabModelInfo[i].m_vScale);
	}

	return pRootNode;
}
