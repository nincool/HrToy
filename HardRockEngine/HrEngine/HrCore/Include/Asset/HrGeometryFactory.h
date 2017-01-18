#ifndef _HR_GEOMETRYFACTORY_H_
#define _HR_GEOMETRYFACTORY_H_

#include "HrCore/Include/Render/HrStaticMeshRenderable.h"
#include "HrCore/Include/Render/HrSkinnedMeshRenderable.h"

namespace Hr
{
	class HrGeometryPlane : public HrStaticMeshRenderable
	{
	public:
		struct Vertex
		{
			float3 position;
			float3 normal;
			float2 uv;
		};

		HrGeometryPlane();
		~HrGeometryPlane();

	private:
		void GetBuildInPlaneMesh();
		void CreateBoxStaticMesh(HrMesh* pMesh);

	};

	class HrGeometryBox : public HrStaticMeshRenderable
	{
	public:
		struct Vertex
		{
			float3 position;
			float3 normal;
			float2 uv;
		};

		HrGeometryBox();
		~HrGeometryBox();

	private:
		void GetBuildInBoxMesh();
		void CreateBoxStaticMesh(HrMesh* pMesh);

		void ComputeNormal(Vertex* pVertex, size_t nVertexNum, uint16* pIndex, size_t nIndexNum);
	};



	class HrGeometryFactory
	{
	public:
		HrGeometryFactory();
		~HrGeometryFactory();

		HrSceneNode* CreateBox(uint32 nLength, uint32 nWidth, uint32 nHeight);

		
	};
}


#endif


