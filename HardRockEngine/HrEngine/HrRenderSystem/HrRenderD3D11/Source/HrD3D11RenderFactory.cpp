#include "HrD3D11RenderFactory.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11ShaderCompiler.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11HardwareBuffer.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderLayout.h"
#include <boost/cast.hpp>

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
	return static_pointer_cast<IRender>(MakeSharedPtr<HrD3D11Render>());
}

IShaderCompilerPtr HrD3D11RenderFactory::CreateShaderCompiler()
{
	return static_pointer_cast<IShaderCompiler>(MakeSharedPtr<HrD3D11ShaderCompiler>());
}

IGraphicsBuffer* HrD3D11RenderFactory::CreateHardwareBufferWithInstance(IGraphicsBuffer* pInstance)
{
	HrD3D11HardwareBuffer* pD3D11HardwareBufferInstance = boost::polymorphic_cast<HrD3D11HardwareBuffer*>(pInstance);
	IGraphicsBuffer* pGraphicsBuffer = HR_NEW HrD3D11HardwareBuffer(*pD3D11HardwareBufferInstance);

	return pGraphicsBuffer;
}

IRenderLayout* HrD3D11RenderFactory::CreateRenderLayout()
{
	IRenderLayout* pRenderLayout = HR_NEW HrD3D11RenderLayout();

	return pRenderLayout;
}

