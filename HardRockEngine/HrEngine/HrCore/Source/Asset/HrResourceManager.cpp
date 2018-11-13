#include "Asset/HrResourceManager.h"
#include "Asset/HrStreamData.h"
#include "Asset/HrResourceLoader.h"
#include "Asset/HrMesh.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrMaterial.h"
#include "Asset/HrTexture.h"
#include "Asset/HrMeshModel.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrFileUtils.h"
#include "Render/HrShader.h"
#include "Render/HrRenderFactory.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrUtilTools/Include/HrStringUtil.h"

#include "Kernel/HrRenderModule.h"
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
	LoadResource("Media/Model/Buildin/Texture/defaulttexture.png", HrResource::RT_TEXTURE_2D);
}

void HrResourceManager::CreateBuildInEffects()
{
	HRLOG("HrResourceManager::CreateBuildInEffects Start to create buildin effects!");
	m_pDefaultRenderEffect = HrCheckPointerCast<HrRenderEffect>(LoadResource("Media/Effect/Hlsl/HrStandardPro.json", HrResource::RT_EFFECT));
	//LoadResource("Media/Effect/Hlsl/HrStandardSampler.json", HrResource::RT_EFFECT);
	//LoadResource("Media/Effect/Hlsl/HrShadowMapDepth.json", HrResource::RT_EFFECT);
	//LoadResource("Media/Effect/Hlsl/HrShadowMap.json", HrResource::RT_EFFECT); 
	LoadResource("Media/Effect/Hlsl/HrMakeGBuffer.json", HrResource::RT_EFFECT);
	LoadResource("Media/Effect/Hlsl/HrDeferredShading.json", HrResource::RT_EFFECT);
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

HrResourcePtr HrResourceManager::GetDefaultRenderEffect()
{
	if (m_pDefaultRenderEffect == nullptr)
	{
		HRASSERT(m_pDefaultRenderEffect, "GetDefaultRenderEffect Error!");
	}

	return m_pDefaultRenderEffect;
}

HrResourcePtr HrResourceManager::LoadResource(const std::string& strFile, HrResource::EnumResourceType resType)
{
	HrResourcePtr pReturnRes = nullptr;

	switch (resType)
	{
	case Hr::HrResource::RT_UNKNOWN:
		break;
	case Hr::HrResource::RT_MESH:
	case Hr::HrResource::RT_EFFECT:
	case Hr::HrResource::RT_MESHMODEL:
	case Hr::HrResource::RT_TEXTURE_1D:
	case Hr::HrResource::RT_TEXTURE_2D:
	case Hr::HrResource::RT_TEXTURE_3D:
	case Hr::HrResource::RT_TEXTURE_CUBE:
	{
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
		break;
	}
	case Hr::HrResource::RT_MATERIAL:
	{
		pReturnRes = AddResource(strFile, resType);
		pReturnRes->Load();

		break;
	}
	default:
		break;
	}


	return pReturnRes;
}

HrResourcePtr HrResourceManager::RetriveResource(const std::string& strFile, HrResource::EnumResourceType resType)
{
	switch (resType)
	{
	case HrResource::RT_TEXTURE_2D:
		return GetTexture2D(strFile);
	case HrResource::RT_MESH:
		return GetMesh(strFile);
	case HrResource::RT_EFFECT:
		return GetEffect(strFile);
	case HrResource::RT_MATERIAL:
		return GetMaterial(strFile);
	case HrResource::RT_MESHMODEL:
		return GetMeshModel(strFile);
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
	case HrResource::RT_TEXTURE_2D:
		return AddTesture2DResource(strFile);
	case HrResource::RT_MESH:
		return AddMeshResource(strFile);
	case HrResource::RT_EFFECT:
		return AddEffectResource(strFile);
	case HrResource::RT_MATERIAL:
		return AddMaterialResource(strFile);
	case HrResource::RT_MESHMODEL:
		return AddMeshModelResource(strFile);
	default:
		break;
	}

	return nullptr;
}

HrResourcePtr HrResourceManager::AddMeshModelResource(const std::string& strFile)
{
	std::string strFileName = strFile.substr(strFile.rfind(HrFileUtils::m_s_strSeparator) + 1, strFile.size());
	
	HrMeshModelPtr pRes;
	if (strFile == "BuildIn_Grid")
		pRes = HrMakeSharedPtr<HrMeshModelGrid>();
	else
		pRes = HrMakeSharedPtr<HrMeshModelObject>();

	pRes->DeclareResource(strFileName, strFile);
	if (m_mapMeshModels.find(pRes->GetHashID()) != m_mapMeshModels.end())
	{
		pRes = nullptr;
		HRASSERT(nullptr, "AddMeshModelResource Error!");

		return nullptr;
	}
	m_mapMeshModels.insert(std::make_pair(pRes->GetHashID(), pRes));

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
	if (strFullFileName.empty())
		strFullFileName = strFile;
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
	if (strFullFileName.empty())
	{
		std::string strMaterialName = "Material_" + strFile;
		HrMaterialPtr pDefaultMaterial = HrMakeSharedPtr<HrMaterial>();
		pDefaultMaterial->DeclareResource(strMaterialName, strMaterialName);
		m_mapMaterials.insert(std::make_pair(pDefaultMaterial->GetHashID(), pDefaultMaterial));

		pDefaultMaterial->CopyFrom(m_pDefaultMaterial);

		return pDefaultMaterial;

	}
	else
	{
		std::string strFileName = strFile.substr(strFile.rfind(HrFileUtils::m_s_strSeparator) + 1, strFile.size());
		HrMaterialPtr pMaterial = HrMakeSharedPtr<HrMaterial>();
		pMaterial->DeclareResource(strFileName, strFile);
		m_mapMaterials.insert(std::make_pair(pMaterial->GetHashID(), pMaterial));

		return pMaterial;
	}

}

HrResourcePtr HrResourceManager::AddTesture2DResource(const std::string& strFile)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strFile);
	size_t nHashID = HrTexture::CreateHashName(strFullFileName);
	if (m_mapTextures2D.find(nHashID) != m_mapTextures2D.end())
	{
		HRASSERT(nullptr, "AddMeshResource Error!");
		return nullptr;
	}

	std::string strFileName = strFile.substr(strFile.rfind(HrFileUtils::m_s_strSeparator) + 1, strFile.size());
	HrTexturePtr pTexture = HrDirector::Instance()->GetRenderModule()->GetRenderFactory()->CreateTexture2D(1, 1, 1, 1, 1, 0
		, HrTexture::EAH_GPU_READ | HrTexture::EAH_GPU_WRITE, EnumPixelFormat::PF_R8G8B8A8_UINT);
	pTexture->DeclareResource(strFileName, strFile);
	pTexture->SetTextureType(HrTexture::TEX_TYPE_2D);
	m_mapTextures2D.insert(std::make_pair(pTexture->GetHashID(), pTexture));

	return pTexture;
}

HrResourcePtr HrResourceManager::GetTexture2D(const std::string& strTextureName)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strTextureName);
	size_t nHashID = HrTexture::CreateHashName(strFullFileName);
	auto item = m_mapTextures2D.find(nHashID);
	if (item != m_mapTextures2D.end())
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
	size_t nHashID = HrRenderEffect::CreateHashName(strFullFileName);
	auto item = m_mapRenderEffects.find(nHashID);
	if (item != m_mapRenderEffects.end())
	{
		return item->second;
	}

	return nullptr;
}

HrResourcePtr HrResourceManager::GetMaterial(const std::string& strMaterialName)
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

HrResourcePtr HrResourceManager::GetMeshModel(const std::string& strModelName)
{
	std::string strFullFileName = HrFileUtils::Instance()->GetFullPathForFileName(strModelName);
	size_t nHashID = HrMeshModel::CreateHashName(strFullFileName);
	auto item = m_mapMeshModels.find(nHashID);
	if (item != m_mapMeshModels.end())
	{
		return item->second;
	}
	return nullptr;
}

HrMaterialPtr HrResourceManager::MakeMaterial(const HrModelDataInfo::HrMaterialDataInfo& materialDataInfo)
{
	auto& pRes = AddMaterialResource(materialDataInfo.strMaterialName);
	pRes->Load();
	HrMaterialPtr pMaterial = HrCheckPointerCast<HrMaterial>(pRes);
	pMaterial->FillMaterialInfo(materialDataInfo);

	return pMaterial;
}

bool HrResourceManager::RemoveResource(const std::string& strFile, HrResource::EnumResourceType resType)
{
	switch (resType)
	{
	case HrResource::RT_MESHMODEL:
		return RemoveMeshModel(strFile);
	case HrResource::RT_MESH:
		return RemoveMesh(strFile);
	case HrResource::RT_MATERIAL:
		return RemoveMaterial(strFile);
	default:
		break;
	}
}

bool HrResourceManager::RemoveMeshModel(const std::string& strModelName)
{
	size_t nHashID = HrMeshModel::CreateHashName(strModelName);
	auto item = m_mapMeshModels.find(nHashID);
	if (item != m_mapMeshModels.end())
	{
		if (item->second->Unload())
			m_mapMeshModels.erase(item);

		return true;
	}

	return false;
}

bool HrResourceManager::RemoveMesh(const std::string& strMeshName)
{
	size_t nHashID = HrMesh::CreateHashName(strMeshName);
	auto item = m_mapMesh.find(nHashID);
	if (item != m_mapMesh.end())
	{
		if (item->second->Unload())
			m_mapMesh.erase(item);

		return true;
	}

	return false;
}

bool HrResourceManager::RemoveMaterial(const std::string& strMaterialName)
{
	size_t nHashID = HrMaterial::CreateHashName(strMaterialName);
	auto item = m_mapMaterials.find(nHashID);
	if (item != m_mapMaterials.end())
	{
		if (item->second->Unload())
			m_mapMaterials.erase(item);

		return true;
	}

	return false;
}

