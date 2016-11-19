#ifndef _HR_RENDERPREDECLARE_H_
#define _HR_RENDERPREDECLARE_H_

#include <memory>

namespace Hr
{
	class HrD3D11RenderFactory;
	typedef std::shared_ptr<HrD3D11RenderFactory> HrD3D11RenderFactoryPtr;

	class HrRender;
	typedef std::shared_ptr<HrRender> HrRenderPtr;
	class HrD3D11Render;
	typedef std::shared_ptr<HrD3D11Render> HrD3D11RenderPtr;

	class HrD3D11RenderWindow;
	typedef std::shared_ptr<HrD3D11RenderWindow> HrD3D11RenderWindowPtr;

	class HrD3D11Device;
	typedef std::unique_ptr<HrD3D11Device> HrD3D11DevicePtr;
	class HrD3D11Utility;
	typedef std::unique_ptr<HrD3D11Utility> HrD3D11UtilityPtr;

	class HrD3D11Shader;
	class HrD3D11GraphicsBuffer;

	class HrD3D11ShaderCompiler;
	typedef std::shared_ptr<HrD3D11ShaderCompiler> HrD3D11ShaderCompilerPtr;
}

#endif