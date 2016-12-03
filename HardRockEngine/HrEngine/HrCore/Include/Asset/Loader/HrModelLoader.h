#ifndef _HR_MODELLOADER_H_
#define _HR_MODELLOADER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrModelDescInfo
	{
	public:
		std::string m_strMeshName;
		std::vector<Vector3> m_vecPrimaryPos;
		std::vector<Vector3> m_vecVertexPos;
		std::vector<uint32> m_vecIndice;
		std::vector<Vector3> m_vecNormal;
		std::vector<float4> m_vecColor;
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

		HrMesh* GetMesh() { return m_pMesh; }
	public:
		void Load(std::string& strFile);

		
	private:
		void FillEmptyModelInfo();
		void MakeVertexStream(HrStreamData& streamData, const std::vector<HrVertexElement>& vecVertexElement);

	protected:
		HrMesh* m_pMesh;

		HrModelDescInfo m_modelDesc;

	};
}

#endif



