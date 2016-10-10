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
		
		virtual HrRenderTargetPtr CreateRenderTarget() = 0;

		virtual HrVertex* CreateVertex() = 0;
		
		virtual HrGraphicsBuffer* CreateHardwareBuffer() = 0;
		
		virtual HrRenderLayout* CreateRenderLayout() = 0;
		
		virtual HrShader* CreateShader() = 0;
		
	};
}

#endif


