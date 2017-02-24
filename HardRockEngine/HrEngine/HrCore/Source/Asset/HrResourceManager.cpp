#include "Asset/HrResourceManager.h"
#include "Asset/HrStreamData.h"
#include "Asset/HrResourceLoader.h"
#include "Asset/HrPrefabModel.h"
#include "Asset/HrMesh.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrMaterial.h"
#include "Asset/HrTexture.h"
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
	LoadResource("Media/HrShader/HrLambert.effectxml");
	//LoadResource("Media/HrShader/HrBasicEffect.effectxml");
	//LoadResource("Media/HrShader/HrTestLighting.effectxml");
}

void HrResourceManager::CreateBuildInMaterial()
{
	HrMaterial* pMaterial = static_cast<HrMaterial*>(this->AddMaterialResource(std::string(HR_BUILDIN_RES_PATH) + "DEFAULTMATERIAL"));
	pMaterial->BuildToDefultMaterial();
}

HrMaterial* HrResourceManager::GetDefaultMaterial()
{
	return static_cast<HrMaterial*>(GetResource(std::string(HR_BUILDIN_RES_PATH) + "DEFAULTMATERIAL", HrResource::RT_MATERIAL));
}

HrRenderEffect* HrResourceManager::GetDefaultRenderEffect()
{
	HrRenderEffect* pRenderEffect = static_cast<HrRenderEffect*>(GetResource("Media/HrShader/HrLambert.effectxml", HrResource::RT_EFFECT));
	BOOST_ASSERT(pRenderEffect);

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
		}

		//todo
		if (strfileSuffix == "effectxml")
		{
			pReturnRes = AddEffectResource(strFullFilePath);
			pReturnRes->Load();
		}
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
	std::string strFileName = strFile.substr(strFile.rfind("/") + 1, strFile.size());
	HrResource* pRes = HR_NEW HrRenderEffect();
	pRes->DeclareResource(strFileName, strFile);
	if (m_mapRenderEffects.find(pRes->GetHashID()) != m_mapRenderEffects.end())
	{
		SAFE_DELETE(pRes);
		HRASSERT(nullptr, "AddEffectResource Error!");
		return nullptr;
	}
	m_mapRenderEffects.insert(std::make_pair(pRes->GetHashID(), pRes));

	return pRes;
}

HrResource* HrResourceManager::AddMeshResource(const std::string& strFile)
{
	std::string strFileName = strFile.substr(strFile.rfind("\\") + 1, strFile.size());

	HrResource* pMesh = HR_NEW HrMesh();
	pMesh->DeclareResource(strFileName, strFile);
	size_t nMeshHashID = pMesh->GetHashID();
	if (m_mapMesh.find(nMeshHashID) != m_mapMesh.end())
	{
		return nullptr;
	}
	m_mapMesh.insert(std::make_pair(nMeshHashID, pMesh));

	return pMesh;
}

HrResource* HrResourceManager::AddMaterialResource(const std::string& strFile)
{
	std::string strFileName = strFile.substr(strFile.rfind("\\") + 1, strFile.size());

	HrMaterial* pMaterial = HR_NEW HrMaterial();
	pMaterial->DeclareResource(strFileName, strFile);
	size_t nMaterialID = pMaterial->GetHashID();
	if (m_mapMaterials.find(nMaterialID) != m_mapMaterials.end())
	{
		return nullptr;
	}
	m_mapMaterials.insert(std::make_pair(nMaterialID, pMaterial));

	return pMaterial;
}

HrResource* HrResourceManager::AddTextureResource(const std::string& strFile)
{
	std::string strFileName = strFile.substr(strFile.rfind("\\") + 1, strFile.size());
	HrTexture* pTexture = HrDirector::Instance()->GetRenderFactory()->CreateTexture(HrTexture::TEX_TYPE_2D, 1, 1);
	pTexture->DeclareResource(strFileName, strFile);
	size_t nTextureID = pTexture->GetHashID();
	if (m_mapMaterials.find(nTextureID) != m_mapMaterials.end())
	{
		return nullptr;
	}
	m_mapMesh.insert(std::make_pair(nTextureID, pTexture));

	return pTexture;
}

HrResource* HrResourceManager::GetTexture(const std::string& strTextureName)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strTextureName);
	size_t nHashID = HrTexture::GetHashName(strFullFileName);
	auto item = m_mapTextures.find(nHashID);
	if (item != m_mapTextures.end())
	{
		return item->second;
	}
	return nullptr;
}

HrResource* HrResourceManager::GetMesh(const std::string& strMeshName)
{
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
	size_t nHashID = HrHashValue(strMaterialName);
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

