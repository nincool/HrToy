#ifndef _HR_D3D11RENDERFACTORY_H_
#define _HR_D3D11RENDERFACTORY_H_

#include "HrCore/Include/Render/IRenderFactory.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"

namespace Hr
{
	class HrD3D11RenderFactory : public IRenderFactory
	{
	public:
		HrD3D11RenderFactory();
		~HrD3D11RenderFactory();

	public:
		virtual IRenderPtr CreateRender() override;
		virtual IRenderTargetPtr CreateRenderTarget() override;

		virtual HrVertex* CreateVertex() override;
		virtual IGraphicsBuffer* CreatehardwareBuffer() override;
		virtual IRenderLayout* CreateRenderLayout() override;
		virtual IShader* CreateShader() override;


	};
}

#endif



