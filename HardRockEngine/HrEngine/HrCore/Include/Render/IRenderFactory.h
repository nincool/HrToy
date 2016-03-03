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
		virtual IShaderCompilerPtr CreateShaderCompiler() = 0;

		virtual IGraphicsBuffer* CreateHardwareBufferWithInstance(IGraphicsBuffer* pInstance) = 0;
		virtual IRenderLayout* CreateRenderLayout() = 0;
		
	};
}

#endif


