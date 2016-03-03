#ifndef _I_RESOURCELOADER_H_
#define _I_RESOURCELOADER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IResourceLoader : public GeneralAllocatedObject
	{
	public:
		virtual ~IResourceLoader(){}
	};
}

#endif



