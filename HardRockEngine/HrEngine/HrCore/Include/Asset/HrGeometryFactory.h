#ifndef _HR_GEOMETRYFACTORY_H_
#define _HR_GEOMETRYFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrGeometryFactory
	{
	public:
		HrGeometryFactory();
		~HrGeometryFactory();

		static HrGeometryFactory& GetInstance();
		
		//·ÀÖ¹log´òÓ¡ÄÚ´æÐ¹Â¶
		static void ReleaseInstance();

		HrSceneNode* Create2DTriangle();
		HrSceneNode* CreateBox(uint32 nLength, uint32 nWidth, uint32 nHeight);
	private:
		static HrGeometryFactoryPtr m_s_pUniqueFactory;
	};
}


#endif


