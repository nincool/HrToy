#include "stdafx.h"
#include "HrConvertUtil.h"
#include "HrUtilTools/Include/HrStringUtil.h"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <experimental/filesystem>
#include <iostream>
#include <fstream>

using namespace Hr;
using namespace std::experimental;

HrConvertUtil::HrConvertUtil()
{
	m_bLoadSuccess = false;
	m_fUnitScale = 1.0f;
	m_fOutputUnitScale = 1.0f;
}

HrConvertUtil::~HrConvertUtil()
{

}

bool HrConvertUtil::LoadOriginalData(std::string const & in_name)
{
	m_strOriginalFile = in_name;
	m_strOriginalPath = HrFileUtils::Instance()->GetFilePath(m_strOriginalFile);

	aiPropertyStore* props = aiCreatePropertyStore();
	aiSetImportPropertyInteger(props, AI_CONFIG_IMPORT_TER_MAKE_UVS, 1);
	aiSetImportPropertyFloat(props, AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, 80);
	aiSetImportPropertyInteger(props, AI_CONFIG_PP_SBP_REMOVE, 0);

	aiSetImportPropertyInteger(props, AI_CONFIG_GLOB_MEASURE_TIME, 1);

	unsigned int ppsteps = aiProcess_JoinIdenticalVertices // join identical vertices/ optimize indexing
		| aiProcess_ValidateDataStructure // perform a full validation of the loader's output
		| aiProcess_RemoveRedundantMaterials // remove redundant materials
		| aiProcess_FindInstances; // search for instanced meshes and remove them by references to one master

	aiScene const * scene = aiImportFileExWithProperties(in_name.c_str(),
		ppsteps // configurable pp steps
		| aiProcess_GenSmoothNormals // generate smooth normal vectors if not existing
		| aiProcess_Triangulate // triangulate polygons with more than 3 edges
		| aiProcess_ConvertToLeftHanded // convert everything to D3D left handed space
		| aiProcess_FixInfacingNormals, // find normals facing inwards and inverts them
		nullptr, props);

	aiReleasePropertyStore(props);

	if (!scene)
	{
		std::cout << "Assimp: Import file error: " << aiGetErrorString() << '\n';
		return false;
	}

	//MeshMLObj meshml_obj(scale);
	//ConvertMaterials(meshml_obj, scene);

	//std::vector<Mesh> meshes(scene->mNumMeshes);
	//JointsMap joint_nodes;

	//int vertex_export_settings;
	//BuildJoints(meshml_obj, joint_nodes, scene);
	//BuildMeshData(meshes, vertex_export_settings, joint_nodes, scene, swap_yz, inverse_z);
	//RecursiveTransformMesh(meshml_obj, float4x4::Identity(), scene->mRootNode, meshes);
	//BuildActions(meshml_obj, joint_nodes, scene);

	//std::ofstream ofs(out_name.c_str());
	//meshml_obj.WriteMeshML(ofs, vertex_export_settings, 0);
	m_bLoadSuccess = true;

	m_modelDesc.vecSubMeshInfo.clear();
	m_modelDesc.vecMaterialDataInfo.clear();
	m_modelDesc.strFileName = Hr::HrFileUtils::Instance()->GetFileName(in_name);


	BuildMeshData(scene);
	RecursiveTransformMesh(float4x4::Identity(), scene->mRootNode, m_modelDesc.vecSubMeshInfo);
	BuildMaterialData(scene);
	
	aiReleaseImport(scene);

	ComputeAABB();

	return true;
}

void HrConvertUtil::ComputeAABB()
{
	for (size_t nSubMeshIndex = 0; nSubMeshIndex < m_modelDesc.vecSubMeshInfo.size(); ++nSubMeshIndex)
	{
		uint32 nMaxIndex = 0, nMinIndex = 0;
		Vector3 v3MinPoint, v3MaxPoint;
		ComputeExtrameDistanceAlongDir(Vector3(1, 0, 0), m_modelDesc.vecSubMeshInfo[nSubMeshIndex].vecVertexPos, nMaxIndex, nMinIndex);
		v3MinPoint.x() = m_modelDesc.vecSubMeshInfo[nSubMeshIndex].vecVertexPos[nMinIndex].x();
		v3MaxPoint.x() = m_modelDesc.vecSubMeshInfo[nSubMeshIndex].vecVertexPos[nMaxIndex].x();

		ComputeExtrameDistanceAlongDir(Vector3(0, 1, 0), m_modelDesc.vecSubMeshInfo[nSubMeshIndex].vecVertexPos, nMaxIndex, nMinIndex);
		v3MinPoint.y() = m_modelDesc.vecSubMeshInfo[nSubMeshIndex].vecVertexPos[nMinIndex].y();
		v3MaxPoint.y() = m_modelDesc.vecSubMeshInfo[nSubMeshIndex].vecVertexPos[nMaxIndex].y();

		ComputeExtrameDistanceAlongDir(Vector3(0, 0, 1), m_modelDesc.vecSubMeshInfo[nSubMeshIndex].vecVertexPos, nMaxIndex, nMinIndex);
		v3MinPoint.z() = m_modelDesc.vecSubMeshInfo[nSubMeshIndex].vecVertexPos[nMinIndex].z();
		v3MaxPoint.z() = m_modelDesc.vecSubMeshInfo[nSubMeshIndex].vecVertexPos[nMaxIndex].z();

		m_modelDesc.vecSubMeshInfo[nSubMeshIndex].aabb = AABBox(v3MinPoint, v3MaxPoint);
	}

}


void HrConvertUtil::ComputeExtrameDistanceAlongDir(const Vector3& vDir, const std::vector<Vector3>& vecVertices, uint32& nMax, uint32& nMin)
{
	float fMaxProj = -FLT_MAX, fMinProj = FLT_MAX;
	for (size_t i = 0; i < vecVertices.size(); ++i)
	{
		float fProjection = HrMath::Dot(vecVertices[i], vDir);

		if (fProjection > fMaxProj)
		{
			fMaxProj = fProjection;
			nMax = i;
		}

		if (fProjection < fMinProj)
		{
			fMinProj = fProjection;
			nMin = i;
		}
	}
}

bool HrConvertUtil::WriteModelDataToFile(const std::string& strOutPath)
{
	if (m_bLoadSuccess)
	{
		rapidjson::Document doc;
		doc.SetObject();

		WriteMeshData(doc);
		WriteMaterialData(doc);
		FlushDataToFile(strOutPath, doc);

		return true;
	}

	return false;
}

void HrConvertUtil::BuildMeshData(const aiScene* pAssimpScene)
{
	for (uint32 nMeshIndex = 0; nMeshIndex < pAssimpScene->mNumMeshes; ++nMeshIndex)
	{
		m_modelDesc.vecSubMeshInfo.emplace_back();
		HrModelDataInfo::HrSubMeshDataInfo& subMeshInfo = m_modelDesc.vecSubMeshInfo[m_modelDesc.vecSubMeshInfo.size() - 1];
		const aiMesh* pAssimpMesh = pAssimpScene->mMeshes[nMeshIndex];

		uint32 nMaterialIndex = pAssimpMesh->mMaterialIndex;
		std::string strName = pAssimpMesh->mName.C_Str();
		if (strName.empty())
			strName = Hr::HrStringUtil::StringFormat("SubMesh_%d", nMeshIndex);
		subMeshInfo.strMeshName = strName;

		//indices
		for (uint32 nFaceIndex = 0; nFaceIndex < pAssimpMesh->mNumFaces; ++nFaceIndex)
		{
			BOOST_ASSERT(3 == pAssimpMesh->mFaces[nFaceIndex].mNumIndices);

			subMeshInfo.vecIndices.push_back(pAssimpMesh->mFaces[nFaceIndex].mIndices[0]);
			subMeshInfo.vecIndices.push_back(pAssimpMesh->mFaces[nFaceIndex].mIndices[1]);
			subMeshInfo.vecIndices.push_back(pAssimpMesh->mFaces[nFaceIndex].mIndices[2]);
		}

		subMeshInfo.nTriangleCount = pAssimpMesh->mNumFaces;

		bool bHasNormal = (pAssimpMesh->mNormals != nullptr);
		bool bHasTangent = (pAssimpMesh->mTangents != nullptr);
		bool bHasBinormal = (pAssimpMesh->mBitangents != nullptr);
		
		for (uint32 nVertexIndex = 0; nVertexIndex < pAssimpMesh->mNumVertices; ++nVertexIndex)
		{
			{
				float fX = pAssimpMesh->mVertices[nVertexIndex].x;
				float fY = pAssimpMesh->mVertices[nVertexIndex].y;
				float fZ = pAssimpMesh->mVertices[nVertexIndex].z;
				subMeshInfo.vecVertexPos.emplace_back(fX, fY, fZ);
			}

			if (bHasNormal)
			{
				float fX = pAssimpMesh->mNormals[nVertexIndex].x;
				float fY = pAssimpMesh->mNormals[nVertexIndex].y;
				float fZ = pAssimpMesh->mNormals[nVertexIndex].z;
				subMeshInfo.vecNormal.emplace_back(fX, fY, fZ);
			}

			if (bHasTangent)
			{
				float fX = pAssimpMesh->mTangents[nVertexIndex].x;
				float fY = pAssimpMesh->mTangents[nVertexIndex].y;
				float fZ = pAssimpMesh->mTangents[nVertexIndex].z;
				subMeshInfo.vecTangent.emplace_back(fX, fY, fZ);
			}

			if (bHasBinormal)
			{
				float fX = pAssimpMesh->mBitangents[nVertexIndex].x;
				float fY = pAssimpMesh->mBitangents[nVertexIndex].y;
				float fZ = pAssimpMesh->mBitangents[nVertexIndex].z;
				subMeshInfo.vecBinormal.emplace_back(fX, fY, fZ);
			}

			//先存储一个uv坐标
			{
				aiVector3D* pTexCoords = nullptr;
				for (uint32 nTexcoordIndex = 0; nTexcoordIndex < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++nTexcoordIndex)
				{
					if (pAssimpMesh->mTextureCoords[nTexcoordIndex] != nullptr)
					{
						pTexCoords = pAssimpMesh->mTextureCoords[nTexcoordIndex];
						break;
					}
				}
				if (pTexCoords)
				{
					float fU = pTexCoords[nVertexIndex].x;
					float fV = pTexCoords[nVertexIndex].y;
					subMeshInfo.vecUV.emplace_back(fU, fV);
				}
			}
		}

		//判断是否使用indices 
		//1.indices等于vertices个数，那么没有用indices 
		//2.indices小于vertices那么使用了indices
		if (subMeshInfo.vecIndices.size() == subMeshInfo.vecVertexPos.size())
		{
			subMeshInfo.bAllIndices = false;
		}
		else if (subMeshInfo.vecIndices.size() > subMeshInfo.vecVertexPos.size())
		{
			subMeshInfo.bAllIndices = true;
		}
		else
		{
			subMeshInfo.bAllIndices = true;
		}

	}
}

void HrConvertUtil::BuildMaterialData(const aiScene* pAssimpScene)
{
	for (uint32 nMaterialIndex = 0; nMaterialIndex < pAssimpScene->mNumMaterials; ++nMaterialIndex)
	{
		m_modelDesc.vecMaterialDataInfo.emplace_back();
		HrModelDataInfo::HrMaterialDataInfo& materialDataInfo = m_modelDesc.vecMaterialDataInfo[m_modelDesc.vecMaterialDataInfo.size() - 1];

		aiMaterial* pMaterial = pAssimpScene->mMaterials[nMaterialIndex];

		std::string strName;
		float4 albedo(0, 0, 0, 0);
		float4 emissive(0, 0, 0, 0);
		float opacity = 1;
		float shininess = 1;
		float reflective = 1;
		bool transparent = false;
		bool two_sided = false;

		aiString aiName;
		aiColor4D aiAlbedo;
		aiColor4D aiEmissive;
		float aiOpacity;
		float aiShininess;
		float aiReflective;
		int aiTwosided;

		if (AI_SUCCESS == aiGetMaterialString(pMaterial, AI_MATKEY_NAME, &aiName))
		{
			strName = aiName.C_Str();
			materialDataInfo.strMaterialName = strName;
		}
		if (AI_SUCCESS == aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_DIFFUSE, &aiAlbedo))
		{
			albedo = Color4ToFloat4(aiAlbedo);
			materialDataInfo.v4Albedo = albedo;
		}
		if (AI_SUCCESS == aiGetMaterialColor(pMaterial, AI_MATKEY_COLOR_EMISSIVE, &aiEmissive))
		{
			emissive = Color4ToFloat4(aiEmissive);
			materialDataInfo.v4Emissive = emissive;
		}

		unsigned int max = 1;
		if (AI_SUCCESS == aiGetMaterialFloatArray(pMaterial, AI_MATKEY_OPACITY, &aiOpacity, &max))
		{
			opacity = aiOpacity;
			materialDataInfo.fOpacity = opacity;
		}

		max = 1;
		if (AI_SUCCESS == aiGetMaterialFloatArray(pMaterial, AI_MATKEY_SHININESS, &aiShininess, &max))
		{
			shininess = aiShininess;

			max = 1;
			float strength;
			if (AI_SUCCESS == aiGetMaterialFloatArray(pMaterial, AI_MATKEY_SHININESS_STRENGTH, &strength, &max))
			{
				shininess *= strength;
			}

			shininess = HrMath::Clamp(shininess, 1.0f, HrMath::MAX_SHININESS);
			materialDataInfo.fShininess = shininess;
			materialDataInfo.fGlossiness = HrMath::Shininess2Glossiness(shininess);

		}
		

		if ((opacity < 1) || (aiGetMaterialTextureCount(pMaterial, aiTextureType_OPACITY) > 0))
		{
			transparent = true;
		}

		max = 1;
		if (AI_SUCCESS == aiGetMaterialFloatArray(pMaterial, AI_MATKEY_REFLECTIVITY, &aiReflective, &max))
		{
			reflective = aiReflective;
			materialDataInfo.fReflective = reflective;
		}
		

		max = 1;
		if (AI_SUCCESS == aiGetMaterialIntegerArray(pMaterial, AI_MATKEY_TWOSIDED, &aiTwosided, &max))
		{
			two_sided = aiTwosided ? true : false;
		}
		materialDataInfo.bTwoSided = two_sided;

		unsigned int count = aiGetMaterialTextureCount(pMaterial, aiTextureType_DIFFUSE);
		if (count > 0)
		{
			aiString str;
			aiGetMaterialTexture(pMaterial, aiTextureType_DIFFUSE, 0, &str, 0, 0, 0, 0, 0, 0);
			std::string strTexture = str.C_Str();
			materialDataInfo.m_arrTexNames[HrModelDataInfo::HrMaterialDataInfo::TS_ALBEDO] = strTexture;
		}

		count = aiGetMaterialTextureCount(pMaterial, aiTextureType_SHININESS);
		if (count > 0)
		{
			aiString str;
			aiGetMaterialTexture(pMaterial, aiTextureType_SHININESS, 0, &str, 0, 0, 0, 0, 0, 0);
			std::string strTexture = str.C_Str();
			materialDataInfo.m_arrTexNames[HrModelDataInfo::HrMaterialDataInfo::TS_GLOSSINESS] = strTexture;
		}

		count = aiGetMaterialTextureCount(pMaterial, aiTextureType_EMISSIVE);
		if (count > 0)
		{
			aiString str;
			aiGetMaterialTexture(pMaterial, aiTextureType_EMISSIVE, 0, &str, 0, 0, 0, 0, 0, 0);
			std::string strTexture = str.C_Str();
			materialDataInfo.m_arrTexNames[HrModelDataInfo::HrMaterialDataInfo::TS_EMISSIVE] = strTexture;
		}

		count = aiGetMaterialTextureCount(pMaterial, aiTextureType_NORMALS);
		if (count > 0)
		{
			aiString str;
			aiGetMaterialTexture(pMaterial, aiTextureType_NORMALS, 0, &str, 0, 0, 0, 0, 0, 0);
			std::string strTexture = str.C_Str();
			materialDataInfo.m_arrTexNames[HrModelDataInfo::HrMaterialDataInfo::TS_NORMAL] = strTexture;
		}

		count = aiGetMaterialTextureCount(pMaterial, aiTextureType_HEIGHT);
		if (count > 0)
		{
			aiString str;
			aiGetMaterialTexture(pMaterial, aiTextureType_HEIGHT, 0, &str, 0, 0, 0, 0, 0, 0);
			std::string strTexture = str.C_Str();
			materialDataInfo.m_arrTexNames[HrModelDataInfo::HrMaterialDataInfo::TS_HEIGHT] = strTexture;
		}
	}
}

void HrConvertUtil::CombineMesh()
{

}

std::string HrConvertUtil::MakeFloat3String(float3 v)
{
	std::string strRet;
	char cTemp[50];
	std::sprintf(cTemp, "%.2f", v[0]);
	strRet += cTemp;
	strRet += ",";
	std::sprintf(cTemp, "%.2f", v[1]);
	strRet += cTemp;
	strRet += ",";
	std::sprintf(cTemp, "%.2f", v[2]);
	strRet += cTemp;

	return strRet;
}

std::string HrConvertUtil::MakeFloat3StringWithEndMark(float3 v, const char c)
{
	std::string strRet;
	char cTemp[50];
	std::sprintf(cTemp, "%.2f", v[0]);
	strRet += cTemp;
	strRet += ",";
	std::sprintf(cTemp, "%.2f", v[1]);
	strRet += cTemp;
	strRet += ",";
	std::sprintf(cTemp, "%.2f", v[2]);
	strRet += cTemp;
	strRet += c;

	return strRet;
}

void HrConvertUtil::WriteMeshData(rapidjson::Document& doc)
{
	rapidjson::Value meshesObj(rapidjson::kObjectType);
	
	rapidjson::Value meshCountObj(rapidjson::kNumberType);
	meshCountObj.SetUint(m_modelDesc.vecSubMeshInfo.size());
	meshesObj.AddMember(rapidjson::StringRef("SubMeshesCount"), meshCountObj, doc.GetAllocator());

	for (size_t nSubMeshIndex = 0; nSubMeshIndex < m_modelDesc.vecSubMeshInfo.size(); ++nSubMeshIndex)
	{
		const HrModelDataInfo::HrSubMeshDataInfo& subMeshInfo = m_modelDesc.vecSubMeshInfo[nSubMeshIndex];
		
		rapidjson::Value subMeshKeyObj(rapidjson::kStringType);
		std::string strSubMeshName = ("SubMesh_" + std::to_string(nSubMeshIndex));
		subMeshKeyObj.SetString(strSubMeshName.c_str(), doc.GetAllocator());
		
		rapidjson::Value subMeshValueObj(rapidjson::kObjectType);

		{
			rapidjson::Value nameValueObj(rapidjson::kStringType);
			if (subMeshInfo.strMeshName.empty())
				nameValueObj.SetString(subMeshInfo.strMeshName.c_str(), doc.GetAllocator());
			else
				nameValueObj.SetString(subMeshInfo.strMeshName.c_str(), doc.GetAllocator());
			subMeshValueObj.AddMember(rapidjson::StringRef("Name"), nameValueObj, doc.GetAllocator());
		}

		{
			if (subMeshInfo.bAllIndices)
			{
				std::string strIndices;
				for (int nIndiceIndex = 0; nIndiceIndex < subMeshInfo.vecIndices.size(); ++nIndiceIndex)
				{
					strIndices += std::to_string(subMeshInfo.vecIndices[nIndiceIndex]);
					strIndices += ",";
				}
				rapidjson::Value indicesValueObj(rapidjson::kStringType);
				indicesValueObj.SetString(strIndices.c_str(), doc.GetAllocator());
				subMeshValueObj.AddMember(rapidjson::StringRef("Indices"), indicesValueObj, doc.GetAllocator());
			}
		}

		{
			std::string strVertices;
			for (int nVerticeIndex = 0; nVerticeIndex < subMeshInfo.vecVertexPos.size(); ++nVerticeIndex)
			{
				Vector3 vPos = subMeshInfo.vecVertexPos[nVerticeIndex] * m_fOutputUnitScale;
				strVertices += MakeFloat3StringWithEndMark(vPos);
			}
			rapidjson::Value verticesValueObj(rapidjson::kStringType);
			verticesValueObj.SetString(strVertices.c_str(), doc.GetAllocator());
			subMeshValueObj.AddMember(rapidjson::StringRef("Vertices"), verticesValueObj, doc.GetAllocator());
		}

		{
			std::string strTangents;
			for (int nTangentIndex = 0; nTangentIndex < subMeshInfo.vecTangent.size(); ++nTangentIndex)
			{
				Vector3 vTangent = subMeshInfo.vecTangent[nTangentIndex];
				strTangents += MakeFloat3StringWithEndMark(vTangent);
			}
			rapidjson::Value tangentsValueObj(rapidjson::kStringType);
			tangentsValueObj.SetString(strTangents.c_str(), doc.GetAllocator());
			subMeshValueObj.AddMember(rapidjson::StringRef("Tangents"), tangentsValueObj, doc.GetAllocator());
		}

		{
			std::string strBinormals;
			for (int nBinormalIndex = 0; nBinormalIndex < subMeshInfo.vecBinormal.size(); ++nBinormalIndex)
			{
				Vector3 vBinormal = subMeshInfo.vecBinormal[nBinormalIndex];
				strBinormals += MakeFloat3StringWithEndMark(vBinormal);
			}
			rapidjson::Value binormalValueObj(rapidjson::kStringType);
			binormalValueObj.SetString(strBinormals.c_str(), doc.GetAllocator());
			subMeshValueObj.AddMember(rapidjson::StringRef("Binormals"), binormalValueObj, doc.GetAllocator());
		}

		{
			std::string strNormals;
			for (int nNormalIndex = 0; nNormalIndex < subMeshInfo.vecNormal.size(); ++nNormalIndex)
			{
				Vector3 vecNormal = subMeshInfo.vecNormal[nNormalIndex];
				strNormals += MakeFloat3StringWithEndMark(vecNormal);
			}
			rapidjson::Value normalsValueObj(rapidjson::kStringType);
			normalsValueObj.SetString(strNormals.c_str(), doc.GetAllocator());
			subMeshValueObj.AddMember(rapidjson::StringRef("Normals"), normalsValueObj, doc.GetAllocator());
		}

		{
			std::string strUVs;
			for (int nUVIndex = 0; nUVIndex < subMeshInfo.vecUV.size(); ++nUVIndex)
			{
				float2 uv = subMeshInfo.vecUV[nUVIndex];
				char cTemp[30];
				std::sprintf(cTemp, "%.2f", uv[0]);
				strUVs += cTemp;
				strUVs += ",";
				std::sprintf(cTemp, "%.2f", uv[1]);
				strUVs += cTemp;
				strUVs += "|";
			}
			rapidjson::Value uvsValueObj(rapidjson::kStringType);
			uvsValueObj.SetString(strUVs.c_str(), doc.GetAllocator());
			subMeshValueObj.AddMember(rapidjson::StringRef("UVs"), uvsValueObj, doc.GetAllocator());
		}

		{
			std::string strAABB;
			strAABB += MakeFloat3StringWithEndMark(subMeshInfo.aabb.Min());
			strAABB += MakeFloat3StringWithEndMark(subMeshInfo.aabb.Max());
			rapidjson::Value aabbValueObj(rapidjson::kStringType);
			aabbValueObj.SetString(strAABB.c_str(), doc.GetAllocator());
			subMeshValueObj.AddMember(rapidjson::StringRef("AABB"), aabbValueObj, doc.GetAllocator());
		}

		meshesObj.AddMember(subMeshKeyObj, subMeshValueObj, doc.GetAllocator());
	}

	doc.AddMember(rapidjson::StringRef("Meshes"), meshesObj, doc.GetAllocator());
}

void HrConvertUtil::WriteMaterialData(rapidjson::Document& doc)
{
	rapidjson::Value materialObj(rapidjson::kObjectType);
	rapidjson::Value materialCountValue(rapidjson::kNumberType);
	materialCountValue.SetUint(m_modelDesc.vecMaterialDataInfo.size());
	materialObj.AddMember(rapidjson::StringRef("MaterialCount"), materialCountValue, doc.GetAllocator());

	for (int nMaterialIndex = 0; nMaterialIndex < m_modelDesc.vecMaterialDataInfo.size(); ++nMaterialIndex)
	{
		std::string strSubMaterialName = "Material_" + std::to_string(nMaterialIndex);
		rapidjson::Value subMaterialKey(rapidjson::kStringType);
		subMaterialKey.SetString(strSubMaterialName.c_str(), doc.GetAllocator());

		rapidjson::Value subMaterialObj(rapidjson::kObjectType);

		rapidjson::Value nameValue(rapidjson::kStringType);
		nameValue.SetString(m_modelDesc.vecMaterialDataInfo[nMaterialIndex].strMaterialName.c_str(), doc.GetAllocator());
		subMaterialObj.AddMember(rapidjson::StringRef("Name"), nameValue, doc.GetAllocator());

		rapidjson::Value albedoValue(rapidjson::kStringType);
		std::string strAlbedo = HrStringUtil::StringFormat("%.2f|%.2f|%.2f|%.2f|"
			, m_modelDesc.vecMaterialDataInfo[nMaterialIndex].v4Albedo[0]
			, m_modelDesc.vecMaterialDataInfo[nMaterialIndex].v4Albedo[1]
			, m_modelDesc.vecMaterialDataInfo[nMaterialIndex].v4Albedo[2]
			, m_modelDesc.vecMaterialDataInfo[nMaterialIndex].v4Albedo[3]);
		albedoValue.SetString(strAlbedo.c_str(), doc.GetAllocator());
		subMaterialObj.AddMember(rapidjson::StringRef("Albedo"), albedoValue, doc.GetAllocator());

		rapidjson::Value emissiveValue(rapidjson::kStringType);
		std::string strEmissive = HrStringUtil::StringFormat("%.2f|%.2f|%.2f|%.2f|"
			, m_modelDesc.vecMaterialDataInfo[nMaterialIndex].v4Emissive[0]
			, m_modelDesc.vecMaterialDataInfo[nMaterialIndex].v4Emissive[1]
			, m_modelDesc.vecMaterialDataInfo[nMaterialIndex].v4Emissive[2]
			, m_modelDesc.vecMaterialDataInfo[nMaterialIndex].v4Emissive[3]);
		emissiveValue.SetString(strEmissive.c_str(), doc.GetAllocator());
		subMaterialObj.AddMember(rapidjson::StringRef("Emissibe"), emissiveValue, doc.GetAllocator());

		rapidjson::Value opacityValue(rapidjson::kNumberType);
		opacityValue.SetFloat(m_modelDesc.vecMaterialDataInfo[nMaterialIndex].fOpacity);
		subMaterialObj.AddMember(rapidjson::StringRef("Opacity"), opacityValue, doc.GetAllocator());

		rapidjson::Value shininessValue(rapidjson::kNumberType);
		shininessValue.SetFloat(m_modelDesc.vecMaterialDataInfo[nMaterialIndex].fGlossiness);
		subMaterialObj.AddMember(rapidjson::StringRef("Glossiness"), shininessValue, doc.GetAllocator());

		rapidjson::Value reflectiveValue(rapidjson::kNumberType);
		reflectiveValue.SetFloat(m_modelDesc.vecMaterialDataInfo[nMaterialIndex].fReflective);
		subMaterialObj.AddMember(rapidjson::StringRef("Reflective"), reflectiveValue, doc.GetAllocator());
		
		rapidjson::Value twoSidedValue(rapidjson::kNumberType);
		if (m_modelDesc.vecMaterialDataInfo[nMaterialIndex].bTwoSided)
			twoSidedValue.SetInt(1);
		else
			twoSidedValue.SetInt(0);
		subMaterialObj.AddMember(rapidjson::StringRef("TwoSided"), twoSidedValue, doc.GetAllocator());

		for (int nTexIndex = 0; nTexIndex < HrModelDataInfo::HrMaterialDataInfo::TS_NUMTEXTURESLOTS; ++nTexIndex)
		{
			std::string strTextKey = "Texture_" + std::to_string(nTexIndex);
			rapidjson::Value textureKey(rapidjson::kStringType);
			textureKey.SetString(strTextKey.c_str(), doc.GetAllocator());
			rapidjson::Value textureValue(rapidjson::kStringType);
			
			std::string strTexturePath = m_modelDesc.vecMaterialDataInfo[nMaterialIndex].m_arrTexNames[nTexIndex];
			if (strTexturePath.size() > 0)
			{
				std::string strTexFileName = Hr::HrFileUtils::Instance()->GetFileNameWithSuffix(strTexturePath);
				std::string strTexPath = "Texture\\" + strTexFileName;
				textureValue.SetString(strTexPath.c_str(), doc.GetAllocator());
			}
			else
			{
				textureValue.SetString(rapidjson::StringRef(""), doc.GetAllocator());
			}
			subMaterialObj.AddMember(textureKey, textureValue, doc.GetAllocator());
		}

		materialObj.AddMember(subMaterialKey, subMaterialObj, doc.GetAllocator());
	}

	doc.AddMember(rapidjson::StringRef("Materials"), materialObj, doc.GetAllocator());
}

void HrConvertUtil::FlushDataToFile(const std::string& strOutputFile, rapidjson::Document& doc)
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	std::string strJsonContent = std::string(buffer.GetString());
	strJsonContent = FormatJsonData(strJsonContent);
	
	std::string strRootPath = HrFileUtils::Instance()->GetFilePath(strOutputFile);
	std::string strFileName = HrFileUtils::Instance()->GetFileName(strOutputFile);
	std::string strSuffix = HrFileUtils::Instance()->GetFileSuffix(strOutputFile);
	filesystem::path filePath(strRootPath);
	//filePath = filePath / strFileName;
	//if (!filesystem::exists(filePath))
	//{
	//	filesystem::create_directories(filePath);
	//}
	//auto outputFilePath = filePath / (strFileName + "." + strSuffix);
	std::string strRealOutputFilePath = strOutputFile;//outputFilePath.string();
	HrFileUtils::Instance()->WriteDataToFile(strRealOutputFilePath, strJsonContent);


	auto fileTexturePath = filePath / "Texture\\";
	if (!filesystem::exists(fileTexturePath))
	{
		filesystem::create_directories(fileTexturePath);
	}
	//拷贝图片到Texture文件夹
	for (size_t nMatIndex = 0; nMatIndex < m_modelDesc.vecMaterialDataInfo.size(); ++nMatIndex)
	{
		for (int nTexIndex = 0; nTexIndex < HrModelDataInfo::HrMaterialDataInfo::TS_NUMTEXTURESLOTS; ++nTexIndex)
		{
			if (filesystem::exists(m_modelDesc.vecMaterialDataInfo[nMatIndex].m_arrTexNames[nTexIndex]))
			{
				std::string strFileName = HrFileUtils::Instance()->GetFileNameWithSuffix(m_modelDesc.vecMaterialDataInfo[nMatIndex].m_arrTexNames[nTexIndex]);
				filesystem::path dstFilePath = fileTexturePath / strFileName;
				if (filesystem::exists(dstFilePath))
					filesystem::remove(dstFilePath);
				filesystem::copy_file(m_modelDesc.vecMaterialDataInfo[nMatIndex].m_arrTexNames[nTexIndex], dstFilePath);
			}
		}
	}
}

std::string HrConvertUtil::FormatJsonData(const std::string& strContent)
{
	std::string strRt;
	strRt.reserve(strContent.size() * 2);

	int nCharIndex = 0;
	int nIndentCount = 0;
	while (nCharIndex < strContent.length())
	{
		char c = strContent[nCharIndex];
		if (c == '{' || c == '[')
		{
			strRt.push_back(c);
			strRt.push_back('\n');
			++nIndentCount;
			for (int i = 0; i < nIndentCount; ++i)
			{
				strRt.push_back('\t');
			}
		}
		else if (c == '}' || c == ']')
		{
			strRt.push_back('\n');
			--nIndentCount;
			for (int i = 0; i < nIndentCount; ++i)
			{
				strRt.push_back('\t');
			}
			strRt.push_back(c);
		}
		else if (c == ',')
		{
			// ,",
			if (strContent[nCharIndex + 1] == '"' && strContent[nCharIndex + 2] != ',')
			{
				strRt.push_back(c);
				strRt.push_back('\n');
				for (int i = 0; i < nIndentCount; ++i)
				{
					strRt.push_back('\t');
				}
			}
			else
			{
				strRt.push_back(c);
			}
		}
		else
		{
			strRt.push_back(c);
		}
		++nCharIndex;
	}

	return strRt;
}

HrSceneNodePtr HrConvertUtil::CreateSceneNode()
{
	//BOOST_ASSERT(m_modelDesc.vecSubMeshInfo.size() == m_modelDesc.vecMaterialDataInfo.size());
	if (m_pLoadedMesh)
	{
		HrDirector::Instance()->GetResourceModule()->RemoveResource<HrMesh>(m_pLoadedMesh->GetFilePath());
	}
	m_pLoadedMesh = HrDirector::Instance()->GetResourceModule()->RetriveResource<HrMesh>(m_strOriginalFile, true, false);
	m_pLoadedMesh->Load();

	for (size_t nMeshInfoIndex = 0; nMeshInfoIndex < m_modelDesc.vecSubMeshInfo.size(); ++nMeshInfoIndex)
	{
		HrModelDataInfo::HrSubMeshDataInfo& subMeshInfo = m_modelDesc.vecSubMeshInfo[nMeshInfoIndex];

		std::vector<HrVertexElement> vecVertexElement;
		MakeVertexElements(subMeshInfo, vecVertexElement);

		//Vertex Buffer
		HrStreamData streamVertexBuffer;
		MakeVertexStream(nMeshInfoIndex, streamVertexBuffer, vecVertexElement);

		HrSubMeshPtr pSubMesh = m_pLoadedMesh->AddSubMesh(subMeshInfo.strMeshName);
		pSubMesh->GetRenderLayout()->BindVertexBuffer(streamVertexBuffer.GetBufferPoint(), streamVertexBuffer.GetBufferSize(), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, vecVertexElement);

		//Index Buffer
		HrStreamData streamIndexBuffer;
		MakeIndexStream(nMeshInfoIndex, streamIndexBuffer);
		pSubMesh->GetRenderLayout()->BindIndexBuffer(streamIndexBuffer.GetBufferPoint(), streamIndexBuffer.GetBufferSize(), HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE, IT_32BIT);

		//Material
		int nMaterialDataIndex = nMeshInfoIndex;
		if (nMaterialDataIndex >= m_modelDesc.vecMaterialDataInfo.size())
			nMaterialDataIndex = 0;

		HrModelDataInfo::HrMaterialDataInfo& materialInfo = m_modelDesc.vecMaterialDataInfo[nMaterialDataIndex];
		//CheckTexture
		for (size_t nTexIndex = 0; nTexIndex < materialInfo.m_arrTexNames.size(); ++nTexIndex)
		{
			std::string strTexture = materialInfo.m_arrTexNames[nTexIndex];
			if (strTexture.size() > 0)
			{
				std::string strTextureFileName = HrFileUtils::Instance()->GetFileNameWithSuffix(strTexture);
				filesystem::path filePath(m_strOriginalPath);
				filePath /= strTextureFileName;
				//BOOST_ASSERT(filesystem::exists(filePath));

				materialInfo.m_arrTexNames[nTexIndex] = filePath.string();
			}
		}

		pSubMesh->SetMeshAABB(subMeshInfo.aabb);

		HrMaterialPtr pMaterial = HrDirector::Instance()->GetResourceModule()->MakeMaterial(materialInfo.strMaterialName, materialInfo);
		pSubMesh->SetMaterial(pMaterial);
	}

	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
	pSceneNode->SetName(m_strOriginalFile);

	for (size_t i = 0; i < m_pLoadedMesh->GetSubMeshNum(); ++i)
	{
		HrSceneNodePtr pNode = HrMakeSharedPtr<HrSceneNode>(m_pLoadedMesh->GetSubMesh(i)->GetName());
		HrSceneObjectPtr pSubRenderObj = pNode->GetSceneObject();
		HrRenderableComponentPtr pRenderableCom = pSubRenderObj->AddComponent<HrRenderableComponent>();
		HrRenderablePtr pRenderable = HrMakeSharedPtr<HrStaticMeshRenderable>(m_pLoadedMesh->GetSubMesh(i));
		pRenderableCom->SetRenderable(pRenderable);
		pRenderable->SetRenderEffect(HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>());

		pSceneNode->AddChild(pNode);
	}

	m_pSceneNode = pSceneNode;

	return pSceneNode;
}

void HrConvertUtil::MoveTextures()
{
	//for (size_t nMatIndex = 0; nMatIndex < m_modelDesc.vecMaterialDataInfo.size(); ++nMatIndex)
	//{
	//	HrModelDataInfo::HrMaterialDataInfo& materialInfo = m_modelDesc.vecMaterialDataInfo[nMatIndex];
	//	for (size_t nTexIndex = 0; nTexIndex < materialInfo.m_arrTexNames.size(); ++nTexIndex)
	//	{
	//		std::string strTexture = materialInfo.m_arrTexNames[nTexIndex];
	//		std::string strTextureFileName = HrFileUtils::Instance()->GetFileName(strTexture);
	//		filesystem::path filePath(m_strOriginalPath);
	//		filePath /= strTextureFileName;
	//		BOOST_ASSERT(filesystem::exists(filePath));


	//	}
	//}
}

void HrConvertUtil::MakeVertexElements(const HrModelDataInfo::HrSubMeshDataInfo& subMeshInfo, std::vector<HrVertexElement>& vecVertexElement)
{
	vecVertexElement.push_back(HrVertexElement(VEU_POSITION, VET_FLOAT3));
	if (subMeshInfo.vecTangent.size() > 0)
		vecVertexElement.push_back(HrVertexElement(VEU_TANGENT, VET_FLOAT3));
	if (subMeshInfo.vecBinormal.size() > 0)
		vecVertexElement.push_back(HrVertexElement(VEU_BINORMAL, VET_FLOAT3));
	if (subMeshInfo.vecNormal.size() > 0)
		vecVertexElement.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));
	if (subMeshInfo.vecUV.size() > 0)
		vecVertexElement.push_back(HrVertexElement(VEU_TEXTURE_COORDINATES, VET_FLOAT2));

}

void HrConvertUtil::MakeVertexStream(int nSubMeshIndex, HrStreamData& streamData, const std::vector<HrVertexElement>& vecVertexElement)
{
	Vector3 v3Zero = Vector3::Zero();

	const HrModelDataInfo::HrSubMeshDataInfo& subMeshInfo = m_modelDesc.vecSubMeshInfo[nSubMeshIndex];

	for (int nVertexIndex = 0; nVertexIndex < subMeshInfo.vecVertexPos.size(); ++nVertexIndex)
	{
		for (size_t nEleIndex = 0; nEleIndex < vecVertexElement.size(); ++nEleIndex)
		{
			switch (vecVertexElement[nEleIndex].m_elementSemantic)
			{
			case VEU_POSITION:
			{
				streamData.AddBuffer((Byte*)(&subMeshInfo.vecVertexPos[nVertexIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			case VEU_TANGENT:
			{
				streamData.AddBuffer((Byte*)(&subMeshInfo.vecTangent[nVertexIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			case VEU_BINORMAL:
			{
				streamData.AddBuffer((Byte*)(&subMeshInfo.vecBinormal[nVertexIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			case VEU_NORMAL:
			{
				streamData.AddBuffer((Byte*)(&subMeshInfo.vecNormal[nVertexIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			case VEU_TEXTURE_COORDINATES:
			{
				streamData.AddBuffer((Byte*)(&subMeshInfo.vecUV[nVertexIndex][0]), vecVertexElement[nEleIndex].GetTypeSize());
				break;
			}
			}
		}
	}
}

void HrConvertUtil::MakeIndexStream(int nSubMeshIndex, HrStreamData& indexData)
{
	const HrModelDataInfo::HrSubMeshDataInfo& subMeshInfo = m_modelDesc.vecSubMeshInfo[nSubMeshIndex];
	if (subMeshInfo.vecIndices.size() > 0)
	{
		indexData.AddBuffer((Byte*)(&subMeshInfo.vecIndices[0]), subMeshInfo.vecIndices.size() * sizeof(subMeshInfo.vecIndices[0]));
	}
}

float4 HrConvertUtil::Color4ToFloat4(aiColor4D const& c)
{
	float4 v;
	v.x() = c.r;
	v.y() = c.g;
	v.z() = c.b;
	v.w() = c.a;
	return v;
}

float3 HrConvertUtil::Color4ToFloat3(aiColor4D const & c)
{
	float3 v;
	v.x() = c.r;
	v.y() = c.g;
	v.z() = c.b;
	return v;
}

const HrModelDataInfo& HrConvertUtil::GetModelDataInfo()
{
	return m_modelDesc;
}

void HrConvertUtil::ChangeMaterial(int nMeshIndex, const std::string& strMaterialName)
{
	if (strMaterialName == "Standard")
	{
		if (nMeshIndex < m_modelDesc.vecSubMeshInfo.size())
		{
			m_modelDesc.vecMaterialDataInfo[nMeshIndex].strMaterialName = "Standard_" + m_modelDesc.vecSubMeshInfo[nMeshIndex].strMeshName;
			m_modelDesc.vecMaterialDataInfo[nMeshIndex].v4Albedo = float4(0.4f, 0.4f, 0.4f, 1.0f);
			m_modelDesc.vecMaterialDataInfo[nMeshIndex].v4Emissive = float4(0, 0, 0, 0);

			m_modelDesc.vecMaterialDataInfo[nMeshIndex].fOpacity = 1.0f;
			m_modelDesc.vecMaterialDataInfo[nMeshIndex].fShininess = 1;
			m_modelDesc.vecMaterialDataInfo[nMeshIndex].fGlossiness = 2.0f;
			m_modelDesc.vecMaterialDataInfo[nMeshIndex].fReflective = 0.1f;
			m_modelDesc.vecMaterialDataInfo[nMeshIndex].bTwoSided = false;

			m_modelDesc.vecMaterialDataInfo[nMeshIndex].m_arrTexNames.assign("");

			HrMaterialPtr pMaterial = HrDirector::Instance()->GetResourceModule()->MakeMaterial(m_modelDesc.vecMaterialDataInfo[nMeshIndex].strMaterialName, m_modelDesc.vecMaterialDataInfo[nMeshIndex]);
			if (m_pSceneNode)
			{
				for (int i = 0; i < m_pSceneNode->GetChildrenCount(); ++i)
				{
					auto& pChildNode = m_pSceneNode->GetChildByIndex(i);
					if (pChildNode->GetName() == m_modelDesc.vecSubMeshInfo[nMeshIndex].strMeshName)
					{
						pChildNode->GetSceneObject()->GetComponent<HrRenderableComponent>()->GetRenderable()->GetSubMesh()->SetMaterial(pMaterial);
					}
				}
			}
		}
	}
}

void HrConvertUtil::SetMaterialGlossiness(int nMeshIndex, float fGlo)
{
	if (nMeshIndex < m_modelDesc.vecSubMeshInfo.size())
	{
		//HrMaterialPtr pMaterial = HrDirector::Instance()->GetResourceModule()->MakeMaterial(m_modelDesc.vecMaterialDataInfo[nMeshIndex].strMaterialName, m_modelDesc.vecMaterialDataInfo[nMeshIndex]);
		if (m_pSceneNode)
		{
			for (int i = 0; i < m_pSceneNode->GetChildrenCount(); ++i)
			{
				auto& pChildNode = m_pSceneNode->GetChildByIndex(i);
				if (pChildNode->GetName() == m_modelDesc.vecSubMeshInfo[nMeshIndex].strMeshName)
				{
					auto pMaterial = pChildNode->GetSceneObject()->GetComponent<HrRenderableComponent>()->GetRenderable()->GetSubMesh()->GetMaterial();
					pMaterial->SetGlossiness(fGlo);
				}
			}
		}
		m_modelDesc.vecMaterialDataInfo[nMeshIndex].fGlossiness = fGlo;
	}
}

void HrConvertUtil::SetMaterialReflective(int nMeshIndex, float fReflective)
{
	if (nMeshIndex < m_modelDesc.vecSubMeshInfo.size())
	{
		//HrMaterialPtr pMaterial = HrDirector::Instance()->GetResourceModule()->MakeMaterial(m_modelDesc.vecMaterialDataInfo[nMeshIndex].strMaterialName, m_modelDesc.vecMaterialDataInfo[nMeshIndex]);
		if (m_pSceneNode)
		{
			for (int i = 0; i < m_pSceneNode->GetChildrenCount(); ++i)
			{
				auto& pChildNode = m_pSceneNode->GetChildByIndex(i);
				if (pChildNode->GetName() == m_modelDesc.vecSubMeshInfo[nMeshIndex].strMeshName)
				{
					auto pMaterial = pChildNode->GetSceneObject()->GetComponent<HrRenderableComponent>()->GetRenderable()->GetSubMesh()->GetMaterial();
					pMaterial->SetReflective(fReflective);
				}
			}
		}
		m_modelDesc.vecMaterialDataInfo[nMeshIndex].fReflective = fReflective;
	}
}

void HrConvertUtil::SetMaterialTexture(int nMeshIndex, int nTexIndex, const std::string& strTextureName)
{
	if (nMeshIndex < m_modelDesc.vecSubMeshInfo.size())
	{
		//HrMaterialPtr pMaterial = HrDirector::Instance()->GetResourceModule()->MakeMaterial(m_modelDesc.vecMaterialDataInfo[nMeshIndex].strMaterialName, m_modelDesc.vecMaterialDataInfo[nMeshIndex]);
		if (m_pSceneNode)
		{
			for (int i = 0; i < m_pSceneNode->GetChildrenCount(); ++i)
			{
				auto& pChildNode = m_pSceneNode->GetChildByIndex(i);
				if (pChildNode->GetName() == m_modelDesc.vecSubMeshInfo[nMeshIndex].strMeshName)
				{
					auto pMaterial = pChildNode->GetSceneObject()->GetComponent<HrRenderableComponent>()->GetRenderable()->GetSubMesh()->GetMaterial();
					auto pTexture = HrDirector::Instance()->GetResourceModule()->RetriveTexture(strTextureName, HrTexture::TEX_TYPE_2D);
					pMaterial->SetTexture((HrMaterial::EnumMaterialTexSlot)nTexIndex, pTexture);
				}
			}
		}
		m_modelDesc.vecMaterialDataInfo[nMeshIndex].m_arrTexNames[nTexIndex] = strTextureName;
	}
}

void HrConvertUtil::RecursiveTransformMesh(const float4x4& matParent, const aiNode* pNode, std::vector<HrModelDataInfo::HrSubMeshDataInfo>& vecMeshes)
{
	const auto matTrans = HrMath::Transpose(float4x4(&pNode->mTransformation.a1)) * matParent;
	const auto quatTrans = HrMath::ToQuaternion(matTrans);

	for (uint32 nMeshIndex = 0; nMeshIndex < pNode->mNumMeshes; ++nMeshIndex)
	{
		auto& mesh = vecMeshes[pNode->mMeshes[nMeshIndex]];

		for (size_t nVertexIndex = 0; nVertexIndex < mesh.vecVertexPos.size(); ++nVertexIndex)
		{
			Vector3 vPos = HrMath::TransformCoord(mesh.vecVertexPos[nVertexIndex], matTrans) * m_fUnitScale;
			mesh.vecVertexPos[nVertexIndex].swap(vPos);
			Vector3 vNormal = HrMath::TransformNormal(mesh.vecNormal[nVertexIndex], matTrans);
			mesh.vecNormal[nVertexIndex].swap(vNormal);
		}
	}

	for (uint32 nChildIndex = 0; nChildIndex < pNode->mNumChildren; ++nChildIndex)
	{
		RecursiveTransformMesh(matTrans, pNode->mChildren[nChildIndex], vecMeshes);
	}
}

void HrConvertUtil::SetUnitScale(float fUnitScale)
{
	m_fUnitScale = fUnitScale;
}

