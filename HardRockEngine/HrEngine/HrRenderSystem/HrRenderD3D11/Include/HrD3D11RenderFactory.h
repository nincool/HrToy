#ifndef _HR_D3D11RENDERFACTORY_H_
#define _HR_D3D11RENDERFACTORY_H_

#include "HrCore/Include/Render/HrRenderFactory.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"

namespace Hr
{
	class HrD3D11RenderFactory : public HrRenderFactory
	{
	public:
		HrD3D11RenderFactory();
		~HrD3D11RenderFactory();

	public:
		virtual HrRenderPtr CreateRender() override;
		
		virtual HrRenderTargetPtr CreateRenderTarget() override;

		virtual HrVertex* CreateVertex() override;
		
		virtual HrGraphicsBuffer* CreateHardwareBuffer() override;
		
		virtual HrRenderLayout* CreateRenderLayout() override;
		
		virtual HrShader* CreateShader() override;

		virtual HrShaderCompilerPtr CreateShaderCompiler() override;
	};
}

#endif


