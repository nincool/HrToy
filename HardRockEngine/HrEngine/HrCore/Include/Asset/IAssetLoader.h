#ifndef _I_ASSERTLOADER_H_
#define _I_ASSERTLOADER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IAssertLoader : public GeneralAllocatedObject
	{
	public:
		virtual ~IAssertLoader(){}
	};
}

#endif



