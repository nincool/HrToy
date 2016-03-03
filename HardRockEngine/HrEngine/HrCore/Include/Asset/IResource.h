#ifndef _I_RESOURCE_H_
#define _I_RESOURCE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IResource : public ResourceAllocatedObject
	{
	public:
		virtual ~IResource(){}

		virtual void Load() = 0;
		virtual void Unload() = 0;

	};
}

#endif


