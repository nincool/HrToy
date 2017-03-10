#include "Asset/HrResourceManager.h"
#include "Asset/HrStreamData.h"
#include "Asset/HrResourceLoader.h"
#include "Asset/HrPrefabModel.h"
#include "Asset/HrMesh.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrMaterial.h"
#include "Asset/HrTexture.h"
#include "Asset/HrGeometryFactory.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrFileUtils.h"
#include "Render/HrShader.h"
#include "Render/HrRenderFactory.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrUtilTools/Include/HrStringUtil.h"

using namespace Hr;

HrResourceManager::HrResourceManager()
{

}

HrResourceManager::~HrResourceManager()
{
	ReleaseAllResources();
}

void HrResourceManager::ReleaseAllResources()
{
	//todo release assets
	ReleaseResourceCache(m_mapPrefabModels);
	ReleaseResourceCache(m_mapMesh);
	ReleaseResourceCache(m_mapMaterials);
	ReleaseResourceCache(m_mapRenderEffects);

}

void HrResourceManager::ReleaseResourceCache(std::unordered_map<size_t, HrResource*>& mapRes)
{
	for (auto it = mapRes.begin(); it != mapRes.end(); ++it)
	{
		SAFE_DELETE(it->second);
	}
	mapRes.clear();
}

void HrResourceManager::InitResourceManager()
{
	CreateBuildInEffects();
	CreateBuildInMaterial();
}

void HrResourceManager::CreateBuildInEffects()
{
	//LoadResource("Media/HrShader/HrLambert.effectxml");
	//LoadResource("Media/HrShader/HrPhong.effectxml");
	LoadResource("Media/HrShader/HrBasicEffect.json", HrResource::RT_EFFECT);
}

void HrResourceManager::CreateBuildInMaterial()
{
	LoadResource("Media/Material/MaterialDefault.material", HrResource::RT_MATERIAL);
}

HrMaterial* HrResourceManager::GetDefaultMaterial()
{
	HrMaterial* pMaterial = static_cast<HrMaterial*>(GetResource("MaterialDefault.material", HrResource::RT_MATERIAL));
	HRASSERT(pMaterial, "GetDefaultMaterial Error!");

	return pMaterial;
}

HrRenderEffect* HrResourceManager::GetDefaultRenderEffect()
{
	HrRenderEffect* pRenderEffect = static_cast<HrRenderEffect*>(GetResource("Media/HrShader/HrBasicEffect.json", HrResource::RT_EFFECT));
	HRASSERT(pRenderEffect, "GetDefaultRenderEffect Error!");

	return pRenderEffect;
}

HrResource* HrResourceManager::LoadResource(const std::string& strFile, HrResource::EnumResourceType resType)
{
	HrResource* pReturnRes = nullptr;

	std::string strFullFilePath = HrFileUtils::Instance()->GetFullPathForFileName(strFile);
	if (!strFullFilePath.empty())
	{
		std::string strfileSuffix = HrFileUtils::Instance()->GetFileSuffix(strFile);
		HrStringUtil::ToLowerCase(strfileSuffix);
		switch (resType)
		{
		case HrResource::RT_MODEL:
		{
			pReturnRes = AddModelResource(strFullFilePath);
			pReturnRes->Load();
			break;
		}
		case HrResource::RT_TEXTURE:
		{
			pReturnRes = AddTextureResource(strFullFilePath);
			pReturnRes->Load();
			break;
		}
		case HrResource::RT_MATERIAL:
		{
			pReturnRes = AddMaterialResource(strFullFilePath);
			pReturnRes->Load();
			break;
		}
		case HrResource::RT_EFFECT:
		{
			pReturnRes = AddEffectResource(strFullFilePath);
			pReturnRes->Load();
			break;
		}
		}

		//todo
		//if (strfileSuffix == "effectxml")
		//{
		//	pReturnRes = AddEffectResource(strFullFilePath);
		//	pReturnRes->Load();
		//}
	}
	else
	{
		HRERROR("HrResourceManager::LoadResource Error! FileName[%s]", strFile.c_str());
	}

	return pReturnRes;
}

HrResource* HrResourceManager::GetResource(const std::string& strFile, HrResource::EnumResourceType resType)
{
	switch (resType)
	{
	case HrResource::RT_TEXTURE:
		return GetTexture(strFile);
	case HrResource::RT_MESH:
		return GetMesh(strFile);
	case HrResource::RT_EFFECT:
		return GetEffect(strFile);
	case HrResource::RT_MATERIAL:
		return GetMaterial(strFile);
	case HrResource::RT_MODEL:
		return GetModel(strFile);
	default:
		break;
	}
	
	return nullptr;
}

HrResource* HrResourceManager::GetSkyBoxResource(const std::string& strFile, HrResource::EnumResourceType resType)
{
	size_t nHashID = HrPrefabModel::CreateHashName(strFile);
	auto item = m_mapPrefabModels.find(nHashID);
	if (item != m_mapPrefabModels.end())
	{
		return item->second;
	}
	else
	{
		HrGeometrySkyBox* pSkyBox = new HrGeometrySkyBox();
		pSkyBox->DeclareResource(strFile, strFile);
		pSkyBox->Load();
		m_mapPrefabModels[nHashID] = pSkyBox;

		return pSkyBox;
	}
}

HrResource* HrResourceManager::GetOrLoadResource(const std::string& strFile, HrResource::EnumResourceType resType)
{
	HrResource* pRes = GetResource(strFile, resType);
	if (pRes != nullptr)
	{
		return pRes;
	}
	else
	{
		return LoadResource(strFile, resType);
	}
}

HrResource* HrResourceManager::GetOrAddResource(const std::string& strFile, HrResource::EnumResourceType resType)
{
	HrResource* pReturnRes = GetResource(strFile, resType);
	if (pReturnRes != nullptr)
	{
		return pReturnRes;
	}
	else
	{
		switch (resType)
		{
		case HrResource::RT_MODEL:
		{
			pReturnRes = AddModelResource(strFile);
			break;
		}
		case HrResource::RT_TEXTURE:
		{
			pReturnRes = AddTextureResource(strFile);
			break;
		}
		case HrResource::RT_MATERIAL:
		{
			pReturnRes = AddMaterialResource(strFile);
			break;
		}
		case HrResource::RT_MESH:
		{
			pReturnRes = AddMeshResource(strFile);
			break;
		}
		}
	}

	return pReturnRes;
}

HrResource* HrResourceManager::AddModelResource(const std::string& strFile)
{
	std::string strFileName = strFile.substr(strFile.rfind("\\") + 1, strFile.size());
	
	HrPrefabModel* pRes = HR_NEW HrPrefabModel();
	pRes->DeclareResource(strFileName, strFile);

	if (m_mapPrefabModels.find(pRes->GetHashID()) != m_mapPrefabModels.end())
	{
		SAFE_DELETE(pRes);
		HRASSERT(nullptr, "AddFBXResource Error!");
		return nullptr;
	}
	m_mapPrefabModels.insert(std::make_pair(pRes->GetHashID(), pRes));

	return pRes;
}

HrResource* HrResourceManager::AddEffectResource(const std::string& strFile)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strFile);
	size_t nHashID = HrRenderEffect::CreateHashName(strFullFileName);
	if (m_mapRenderEffects.find(nHashID) != m_mapRenderEffects.end())
	{
		HRASSERT(nullptr, "AddEffectResource Error!");
		return nullptr;
	}

	std::string strFileName = strFile.substr(strFile.rfind("/") + 1, strFile.size());
	HrResource* pRes = HR_NEW HrRenderEffect();
	pRes->DeclareResource(strFileName, strFullFileName);
	m_mapRenderEffects.insert(std::make_pair(pRes->GetHashID(), pRes));

	return pRes;
}

HrResource* HrResourceManager::AddMeshResource(const std::string& strFile)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strFile);
	size_t nHashID = HrMesh::CreateHashName(strFullFileName);
	if (m_mapMesh.find(nHashID) != m_mapMesh.end())
	{
		HRASSERT(nullptr, "AddMeshResource Error!");
		return nullptr;
	}

	std::string strFileName = strFile.substr(strFile.rfind("\\") + 1, strFile.size());
	HrResource* pMesh = HR_NEW HrMesh();
	pMesh->DeclareResource(strFileName, strFullFileName);
	m_mapMesh.insert(std::make_pair(pMesh->GetHashID(), pMesh));

	return pMesh;
}

HrResource* HrResourceManager::AddMaterialResource(const std::string& strFile)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strFile);
	size_t nHashID = HrMaterial::CreateHashName(strFullFileName);
	if (m_mapMaterials.find(nHashID) != m_mapMaterials.end())
	{
		HRASSERT(nullptr, "AddMeshResource Error!");
		return nullptr;
	}

	std::string strFileName = strFile.substr(strFile.rfind("\\") + 1, strFile.size());
	HrMaterial* pMaterial = HR_NEW HrMaterial();
	pMaterial->DeclareResource(strFileName, strFile);
	m_mapMaterials.insert(std::make_pair(pMaterial->GetHashID(), pMaterial));

	return pMaterial;
}

HrResource* HrResourceManager::AddTextureResource(const std::string& strFile)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strFile);
	size_t nHashID = HrTexture::CreateHashName(strFullFileName);
	if (m_mapTextures.find(nHashID) != m_mapTextures.end())
	{
		HRASSERT(nullptr, "AddMeshResource Error!");
		return nullptr;
	}

	std::string strFileName = strFile.substr(strFile.rfind("\\") + 1, strFile.size());
	HrTexture* pTexture = HrDirector::Instance()->GetRenderFactory()->CreateTexture(HrTexture::TEX_TYPE_2D, 1, 1);
	pTexture->DeclareResource(strFileName, strFile);
	m_mapMesh.insert(std::make_pair(pTexture->GetHashID(), pTexture));

	return pTexture;
}

HrResource* HrResourceManager::GetTexture(const std::string& strTextureName)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strTextureName);
	size_t nHashID = HrTexture::CreateHashName(strFullFileName);
	auto item = m_mapTextures.find(nHashID);
	if (item != m_mapTextures.end())
	{
		return item->second;
	}
	return nullptr;
}

HrResource* HrResourceManager::GetMesh(const std::string& strMeshName)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strMeshName);
	size_t nHashID = HrMesh::CreateHashName(strFullFileName);
	auto item = m_mapMesh.find(nHashID);
	if (item != m_mapMesh.end())
	{
		return item->second;
	}

	return nullptr;
}

HrResource* HrResourceManager::GetEffect(const std::string& strEffectName)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strEffectName);
	size_t nHashID = HrHashValue(strFullFileName);
	auto item = m_mapRenderEffects.find(nHashID);
	if (item != m_mapRenderEffects.end())
	{
		return item->second;
	}

	return nullptr;
}

HrResource* HrResourceManager::GetMaterial(const std::string& strMaterialName)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strMaterialName);
	size_t nHashID = HrMaterial::CreateHashName(strFullFileName);
	auto item = m_mapMaterials.find(nHashID);
	if (item != m_mapMaterials.end())
	{
		return item->second;
	}
	return nullptr;
}

HrResource* HrResourceManager::GetModel(const std::string& strModelName)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strModelName);
	size_t nHashID = HrPrefabModel::CreateHashName(strFullFileName);
	auto item = m_mapPrefabModels.find(nHashID);
	if (item != m_mapPrefabModels.end())
	{
		return item->second;
	}
	return nullptr;
}

