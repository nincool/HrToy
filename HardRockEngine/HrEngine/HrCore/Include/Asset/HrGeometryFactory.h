#ifndef _HR_GEOMETRYFACTORY_H_
#define _HR_GEOMETRYFACTORY_H_

#include "HrCore/Include/Render/HrStaticMeshRenderable.h"

namespace Hr
{
	class HrGeometryBox : public HrStaticMeshRenderable
	{
	public:
		struct Vertex
		{
			float3 position;
			float3 normal;
		};

		HrGeometryBox();
		~HrGeometryBox();

	private:
		void GetBuildInBoxMesh();
		void CreateBoxStaticMesh(HrMesh* pMesh);

		void ComputeNormal(Vertex* pVertex, uint16* pIndex, size_t nSize);
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


