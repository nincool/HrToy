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
				, nMaterialIndex(0)
				, v4Emissive(Vector4::Zero())
				, v4Ambient(Vector4::Zero())
				, v4Diffuse(Vector4::Zero())
				, v4Specular(Vector4::Zero())
				, fOpacity(1.0f)
				, fShininess(1.0f)
				, fReflectivity(1.0f)
			{}
			int nMaterialIndex;
			std::string strMaterialName;
			Vector4 v4Emissive;
			Vector4 v4Ambient;
			Vector4 v4Diffuse;
			Vector4 v4Specular;
			float fOpacity;
			float fShininess;
			float fReflectivity;
		};

		struct HrSubMeshInfo
		{
			std::string strMeshName;

			std::vector<uint32> vecIndices;
			std::vector<Vector3> vecVertexPos;
			std::vector<Vector3> vecNormal;
			std::vector<float4> vecColor;
			std::vector<float2> vecUV;

			HrMaterialInfo materialInfo;
			std::vector<std::string> vecTextureFileName;
		};

	public:

		std::vector<HrSubMeshInfo> vecSubMeshInfo;
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

		HrMeshPtr GetMesh() { return m_pMesh; }
	public:
		void Load(std::string& strFile);

	private:
		void FillEmptyModelInfo();
		HrMaterial* MakeMaterialResource(HrModelDescInfo::HrMaterialInfo& materialInfo);
		std::vector<HrTexture*> MakeTextureResource(std::vector<std::string>& vecTextureFile);
		void MakeVertexStream(HrModelDescInfo::HrSubMeshInfo& subMeshInfo, HrStreamData& streamData, const std::vector<HrVertexElement>& vecVertexElement);

	protected:
		std::string m_strFileName;
		HrMeshPtr m_pMesh;

		HrModelDescInfo m_modelDesc;

	};
}

#endif



