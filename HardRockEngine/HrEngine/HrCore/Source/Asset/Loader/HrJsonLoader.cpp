#include "Asset/Loader/HrJsonLoader.h"
#include "Asset/HrStreamData.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrLog.h"
#include "HrUtilTools/Include/HrStringUtil.h"


using namespace Hr;

HrJsonLoader::HrJsonLoader()
{

}

HrJsonLoader::~HrJsonLoader()
{

}

void HrJsonLoader::Load(std::string& strFile, HrModelDataInfo& modelDesc)
{
	HrStreamDataPtr pStreamData = HrFileUtils::Instance()->GetFileData(strFile);
	rapidjson::Document d;
	d.Parse<0>(pStreamData->GetBufferPoint());
	if (d.HasParseError())
	{
		int nErrorCode = d.GetParseError();
		int nOffset = d.GetErrorOffset();
		HRERROR("HrJsonLoader::Load Error! ParseJsonFile Error! FileName[%s] ErrorCode[%d] Offset[%d]", strFile.c_str(), nErrorCode, nOffset);
		
		return;
	}

	std::string strTexturePath = strFile.substr(0, strFile.rfind('\\'));

	const rapidjson::Value& meshesInfo = d["Meshes"];
	int nSubMeshCount = meshesInfo["SubMeshesCount"].GetInt();
	for (int nSubMeshIndex = 0; nSubMeshIndex < nSubMeshCount; ++nSubMeshIndex)
	{
		modelDesc.vecSubMeshInfo.emplace_back();
		HrModelDataInfo::HrSubMeshDataInfo& subMeshData = modelDesc.vecSubMeshInfo.back();
		const rapidjson::Value& subMeshInfo = meshesInfo[HrStringUtil::StringFormat("SubMesh_%d", nSubMeshIndex).c_str()];
		
		subMeshData.vecIndices = HrStringUtil::GetTVectorFromString<uint32>(subMeshInfo["Indices"].GetString(), ",");
		subMeshData.vecVertexPos = HrStringUtil::GetVectorVector3FromString(subMeshInfo["Vertices"].GetString(), "|", ",");
		subMeshData.vecNormal = HrStringUtil::GetVectorVector3FromString(subMeshInfo["Normals"].GetString(), "|", ",");
	}

	const rapidjson::Value& materialsInfo = d["Materials"];
	int nMaterialCount = materialsInfo["MaterialCount"].GetInt();
	for (int nMaterialIndex = 0; nMaterialIndex < nMaterialCount; ++nMaterialIndex)
	{
		modelDesc.vecMaterialDataInfo.emplace_back();
		HrModelDataInfo::HrMaterialDataInfo& materialData = modelDesc.vecMaterialDataInfo.back();
		const rapidjson::Value& materialInfo = materialsInfo[HrStringUtil::StringFormat("Material_%d", nMaterialIndex).c_str()];

		materialData.nMaterialIndex = nMaterialIndex;

		materialData.v4Albedo = HrStringUtil::GetFloat4FromString(materialInfo["Albedo"].GetString());
		materialData.v4Emissive = HrStringUtil::GetFloat4FromString(materialInfo["Emissibe"].GetString());
		materialData.fOpacity = materialInfo["Opacity"].GetFloat();
		materialData.fShininess = materialInfo["Shininess"].GetFloat();
		materialData.fGlossiness = HrMath::Shininess2Glossiness(materialData.fShininess);
		materialData.bTwoSided = materialInfo["TwoSided"].GetInt() == 0;
		for (int nTexIndex = 0; nTexIndex < HrModelDataInfo::HrMaterialDataInfo::TS_NUMTEXTURESLOTS; ++nTexIndex)
		{
			std::string strTextureKey = "Texture_" + std::to_string(nTexIndex);
			std::string strTexture = materialInfo[strTextureKey.c_str()].GetString();

			materialData.m_arrTexNames[nTexIndex] = strTexture;
		}
	}


}
