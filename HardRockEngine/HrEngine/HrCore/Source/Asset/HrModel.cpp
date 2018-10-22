#include "Asset/HrModel.h"
#include "Asset/HrMesh.h"
#include "Asset/HrTexture.h"
#include "Asset/HrMaterial.h"
#include "Asset/HrResourceManager.h"
#include "Asset/Loader/HrModelLoader.h"
#include "Asset/Loader/HrFBXLoader.h"
#include "Asset/HrStreamData.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrResourceModule.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrUtilTools/Include/HrStringUtil.h"
#include "ThirdParty/rapidjson/include/rapidjson/document.h"

#include <boost/format.hpp>


using namespace Hr;
using namespace std;

HrModel::HrModel()
{

}

HrModel::~HrModel()
{

}

size_t HrModel::CreateHashName(const std::string& strFullFilePath)
{
	return HrHashValue(strFullFilePath);
}

void HrModel::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFilePath = strFilePath;
	m_strFileName = strFileName;
	m_resType = HrResource::RT_MODEL;
	m_resStatus = HrResource::RS_DECLARED;

	m_nHashID = CreateHashName(m_strFilePath);
}

bool HrModel::LoadImpl()
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
		size_t nOffset = d.GetErrorOffset();
		HRERROR("HrSceneImported::LoadScene Error! ParseJsonFile Error! ErrorCode[%d] Offset[%d]", nErrorCode, nOffset);
		return false;
	}

	const rapidjson::Value& sceneRootInfo = d["ASSET_ROOT"];

	//Mesh only fbx
	{
		std::string strFileName = sceneRootInfo["RESOURCE_FILE"].GetString();
		HrModelLoaderPtr pModelLoader = std::make_shared<HrModelLoader>();
		pModelLoader->Load(strFileName);
		m_pMesh = pModelLoader->GetMesh();
	}

	//todo submesh fbx还是不行
	{
		//if (sceneRootInfo.HasMember("TEXTURE_SAMPLER"))
		//{
		//	std::string strTextureFile = sceneRootInfo["TEXTURE_SAMPLER"].GetString();
		//	HrTexturePtr pTexSampler = HrDirector::Instance()->GetResourceModule()->RetriveTexture(strTextureFile, HrTexture::TEX_TYPE_2D);
		//	m_pMesh->GetSubMesh(0)->GetMaterial()->SetTexture(HrMaterial::TS_SLOT_0, pTexSampler);
		//}
	}
	
	return true;
}

bool HrModel::UnloadImpl()
{
	return false;
}

const HrMeshPtr& HrModel::GetMesh() const
{
	return m_pMesh;
}
