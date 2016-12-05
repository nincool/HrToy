#ifndef _HR_MODELLOADER_H_
#define _HR_MODELLOADER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrModelDescInfo
	{
	public:
		struct HrMaterialInfo
		{
			HrMaterialInfo()
				: strMaterialName("")
				, v3Emissive(Vector3::Zero())
				, v3Ambient(Vector3::Zero())
				, v3Diffuse(Vector3::Zero())
				, v3Specular(Vector3::Zero())
				, fOpacity(1.0f)
				, fShininess(1.0f)
				, fReflectivity(1.0f)
			{}
			std::string strMaterialName;
			Vector3 v3Emissive;
			Vector3 v3Ambient;
			Vector3 v3Diffuse;
			Vector3 v3Specular;
			float fOpacity;
			float fShininess;
			float fReflectivity;
		};

		struct HrMeshInfo
		{
			std::string strMeshName;
			std::vector<Vector3> m_vecPrimaryPos;
			std::vector<Vector3> m_vecVertexPos;
			std::vector<uint16> m_vecIndice;
			std::vector<Vector3> m_vecNormal;
			std::vector<float4> m_vecColor;

			std::vector<HrMaterialInfo> m_vecMaterialInfo;
			std::vector< std::vector<uint32> > m_vecMaterialConnectInfo;
		};
	public:
		std::vector<HrMeshInfo> m_vecMeshInfo;
	};

	class HrModelLoader
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

		HrMesh* GetMesh() { return m_vecMesh[0]; }
	public:
		void Load(std::string& strFile);

	private:
		void FillEmptyModelInfo(HrModelDescInfo::HrMeshInfo& meshInfo);
		void MakeMaterialResource(HrModelDescInfo::HrMeshInfo& meshInfo);
		void MakeVertexStream(HrModelDescInfo::HrMeshInfo& meshInfo, HrStreamData& streamData, const std::vector<HrVertexElement>& vecVertexElement);
		void ConnectMaterial();

		void CalculateAverageNormals(HrModelDescInfo::HrMeshInfo& meshInfo);
	protected:
		std::string m_strFileName;
		std::vector<HrMesh*> m_vecMesh;
		std::vector<HrMaterial*> m_vecMaterial;

		HrModelDescInfo m_modelDesc;

	};
}

#endif



