#ifndef _HR_MODELLOADER_H_
#define _HR_MODELLOADER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
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

	public:
		void Load(std::string& strFile);

		
	public:
		HrMesh* m_pMesh;

		std::string m_strMeshName;
		std::vector<Vector3> m_vecPrimaryPos;
		std::vector<Vector3> m_vecVertexPos;
		std::vector<uint32> m_vecIndice;
		std::vector<Vector3> m_vecNormal;

	};
}

#endif



