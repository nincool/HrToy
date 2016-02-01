#ifndef _HR_GEOMETRYFACTORY_H_
#define _HR_GEOMETRYFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HrGeometryFactory : public GeneralAllocatedObject
	{
	public:
		HrGeometryFactory();
		~HrGeometryFactory();

		static HrGeometryFactory& GetInstance();

	private:
		static HrGeometryFactoryPtr m_s_pUniqueFactory;
	};
}


#endif


