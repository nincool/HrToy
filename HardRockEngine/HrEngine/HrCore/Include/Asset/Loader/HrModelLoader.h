#ifndef _HR_MODELLOADER_H_
#define _HR_MODELLOADER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	/*
	@brief	����ʱŪ����һ��Vertex�ṹ������������˵ [11/11/2016 By Hr]
	*/
	class Vertex
	{
	public:
		Vertex(float3 p, float4 c)
		{
			position = p;
			color = c;
		}
		float3 position;
		float4 color;
	};

	class HrModelLoader
	{
	public:
		HrModelLoader();
		virtual ~HrModelLoader();

	public:
		void Load(std::string& strFile);

		
	public:
		HrMesh* m_pMesh;

		std::string m_strMeshName;
		std::vector<Vertex> m_vecVertexBuffer;
		std::vector<uint32> m_vecIndexBuffer;

	};
}

#endif



