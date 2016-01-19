#ifndef _HR_RENDERPREDECLARE_H_
#define _HR_RENDERPREDECLARE_H_

#include <memory>

namespace Hr
{
	class IRender;
	typedef std::shared_ptr<IRender> IRenderPtr;
	class HrD3D11Render;
	typedef std::shared_ptr<HrD3D11Render> HrD3D11RenderPtr;
}

#endif