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
	std::string strContentData = HrFileUtils::Instance()->GetFileString(strFile);
	rapidjson::Document d;
	d.Parse<0>(strContentData.c_str());
	if (d.HasParseError())
	{
		int nErrorCode = d.GetParseError();
		int nOffset = d.GetErrorOffset();
		HRERROR("HrJsonLoader::Load Error! ParseJsonFile Error! FileName[%s] ErrorCode[%d] Offset[%d]", strFile.c_str(), nErrorCode, nOffset);
		
		return;
	}
	modelDesc.strFilePath = strFile;
	std::string strTexturePath = strFile.substr(0, strFile.rfind('\\'));
	modelDesc.strFileName = HrFileUtils::Instance()->GetFileName(strFile);

	const rapidjson::Value& meshesInfo = d["Meshes"];
	int nSubMeshCount = meshesInfo["SubMeshesCount"].GetInt();
	for (int nSubMeshIndex = 0; nSubMeshIndex < nSubMeshCount; ++nSubMeshIndex)
	{
		modelDesc.vecSubMeshInfo.emplace_back();
		HrModelDataInfo::HrSubMeshDataInfo& subMeshData = modelDesc.vecSubMeshInfo.back();
		subMeshData.strMeshName = HrStringUtil::StringFormat("SubMesh_%d", nSubMeshIndex);
		const rapidjson::Value& subMeshInfo = meshesInfo[subMeshData.strMeshName.c_str()];
		subMeshData.vecIndices = HrStringUtil::GetTVectorFromString<uint32>(subMeshInfo["Indices"].GetString(), ",");
		subMeshData.vecVertexPos = HrStringUtil::GetVectorFloat3FromString(subMeshInfo["Vertices"].GetString(), "|", ",");
		subMeshData.vecNormal = HrStringUtil::GetVectorFloat3FromString(subMeshInfo["Normals"].GetString(), "|", ",");
		subMeshData.vecUV = HrStringUtil::GetVectorFloat2FromString(subMeshInfo["UVs"].GetString(), "|", ",");
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
		materialData.fShininess = 0;
		materialData.fGlossiness = materialInfo["Glossiness"].GetFloat();
		materialData.fReflective = materialInfo["Reflective"].GetFloat();
		materialData.bTwoSided = materialInfo["TwoSided"].GetInt() == 0;
		for (int nTexIndex = 0; nTexIndex < HrModelDataInfo::HrMaterialDataInfo::TS_NUMTEXTURESLOTS; ++nTexIndex)
		{
			std::string strTextureKey = "Texture_" + std::to_string(nTexIndex);
			std::string strTexture = materialInfo[strTextureKey.c_str()].GetString();
			if (strTexture.length() > 0)
			{
				strTexture = strTexturePath + "\\" + strTexture;
				materialData.m_arrTexNames[nTexIndex] = strTexture;
			}
		}
	}


}
