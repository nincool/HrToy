#ifndef _HR_GEOMETRYFACTORY_H_
#define _HR_GEOMETRYFACTORY_H_

#include "HrCore/Include/Render/HrStaticMeshRenderable.h"

namespace Hr
{
	class HrGeometryBox : public HrStaticMeshRenderable
	{
	public:
		HrGeometryBox();
		~HrGeometryBox();

	private:
		void GetBuildInBoxMesh();
		void CreateBoxStaticMesh(HrMesh* pMesh);
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


