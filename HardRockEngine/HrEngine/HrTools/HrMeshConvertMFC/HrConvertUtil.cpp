#include "stdafx.h"
#include "HrConvertUtil.h"
#include "HrUtilTools/Include/HrStringUtil.h"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <iostream>
#include <fstream>

using namespace Hr;
using namespace std::experimental;

HrConvertUtil::HrConvertUtil()
{
	m_bLoadSuccess = false;
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

	m_modelDesc.strFileName = Hr::HrFileUtils::Instance()->GetFileName(in_name);

	BuildMeshData(scene);
	BuildMaterialData(scene);
	
	aiReleaseImport(scene);

	return true;
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
		bool transparent = false;
		bool two_sided = false;

		aiString aiName;
		aiColor4D aiAlbedo;
		aiColor4D aiEmissive;
		float aiOpacity;
		float aiShininess;
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
		}
		shininess = HrMath::Clamp(shininess, 1.0f, HrMath::MAX_SHININESS);
		materialDataInfo.fShininess = shininess;
		materialDataInfo.fGlossiness = HrMath::Shininess2Glossiness(shininess);

		if ((opacity < 1) || (aiGetMaterialTextureCount(pMaterial, aiTextureType_OPACITY) > 0))
		{
			transparent = true;
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
				Vector3 vecPos = subMeshInfo.vecVertexPos[nVerticeIndex];

				char cTemp[50];
				std::sprintf(cTemp, "%.2f", vecPos[0]);
				strVertices += cTemp;
				strVertices += ",";
				std::sprintf(cTemp, "%.2f", vecPos[1]);
				strVertices += cTemp;
				strVertices += ",";
				std::sprintf(cTemp, "%.2f", vecPos[2]);
				strVertices += cTemp;
				strVertices += "|";
			}
			rapidjson::Value verticesValueObj(rapidjson::kStringType);
			verticesValueObj.SetString(strVertices.c_str(), doc.GetAllocator());
			subMeshValueObj.AddMember(rapidjson::StringRef("Vertices"), verticesValueObj, doc.GetAllocator());
		}

		{
			std::string strNormals;
			for (int nNormalIndex = 0; nNormalIndex < subMeshInfo.vecNormal.size(); ++nNormalIndex)
			{
				Vector3 vecPos = subMeshInfo.vecNormal[nNormalIndex];
				char cTemp[50];
				std::sprintf(cTemp, "%.2f", vecPos[0]);
				strNormals += cTemp;
				strNormals += ",";
				std::sprintf(cTemp, "%.2f", vecPos[1]);
				strNormals += cTemp;
				strNormals += ",";
				std::sprintf(cTemp, "%.2f", vecPos[2]);
				strNormals += cTemp;
				strNormals += "|";
			}
			rapidjson::Value normalsValueObj(rapidjson::kStringType);
			normalsValueObj.SetString(strNormals.c_str(), doc.GetAllocator());
			subMeshValueObj.AddMember(rapidjson::StringRef("Normals"), normalsValueObj, doc.GetAllocator());
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
		shininessValue.SetFloat(m_modelDesc.vecMaterialDataInfo[nMaterialIndex].fShininess);
		subMaterialObj.AddMember(rapidjson::StringRef("Shininess"), shininessValue, doc.GetAllocator());
		
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
			textureValue.SetString(m_modelDesc.vecMaterialDataInfo[nMaterialIndex].m_arrTexNames[nTexIndex].c_str(), doc.GetAllocator());
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
	//strJsonContent = HrStringUtil::ReplaceAllDistinct(strJsonContent, "{", "{\r\n");

	HrFileUtils::Instance()->WriteDataToFile(strOutputFile, strJsonContent);
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
	BOOST_ASSERT(m_modelDesc.vecSubMeshInfo.size() == m_modelDesc.vecMaterialDataInfo.size());
	m_pLoadedMesh = HrDirector::Instance()->GetResourceComponent()->RetriveResource<HrMesh>(m_strOriginalFile, true, false);

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
		HrModelDataInfo::HrMaterialDataInfo& materialInfo = m_modelDesc.vecMaterialDataInfo[nMeshInfoIndex];
		//CheckTexture
		for (size_t nTexIndex = 0; nTexIndex < materialInfo.m_arrTexNames.size(); ++nTexIndex)
		{
			std::string strTexture = materialInfo.m_arrTexNames[nTexIndex];
			if (strTexture.size() > 0)
			{
				std::string strTextureFileName = HrFileUtils::Instance()->GetFileNameWithSuffix(strTexture);
				filesystem::path filePath(m_strOriginalPath);
				filePath /= strTextureFileName;
				BOOST_ASSERT(filesystem::exists(filePath));

				materialInfo.m_arrTexNames[nTexIndex] = filePath.string();
			}
		}

		HrMaterialPtr pMaterial = HrDirector::Instance()->GetResourceComponent()->MakeMaterial(materialInfo.strMaterialName, materialInfo);
		pSubMesh->SetMaterial(pMaterial);
	}

	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>();
	HrSceneObjectPtr pSceneObj = HrMakeSharedPtr<HrSceneObject>();
	pSceneNode->SetSceneObject(pSceneObj);
	pSceneNode->SetName(m_strOriginalFile);

	for (size_t i = 0; i < m_pLoadedMesh->GetSubMeshNum(); ++i)
	{
		HrSceneObjectPtr pSubRenderObj = HrMakeSharedPtr<HrSceneObject>();
		HrRenderableComponentPtr pRenderableCom = pSubRenderObj->AddComponent<HrRenderableComponent>();
		HrRenderablePtr pRenderable = HrMakeSharedPtr<HrStaticMeshRenderable>();
		pRenderableCom->SetRenderable(pRenderable);
		pRenderable->SetSubMesh(m_pLoadedMesh->GetSubMesh(i));
		pRenderable->SetRenderEffect(HrDirector::Instance()->GetResourceComponent()->RetriveResource<HrRenderEffect>());

		HrSceneNodePtr pNode = HrMakeSharedPtr<HrSceneNode>(m_pLoadedMesh->GetSubMesh(i)->GetName());
		pNode->SetSceneObject(pSubRenderObj);
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
	//if (m_modelDesc.vecTangent.size() > 0)
	//	vecVertexElement.push_back(HrVertexElement(VEU_TANGENT, VET_FLOAT3));
	//if (m_modelDesc.vecBinormal.size() > 0)
	//	vecVertexElement.push_back(HrVertexElement(VEU_BINORMAL, VET_FLOAT3));
	if (subMeshInfo.vecNormal.size() > 0)
		vecVertexElement.push_back(HrVertexElement(VEU_NORMAL, VET_FLOAT3));
	//if (m_modelDesc.vecUV.size() > 0)
	//	vecVertexElement.push_back(HrVertexElement(VEU_TEXTURE_COORDINATES, VET_FLOAT2));

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
				break;
			}
			case VEU_BINORMAL:
			{
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
			m_modelDesc.vecMaterialDataInfo[nMeshIndex].fShininess = HrMath::Glossiness2Shininess(5.0f);
			m_modelDesc.vecMaterialDataInfo[nMeshIndex].fGlossiness = 10.0f;
			m_modelDesc.vecMaterialDataInfo[nMeshIndex].bTwoSided = false;

			m_modelDesc.vecMaterialDataInfo[nMeshIndex].m_arrTexNames.assign("");

			HrMaterialPtr pMaterial = HrDirector::Instance()->GetResourceComponent()->MakeMaterial(m_modelDesc.vecMaterialDataInfo[nMeshIndex].strMaterialName, m_modelDesc.vecMaterialDataInfo[nMeshIndex]);
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
		//HrMaterialPtr pMaterial = HrDirector::Instance()->GetResourceComponent()->MakeMaterial(m_modelDesc.vecMaterialDataInfo[nMeshIndex].strMaterialName, m_modelDesc.vecMaterialDataInfo[nMeshIndex]);
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

void HrConvertUtil::SetMaterialTexture(int nMeshIndex, int nTexIndex, const std::string& strTextureName)
{

}

