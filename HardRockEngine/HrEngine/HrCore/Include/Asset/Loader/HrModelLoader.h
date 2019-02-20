#ifndef _HR_MODELLOADER_H_
#define _HR_MODELLOADER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrModelDataInfo
	{
	public:
		struct HrMaterialDataInfo
		{
			enum EnumTextureSlot
			{
				TS_ALBEDO,
				TS_METALNESS,
				TS_NORMALMAP,

				TS_NUMTEXTURESLOTS,
			};

			HrMaterialDataInfo()
				: strMaterialName("")
				, nMaterialIndex(0)
				, v4Albedo(Vector4::Zero())
				, v4Emissive(Vector4::Zero())
				, fMetalness(1.0f)
				, fRoughness(0.3f)
				, fOpacity(1.0f)
				, bTwoSided(false)
			{}
			int nMaterialIndex;
			std::string strMaterialName;
			
			Vector4 v4Albedo;
			Vector4 v4Emissive;

			float fMetalness;
			float fRoughness;

			float fOpacity;

			bool bTwoSided;

			std::array<std::string, TS_NUMTEXTURESLOTS> m_arrTexNames;
		};

		struct HrSubMeshDataInfo
		{
			std::string strMeshName;
			bool bAllIndices;
			bool bIndexDataType16bit;
			int nTriangleCount;

			std::vector<uint32> vecIndices;
			std::vector<Vector3> vecVertexPos;
			std::vector<Vector3> vecTangent;
			std::vector<Vector3> vecBinormal;
			std::vector<Vector3> vecNormal;
			std::vector<float4> vecColor;
			std::vector<float2> vecUV;

			AABBox aabb;
		};

	public:
		std::vector<HrSubMeshDataInfo> vecSubMeshInfo;
		std::vector<HrMaterialDataInfo> vecMaterialDataInfo;

		std::string strFilePath;
		std::string strFileName;
	};

	class HR_CORE_API HrModelLoader
	{
	public:
		enum EnumModelTopologyVertexCount
		{
			MTVC_POINT = 1,
			MTVC_LINE = 2,
			MTVC_TRIANGLE = 3,
		};

		HrModelLoader();
		virtual ~HrModelLoader();

		HrMeshPtr GetMesh() { return m_pMesh; }

		const HrModelDataInfo& GetModelDataInfo();
	public:
		void Load(std::string& strFile);

	private:
		void MakeVertexElements(const HrModelDataInfo::HrSubMeshDataInfo& subMeshInfo, std::vector<HrVertexElement>& vecVertexElement);
		void MakeVertexStream(int nSubMeshIndex, HrStreamData& streamData, const std::vector<HrVertexElement>& vecVertexElement);
		void MakeIndexStream(int nSubMeshIndex, HrStreamData& indexData);
	protected:
		std::string m_strFileName;
		HrMeshPtr m_pMesh;

		HrModelDataInfo m_modelDesc;

	};
}

#endif



