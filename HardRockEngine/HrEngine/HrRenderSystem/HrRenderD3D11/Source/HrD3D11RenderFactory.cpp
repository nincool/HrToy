#include "HrD3D11RenderFactory.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11ShaderCompiler.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11HardwareBuffer.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderLayout.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Shader.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderWindow.h"
#include "HrCore/Include/Render/HrVertex.h"
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

IRenderTargetPtr HrD3D11RenderFactory::CreateRenderTarget()
{
	return static_pointer_cast<IRenderTarget>(MakeSharedPtr<HrD3D11RenderWindow>());
}

HrVertex* HrD3D11RenderFactory::CreateVertex()
{
	return HR_NEW HrVertex();
}

IGraphicsBuffer* HrD3D11RenderFactory::CreatehardwareBuffer()
{
	return HR_NEW HrD3D11HardwareBuffer(HrD3D11Device::GetInstance().GetDevice(), HrD3D11Device::GetInstance().GetImmediateContext());
}

IRenderLayout* HrD3D11RenderFactory::CreateRenderLayout()
{
	IRenderLayout* pRenderLayout = HR_NEW HrD3D11RenderLayout();

	return pRenderLayout;
}

IShader* HrD3D11RenderFactory::CreateShader()
{
	IShader* pD3D11Shader = HR_NEW HrD3D11Shader();

	return pD3D11Shader;
}

