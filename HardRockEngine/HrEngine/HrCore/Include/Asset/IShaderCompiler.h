#ifndef _I_SHADERCOMPILER_H_
#define _I_SHADERCOMPILER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HR_CORE_API IShaderCompiler : public RenderSysAllocatedObject
	{
	public:
		virtual ~IShaderCompiler(){}
	};
}

#endif