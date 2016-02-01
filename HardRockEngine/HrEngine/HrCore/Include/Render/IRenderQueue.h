#ifndef _I_RENDERQUEUE_H_
#define _I_RENDERQUEUE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IRenderQueue : public RenderSysAllocatedObject
	{
	public:
		virtual ~IRenderQueue(){}
	};
}

#endif



