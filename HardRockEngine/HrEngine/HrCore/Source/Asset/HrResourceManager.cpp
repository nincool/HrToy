#include "Asset/HrResourceManager.h"
#include "Asset/HrStreamData.h"
#include "Asset/HrResourceLoader.h"
#include "Asset/HrPrefebModel.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"

using namespace Hr;

HrResourceManager::HrResourceManager()
{

}

HrResourceManager::~HrResourceManager()
{

}

void HrResourceManager::InitResourceManager()
{
}

HrResource* HrResourceManager::LoadResource(std::string& strFile)
{
	if (HrFileUtils::Instance()->IsFileExist(strFile))
	{
		std::string strfileSuffix = HrFileUtils::Instance()->GetFileSuffix(strFile);
		if (strfileSuffix == "fbx")
		{
			HrResource* pRes = AddFBXResource(strFile);
			//HrResourceLoader::Instance()->SyncLoad(pRes);
		}
	}

	return nullptr;
}

HrResource* HrResourceManager::GetResource(std::string& strName)
{
	return nullptr;
}

HrResource* HrResourceManager::AddFBXResource(std::string& strFile)
{
	std::string strFileName = strFile.substr(strFile.rfind("/") + 1, strFile.size());
	HrResource* pRes = HR_NEW HrPrefebModel();
	pRes->DeclareResource(strFile, strFileName);

	if (m_mapPrefebModels.find(pRes->GetHashID()) != m_mapPrefebModels.end())
	{
		SAFE_DELETE(pRes);
		HRASSERT(nullptr, "AddFBXResource Error!");
		return;
	}
	m_mapPrefebModels[pRes->GetHashID()] = pRes;

	return pRes;
}

