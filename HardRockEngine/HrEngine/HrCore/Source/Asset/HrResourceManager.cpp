#include "Asset/HrResourceManager.h"
#include "Asset/HrStreamData.h"
#include "Asset/HrResourceLoader.h"
#include "Asset/HrPrefebModel.h"
#include "Asset/HrMesh.h"
#include "Asset/HrRenderEffect.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrFileUtils.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrResourceManager::HrResourceManager()
{

}

HrResourceManager::~HrResourceManager()
{

}

void HrResourceManager::InitResourceManager()
{
	CreateBuildInEffects();
}

HrResource* HrResourceManager::LoadResource(const std::string& strFile)
{
	if (HrFileUtils::Instance()->IsFileExist(strFile))
	{
		std::string strfileSuffix = HrFileUtils::Instance()->GetFileSuffix(strFile);
		if (strfileSuffix == "fbx")
		{
			HrResource* pRes = AddFBXResource(strFile);
		}
		else if (strfileSuffix == "hxml")
		{
			HrResource* pRes = AddEffectResource(strFile);
		}
	}

	return nullptr;
}

HrResource* HrResourceManager::GetResource(const std::string& strFile, HrResource::EnumResourceType resType)
{
	switch (resType)
	{
	case HrResource::RT_TEXTURE:
		break;
	case HrResource::RT_MESH:
		break;
	case HrResource::RT_EFFECT:
		return GetEffect(strFile);
		break;
	case HrResource::RT_MATERIAL:
		break;
	case HrResource::RT_MODEL:
		break;
	default:
		break;
	}
	
	return nullptr;
}

HrResource* HrResourceManager::CreateMeshManual(const std::string& strName, std::string& strFile)
{
	HrResource* pMesh = HR_NEW HrMesh();
	pMesh->DeclareResource(strName, strFile);
	size_t nMeshHashID = pMesh->GetHashID();
	if (m_mapMesh.find(nMeshHashID) != m_mapMesh.end())
	{
		return nullptr;
	}
	m_mapMesh.insert(std::make_pair(nMeshHashID, pMesh));

	return pMesh;
}

HrResource* HrResourceManager::AddFBXResource(const std::string& strFile)
{
	std::string strFileName = strFile.substr(strFile.rfind("/") + 1, strFile.size());
	HrResource* pRes = HR_NEW HrPrefebModel();
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

void HrResourceManager::CreateBuildInEffects()
{
	std::string strEffectFile;

	strEffectFile = "Media/HrShader/HrBasicEffect.hxml";
	HrResource* pRes = AddEffectResource(strEffectFile);
	pRes->Load();
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

