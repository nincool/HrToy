#include "HrD3D11RenderFactory.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"

using namespace Hr;
using namespace std;

HrD3D11RenderFactory::HrD3D11RenderFactory()
{

}

HrD3D11RenderFactory::~HrD3D11RenderFactory()
{

}

IRenderPtr HrD3D11RenderFactory::CreateRender()
{
	return dynamic_pointer_cast<IRender>(MakeSharedPtr<HrD3D11Render>());
}



