#ifndef _I_RENDERFACTORY_H_
#define _I_RENDERFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrRenderFactory
	{
	public:
		virtual ~HrRenderFactory(){};

	public:
		
		virtual HrRenderPtr CreateRender() = 0;
		
		virtual IRenderTargetPtr CreateRenderTarget() = 0;

		virtual HrVertex* CreateVertex() = 0;
		
		virtual IGraphicsBuffer* CreateHardwareBuffer() = 0;
		
		virtual IRenderLayout* CreateRenderLayout() = 0;
		
		virtual IShader* CreateShader() = 0;
		
	};
}

#endif


