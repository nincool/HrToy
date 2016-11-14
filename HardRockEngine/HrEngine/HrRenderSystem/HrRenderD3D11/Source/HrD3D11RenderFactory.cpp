#include "HrD3D11RenderFactory.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11ShaderCompiler.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11GraphicsBuffer.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderLayout.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Shader.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderWindow.h"
#include "HrCore/Include/Render/HrVertex.h"
#include <boost/cast.hpp>

using namespace Hr;

HrD3D11RenderFactory::HrD3D11RenderFactory()
{

}

HrD3D11RenderFactory::~HrD3D11RenderFactory()
{

}

HrRenderPtr HrD3D11RenderFactory::CreateRender()
{
	return std::static_pointer_cast<HrRender>(MakeSharedPtr<HrD3D11Render>());
}

HrRenderTargetPtr HrD3D11RenderFactory::CreateRenderTarget()
{
	return std::static_pointer_cast<HrRenderTarget>(MakeSharedPtr<HrD3D11RenderWindow>());
}

HrVertex* HrD3D11RenderFactory::CreateVertex()
{
	return HR_NEW HrVertex();
}

HrGraphicsBuffer* HrD3D11RenderFactory::CreateHardwareBuffer()
{
	return HR_NEW HrD3D11GraphicsBuffer(HrD3D11Device::Instance()->GetDevice(), HrD3D11Device::Instance()->GetImmediateContext());
}

HrRenderLayout* HrD3D11RenderFactory::CreateRenderLayout()
{
	HrRenderLayout* pRenderLayout = HR_NEW HrD3D11RenderLayout();

	return pRenderLayout;
}

HrShader* HrD3D11RenderFactory::CreateShader()
{
	HrShader* pD3D11Shader = HR_NEW HrD3D11Shader();

	return pD3D11Shader;
}

