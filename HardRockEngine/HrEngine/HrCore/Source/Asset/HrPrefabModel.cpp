#include "Asset/HrPrefabModel.h"
#include "Asset/HrMesh.h"
#include "Asset/HrTexture.h"
#include "Asset/HrMaterial.h"
#include "Asset/HrResourceManager.h"
#include "Asset/Loader/HrModelLoader.h"
#include "Asset/Loader/HrFBXLoader.h"
#include "Asset/HrStreamData.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrUtilTools/Include/HrStringUtil.h"
#include "ThirdParty/rapidjson/include/rapidjson/document.h"

#include <boost/format.hpp>


using namespace Hr;
using namespace std;

HrPrefabModel::HrPrefabModel()
{

}

HrPrefabModel::~HrPrefabModel()
{

}

size_t HrPrefabModel::CreateHashName(const std::string& strFullFilePath)
{
	return HrHashValue(strFullFilePath);
}

void HrPrefabModel::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFilePath = strFilePath;
	m_strFileName = strFileName;
	m_resType = HrResource::RT_MODEL;

	m_nHashID = CreateHashName(m_strFilePath);
}

bool HrPrefabModel::LoadImpl()
{
	std::string strFullPath = HrFileUtils::Instance()->GetFullPathForFileName(m_strFilePath);
	if (strFullPath.length() <= 0)
	{
		HRERROR("HrSceneImported::LoadScene Error! SceneName[%s]", m_strFilePath.c_str());
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

	const rapidjson::Value& sceneRootInfo = d["ASSET_ROOT"];

	//Mesh
	std::string strFileName = sceneRootInfo["RESOURCE_FILE"].GetString();
	HrModelLoaderPtr pModelLoader = std::make_shared<HrModelLoader>();
	pModelLoader->Load(strFileName);
	m_pMesh = pModelLoader->GetMesh();
	
	//Material
	const rapidjson::Value& materialInfo = sceneRootInfo["MATERIAL"];
	{
		int nMaterialIndex = 0;
		while (true)
		{
			++nMaterialIndex;

			boost::format fmt("MATERIAL_%1%");
			std::string strMaterialItem = (fmt % nMaterialIndex).str();
			if (materialInfo.HasMember(strMaterialItem.c_str()))
			{
				const rapidjson::Value& childMaterial = materialInfo[strMaterialItem.c_str()];
				if (childMaterial.HasMember("NORMAL_TEXTURE"))
				{
					std::string strNormalTexture = childMaterial["NORMAL_TEXTURE"].GetString();

					HrTexture* pTexture = static_cast<HrTexture*>(HrResourceManager::Instance()->GetOrLoadResource(strNormalTexture, HrResource::RT_TEXTURE));
					m_vecTexture.push_back(pTexture);
				}
				if (childMaterial.HasMember("SELF_MATERIAL"))
				{
					const rapidjson::Value& selfMaterialInfo = childMaterial["SELF_MATERIAL"];
					std::string strMaterialName = selfMaterialInfo["NAME"].GetString();

					std::vector<uint8> vAmbient = HrStringUtil::GetUInt8VectorFromString(selfMaterialInfo["AMBIENT"].GetString());
					std::vector<uint8> vDiffuse = HrStringUtil::GetUInt8VectorFromString(selfMaterialInfo["DIFFUSE"].GetString());
					std::vector<uint8> vSpecular = HrStringUtil::GetUInt8VectorFromString(selfMaterialInfo["SPECULAR"].GetString());
					std::vector<uint8> vEmissive = HrStringUtil::GetUInt8VectorFromString(selfMaterialInfo["EMISSIVE"].GetString());
					float fOpacity = selfMaterialInfo["OPACITY"].GetFloat();
					
					//»»ÏÂMaterialµÄÃû×Ö
					std::string strMeshFilePath = HrFileUtils::Instance()->GetFilePath(strFileName);
					std::string strMeshFileName = HrFileUtils::Instance()->GetFileName(strFileName);
					strMaterialName = strMeshFilePath + "\\" + strMeshFileName + "-" + strMaterialName;
					HrMaterial* pMaterial = static_cast<HrMaterial*>(HrResourceManager::Instance()->GetResource(strMaterialName, HrResource::RT_MATERIAL));
					if (pMaterial == nullptr)
					{
						pMaterial = static_cast<HrMaterial*>(HrResourceManager::Instance()->GetOrAddResource(strMaterialName, HrResource::RT_MATERIAL));
						pMaterial->FillMaterialInfo(HrMath::MakeColor(vAmbient).Value()
							, HrMath::MakeColor(vDiffuse).Value()
							, HrMath::MakeColor(vSpecular).Value()
							, HrMath::MakeColor(vEmissive).Value()
							, fOpacity);
					}
					m_vecMaterial.push_back(pMaterial);
				}
				else if (childMaterial.HasMember("DEFAULT_MATERIAL_NAME"))
				{
					std::string strDefaultMaterialName = childMaterial["DEFAULT_MATERIAL_NAME"].GetString();
					HrMaterial* pMaterial = static_cast<HrMaterial*>(HrResourceManager::Instance()->GetResource(strDefaultMaterialName, HrResource::RT_MATERIAL));
					if (pMaterial != nullptr)
					{
						m_vecMaterial.push_back(pMaterial);
					}
					else
					{
						m_vecMaterial.push_back(HrResourceManager::Instance()->GetDefaultMaterial());
					}
				}
				else
				{
					m_vecMaterial.push_back(HrResourceManager::Instance()->GetDefaultMaterial());
				}
			}
			else
			{
				break;
			}
		}
	}

	for (int i = 0; i < m_pMesh->GetSubMeshNum(); ++i)
	{
		HrSubMesh* pSubMesh = m_pMesh->GetSubMesh(i);
		if (pSubMesh && m_vecMaterial.size() > i)
		{
			pSubMesh->SetMaterial(m_vecMaterial[i]);
			pSubMesh->SetTexture(m_vecTexture[i]);
		}
	}

	return true;
}

bool HrPrefabModel::UnloadImpl()
{
	return false;
}
