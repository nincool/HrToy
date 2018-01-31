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

#include "Kernel/HrCoreComponentRender.h"
#include "Render/HrRenderSystem.h"


using namespace Hr;

HrResourceManager::HrResourceManager()
	:m_pDefaultTexture(nullptr),
	m_pDefaultMaterial(nullptr),
	m_pDefaultRenderEffect(nullptr)
{
}

HrResourceManager::~HrResourceManager()
{
	ReleaseAllResources();
}

void HrResourceManager::ReleaseAllResources()
{
	//todo release assets
	//ReleaseResourceCache(m_mapPrefabModels);
	ReleaseResourceCache(m_mapMesh);
	//ReleaseResourceCache(m_mapMaterials);
	//ReleaseResourceCache(m_mapRenderEffects);

}

void HrResourceManager::ReleaseResourceCache(std::unordered_map<size_t, HrResourcePtr>& mapRes)
{
	mapRes.clear();
}

void HrResourceManager::InitResourceManager()
{
	HRLOG("HrResourceManager::InitResourceManager Start to create buildin resources!");
	//CreateBuildInTexture();
	CreateBuildInEffects();
	CreateBuildInMaterial();
}

void HrResourceManager::CreateBuildInTexture()
{
	HRLOG("HrResourceManager::CreateBuildTexture Start to create buildin textures!");
	LoadResource("Media/Model/Buildin/Texture/defaulttexture.png", HrResource::RT_TEXTURE);
}

void HrResourceManager::CreateBuildInEffects()
{
	HRLOG("HrResourceManager::CreateBuildInEffects Start to create buildin effects!");
	m_pDefaultRenderEffect = HrCheckPointerCast<HrRenderEffect>(LoadResource("Media/HrShader/HrBasicEffect.json", HrResource::RT_EFFECT));
}

void HrResourceManager::CreateBuildInMaterial()
{
	HRLOG("HrResourceManager::CreateBuildInMaterial Start to create buildin material!");
	m_pDefaultMaterial = HrCheckPointerCast<HrMaterial>(LoadResource("Media/Material/MaterialDefault.material", HrResource::RT_MATERIAL));
}

HrTexture* HrResourceManager::GetDefaultTexture()
{
	if (m_pDefaultTexture == nullptr)
	{
		HRASSERT(m_pDefaultTexture, "GetDefaultTexture Error!");
	}

	return m_pDefaultTexture;
}

HrRenderEffectPtr HrResourceManager::GetDefaultRenderEffect()
{
	if (m_pDefaultRenderEffect == nullptr)
	{
		HRASSERT(m_pDefaultRenderEffect, "GetDefaultRenderEffect Error!");
	}

	return m_pDefaultRenderEffect;
}

HrMaterialPtr HrResourceManager::CreateDefaultMaterial()
{
	HrMaterialPtr pTempDefaultMaterial = HrMakeSharedPtr<HrMaterial>(m_pDefaultMaterial);
	m_mapMaterials.insert(std::make_pair(pTempDefaultMaterial->GetHashID(), pTempDefaultMaterial));

	return pTempDefaultMaterial;
}

HrResourcePtr HrResourceManager::LoadResource(const std::string& strFile, HrResource::EnumResourceType resType)
{
	HrResourcePtr pReturnRes = nullptr;

	std::string strFullFilePath = HrFileUtils::Instance()->GetFullPathForFileName(strFile);
	if (!strFullFilePath.empty())
	{
		pReturnRes = AddResource(strFullFilePath, resType);
		pReturnRes->Load();
	}
	else
	{
		HRERROR("HrResourceManager::LoadResource Error! FileName[%s]", strFile.c_str());
	}

	return pReturnRes;
}

HrResourcePtr HrResourceManager::RetriveResource(const std::string& strFile, HrResource::EnumResourceType resType)
{
	switch (resType)
	{
	//case HrResource::RT_TEXTURE:
	//	return GetTexture(strFile);
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

HrResourcePtr HrResourceManager::RetriveOrLoadResource(const std::string& strFile, HrResource::EnumResourceType resType)
{
	HrResourcePtr pRes = RetriveResource(strFile, resType);
	if (pRes != nullptr)
	{
		return pRes;
	}
	else
	{
		return LoadResource(strFile, resType);
	}
}

HrResourcePtr HrResourceManager::RetriveOrAddResource(const std::string& strFile, HrResource::EnumResourceType resType)
{
	HrResourcePtr pRes = RetriveResource(strFile, resType);
	if (pRes != nullptr)
	{
		return pRes;
	}
	else
	{
		return AddResource(strFile, resType);
	}
}

HrResourcePtr HrResourceManager::AddResource(const std::string& strFile, HrResource::EnumResourceType resType)
{
	switch (resType)
	{
		//case HrResource::RT_TEXTURE:
		//	return GetTexture(strFile);
	case HrResource::RT_MESH:
		return AddMeshResource(strFile);
	case HrResource::RT_EFFECT:
		return AddEffectResource(strFile);
	case HrResource::RT_MATERIAL:
		return AddMaterialResource(strFile);
	case HrResource::RT_MODEL:
		return AddModelResource(strFile);
	default:
		break;
	}

	return nullptr;
}

HrResourcePtr HrResourceManager::AddModelResource(const std::string& strFile)
{
	std::string strFileName = strFile.substr(strFile.rfind(HrFileUtils::m_s_strSeparator) + 1, strFile.size());
	
	HrPrefabModelPtr pRes = HrMakeSharedPtr<HrPrefabModel>();
	pRes->DeclareResource(strFileName, strFile);
	if (m_mapPrefabModels.find(pRes->GetHashID()) != m_mapPrefabModels.end())
	{
		pRes = nullptr;
		HRASSERT(nullptr, "AddFBXResource Error!");
		
		return nullptr;
	}
	m_mapPrefabModels.insert(std::make_pair(pRes->GetHashID(), pRes));

	return pRes;
}

HrResourcePtr HrResourceManager::AddEffectResource(const std::string& strFile)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strFile);
	size_t nHashID = HrRenderEffect::CreateHashName(strFullFileName);
	if (m_mapRenderEffects.find(nHashID) != m_mapRenderEffects.end())
	{
		HRASSERT(nullptr, "AddEffectResource Error!");
		return nullptr;
	}

	std::string strFileName = strFile.substr(strFile.rfind(HrFileUtils::m_s_strSeparator) + 1, strFile.size());
	HrResourcePtr pRes = HrMakeSharedPtr<HrRenderEffect>();
	pRes->DeclareResource(strFileName, strFullFileName);
	m_mapRenderEffects.insert(std::make_pair(pRes->GetHashID(), pRes));

	return pRes;
}

HrResourcePtr HrResourceManager::AddMeshResource(const std::string& strFile)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strFile);
	size_t nHashID = HrMesh::CreateHashName(strFullFileName);
	if (m_mapMesh.find(nHashID) != m_mapMesh.end())
	{
		HRASSERT(nullptr, "AddMeshResource Error!");
		return nullptr;
	}

	std::string strFileName = strFile.substr(strFile.rfind(HrFileUtils::m_s_strSeparator) + 1, strFile.size());
	HrResourcePtr pMesh = HrMakeSharedPtr<HrMesh>();
	pMesh->DeclareResource(strFileName, strFullFileName);
	m_mapMesh.insert(std::make_pair(pMesh->GetHashID(), pMesh));

	return pMesh;
}

HrResourcePtr HrResourceManager::AddMaterialResource(const std::string& strFile)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strFile);
	std::string strFileName = strFile.substr(strFile.rfind(HrFileUtils::m_s_strSeparator) + 1, strFile.size());
	HrMaterialPtr pMaterial = HrMakeSharedPtr<HrMaterial>();
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

	std::string strFileName = strFile.substr(strFile.rfind(HrFileUtils::m_s_strSeparator) + 1, strFile.size());
	//HrTexture* pTexture = HrDirector::Instance()->GetRenderCoreComponent()->GetRenderSystem()->GetRenderFactory()->CreateTexture(HrTexture::TEX_TYPE_2D, 1, 1);
	//pTexture->DeclareResource(strFileName, strFile);
	//m_mapMesh.insert(std::make_pair(pTexture->GetHashID(), pTexture));

	return nullptr;
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

HrResourcePtr HrResourceManager::GetMesh(const std::string& strMeshName)
{
	std::string strFullFilePath = HrFileUtils::Instance()->GetFullPathForFileName(strMeshName);
	size_t nHashID = HrMesh::CreateHashName(strFullFilePath);
	auto item = m_mapMesh.find(nHashID);
	if (item != m_mapMesh.end())
	{
		return item->second;
	}

	return nullptr;
}

HrResourcePtr HrResourceManager::GetEffect(const std::string& strEffectName)
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

const HrResourcePtr& HrResourceManager::GetMaterial(const std::string& strMaterialName)
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

HrResourcePtr HrResourceManager::GetModel(const std::string& strModelName)
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

