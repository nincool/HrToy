#include "HrD3D11RenderFactory.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11ShaderCompiler.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11HardwareBuffer.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderLayout.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Shader.h"
#include "HrCore/Include/Render/HrVertext.h"
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

HrVertext* HrD3D11RenderFactory::CreateVertext()
{
	return HR_NEW HrVertext();
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

