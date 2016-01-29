#ifndef _I_RENDERFACTORY_H_
#define _I_RENDERFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HR_CORE_API IRenderFactory : public RenderSysAllocatedObject
	{
	public:
		virtual ~IRenderFactory(){};

	public:
		virtual IRenderPtr CreateRender() = 0;

	};
}

#endif


