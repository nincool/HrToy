#include "HrD3D11RenderFactory.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11ShaderCompiler.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11GraphicsBuffer.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderLayout.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Shader.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderWindow.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11ShaderCompiler.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Texture.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11SamplerState.h" 
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11BlendState.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RasterizerState.h"
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
	return std::static_pointer_cast<HrRender>(HrMakeSharedPtr<HrD3D11Render>());
}

HrRenderTargetPtr HrD3D11RenderFactory::CreateRenderTarget()
{
	return std::static_pointer_cast<HrRenderTarget>(HrMakeSharedPtr<HrD3D11RenderWindow>());
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

HrShaderCompilerPtr HrD3D11RenderFactory::CreateShaderCompiler()
{
	HrShaderCompilerPtr pShaderCompiler = HrMakeSharedPtr<HrD3D11ShaderCompiler>();

	return pShaderCompiler;
}

HrTexture* HrD3D11RenderFactory::CreateTexture(HrTexture::EnumTextureType texType
	, uint32 nSampleCount
	, uint32 nSampleQuality)
{
	HrD3D11Texture2D* pTexture2D = HR_NEW HrD3D11Texture2D(HrD3D11Device::Instance()->GetDevice()
		, HrD3D11Device::Instance()->GetImmediateContext()
		, texType
		, nSampleCount
		, nSampleQuality);
	return pTexture2D;
}

HrSamplerState* HrD3D11RenderFactory::CreateSamplerState()
{
	HrD3D11SamplerState* pSamplerState = HR_NEW HrD3D11SamplerState(HrD3D11Device::Instance()->GetDevice()
		, HrD3D11Device::Instance()->GetImmediateContext());

	return pSamplerState;
}

HrBlendState* HrD3D11RenderFactory::CreateBlendState()
{
	HrD3D11BlendState* pBlendState = HR_NEW HrD3D11BlendState(HrD3D11Device::Instance()->GetDevice()
		, HrD3D11Device::Instance()->GetImmediateContext());

	return pBlendState;
}

HrRasterizerState* HrD3D11RenderFactory::CreateRasterizerState(HrRasterizerState::RasterizerStateDesc& desc)
{
	HrD3D11RasterizerState* pRasterizer = HR_NEW HrD3D11RasterizerState(HrD3D11Device::Instance()->GetDevice()
		, HrD3D11Device::Instance()->GetImmediateContext(), desc);

	return pRasterizer;
}

