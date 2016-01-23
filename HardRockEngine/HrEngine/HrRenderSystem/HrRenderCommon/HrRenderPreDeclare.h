#ifndef _HR_RENDERPREDECLARE_H_
#define _HR_RENDERPREDECLARE_H_

#include <memory>

namespace Hr
{
	class HrD3D11RenderFactory;
	typedef std::shared_ptr<HrD3D11RenderFactory> HrD3D11RenderFactoryPtr;

	class IRender;
	typedef std::shared_ptr<IRender> IRenderPtr;
	class HrD3D11Render;
	typedef std::shared_ptr<HrD3D11Render> HrD3D11RenderPtr;

	class HrD3D11RenderWindow;
	typedef std::shared_ptr<HrD3D11RenderWindow> HrD3D11RenderWindowPtr;

}

#endif