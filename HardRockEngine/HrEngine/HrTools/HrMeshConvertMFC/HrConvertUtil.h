#pragma once

#include "HrEngine.h"
#include <string>
#include <vector>
#include "ThirdParty/rapidjson/include/rapidjson/document.h"
#include "ThirdParty/rapidjson/include/rapidjson/writer.h"
#include "ThirdParty/rapidjson/include/rapidjson/stringbuffer.h"
#include "ThirdParty/assimp/include/assimp/color4.h"

class aiScene;
class aiNode;

namespace Hr
{
	class HrConvertUtil
	{
	public:
		HrConvertUtil();
		~HrConvertUtil();

		bool LoadOriginalData(std::string const & in_name);

		bool WriteModelDataToFile(const std::string& strOutPath);

		HrSceneNodePtr CreateSceneNode();

		const HrModelDataInfo& GetModelDataInfo();

		void ChangeMaterial(int nMeshIndex, const std::string& strMaterialName);
		void SetMaterialGlossiness(int nMeshIndex, float fGlo);
		void SetMaterialReflective(int nMeshIndex, float fReflective);
		void SetMaterialTexture(int nMeshIndex, int nTexIndex, const std::string& strTextureName);
		void SetUnitScale(float fUnitScale);
	private:
		void BuildMeshData(const aiScene* pAssimpScene);
		void BuildMaterialData(const aiScene* pAssimpScene);

		void RecursiveTransformMesh(const float4x4& matParent, const aiNode* pNode, std::vector<HrModelDataInfo::HrSubMeshDataInfo>& vecMeshes);

		void CombineMesh();

		void WriteMeshData(rapidjson::Document& doc);
		void WriteMaterialData(rapidjson::Document& doc);
		
		void FlushDataToFile(const std::string& strOutputFile, rapidjson::Document& doc);

		std::string FormatJsonData(const std::string& strContent);

		std::string MakeFloat3String(float3 v);
		std::string MakeFloat3StringWithEndMark(float3 v, const char c= '|');

		void ComputeAABB();
		void ComputeExtrameDistanceAlongDir(const Vector3& vDir, const std::vector<Vector3>& vecVertices, uint32& nMax, uint32& nMin);
	private:
		void MakeVertexElements(const HrModelDataInfo::HrSubMeshDataInfo& subMeshInfo, std::vector<HrVertexElement>& vecVertexElement);
		void MakeVertexStream(int nSubMeshIndex, HrStreamData& streamData, const std::vector<HrVertexElement>& vecVertexElement);
		void MakeIndexStream(int nSubMeshIndex, HrStreamData& indexData);

		void MoveTextures();

		float4 Color4ToFloat4(aiColor4D const& c);
		float3 Color4ToFloat3(aiColor4D const & c);
	private:
		std::string m_strOriginalFile;
		std::string m_strOriginalPath;

		bool m_bLoadSuccess;
		HrModelDataInfo m_modelDesc;

		HrMeshPtr m_pLoadedMesh;
		HrSceneNodePtr m_pSceneNode;

		float m_fUnitScale;
		float m_fOutputUnitScale;
	};
}















