#ifndef _HR_GRAPHICSBUFFER_H_
#define _HR_GRAPHICSBUFFER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IGraphicsBuffer : public RenderSysAllocatedObject
	{
	public:
		IGraphicsBuffer()
		{
		}
		virtual ~IGraphicsBuffer(){}

	};
}

#endif
