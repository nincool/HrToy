#include "Asset/HrResourceManager.h"
#include "Asset/HrStreamData.h"
#include "Asset/HrResourceLoader.h"
#include "Asset/HrPrefebModel.h"
#include "Asset/HrMesh.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrMaterial.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrFileUtils.h"
#include "Render/HrShader.h"
#include "Render/HrRenderFactory.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrResourceManager::HrResourceManager()
{

}

HrResourceManager::~HrResourceManager()
{
	//todo release assets
	ReleaseResourceCache(m_mapPrefebModels);
	ReleaseResourceCache(m_mapMesh);
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

HrResource* HrResourceManager::LoadResource(const std::string& strFile)
{
	HrResource* pReturnRes = nullptr;

	std::string strFullFilePath = HrFileUtils::Instance()->GetFullPathForFileName(strFile);
	if (!strFullFilePath.empty())
	{
		std::string strfileSuffix = HrFileUtils::Instance()->GetFileSuffix(strFile);
		if (strfileSuffix == "fbx")
		{
			pReturnRes = AddFBXResource(strFullFilePath);
			pReturnRes->Load();
		}
		else if (strfileSuffix == "effectxml")
		{
			pReturnRes = AddEffectResource(strFullFilePath);
			pReturnRes->Load();
		}
	}

	return pReturnRes;
}

HrResource* HrResourceManager::GetResource(const std::string& strFile, HrResource::EnumResourceType resType)
{
	switch (resType)
	{
	case HrResource::RT_TEXTURE:
		break;
	case HrResource::RT_MESH:
		return GetMesh(strFile);
	case HrResource::RT_EFFECT:
		return GetEffect(strFile);
	case HrResource::RT_MATERIAL:
		break;
	case HrResource::RT_MODEL:
		break;
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
		return LoadResource(strFile);
	}
}

HrRenderEffect* HrResourceManager::GetDefaultRenderEffect()
{
	HrRenderEffect* pRenderEffect = static_cast<HrRenderEffect*>(GetResource("Media/HrShader/HrLambert.effectxml", HrResource::RT_EFFECT));
	BOOST_ASSERT(pRenderEffect);

	return pRenderEffect;
}

HrResource* HrResourceManager::AddFBXResource(const std::string& strFile)
{
	std::string strFileName = strFile.substr(strFile.rfind("\\") + 1, strFile.size());
	
	HrPrefebModel* pRes = HR_NEW HrPrefebModel();
	pRes->DeclareResource(strFileName, strFile);

	if (m_mapPrefebModels.find(pRes->GetHashID()) != m_mapPrefebModels.end())
	{
		SAFE_DELETE(pRes);
		HRASSERT(nullptr, "AddFBXResource Error!");
		return nullptr;
	}
	m_mapPrefebModels.insert(std::make_pair(pRes->GetHashID(), pRes));

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
		return pMesh;
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
		return pMaterial;
	}
	m_mapMesh.insert(std::make_pair(nMaterialID, pMaterial));

	return pMaterial;
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
