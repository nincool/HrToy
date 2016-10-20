#ifndef _HR_GEOMETRYFACTORY_H_
#define _HR_GEOMETRYFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrGeometryFactory
	{
	public:
		HrGeometryFactory();
		~HrGeometryFactory();

		HrSceneNode* Create2DTriangle();
		HrSceneNode* CreateBox(uint32 nLength, uint32 nWidth, uint32 nHeight);
	};
}


#endif


