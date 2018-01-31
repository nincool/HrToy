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
	m_resStatus = HrResource::RS_DECLARED;

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

	//Mesh only fbx
	std::string strFileName = sceneRootInfo["RESOURCE_FILE"].GetString();
	HrModelLoaderPtr pModelLoader = std::make_shared<HrModelLoader>();
	pModelLoader->Load(strFileName);
	m_pMesh = pModelLoader->GetMesh();
	
	return true;
}

bool HrPrefabModel::UnloadImpl()
{
	return false;
}

const HrMeshPtr& HrPrefabModel::GetMesh() const
{
	return m_pMesh;
}
