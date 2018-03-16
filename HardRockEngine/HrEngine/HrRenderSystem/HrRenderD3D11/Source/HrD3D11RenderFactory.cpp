#include "HrD3D11RenderFactory.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11FrameBuffer.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11ShaderCompiler.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11GraphicsBuffer.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderLayout.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Shader.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderTarget.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11ShaderCompiler.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Texture.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11SamplerState.h" 
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11DepthStencilState.h"
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

HrRenderTargetPtr HrD3D11RenderFactory::CreateRenderTarget(const HrTexturePtr& pTexture)
{
	//return std::static_pointer_cast<HrRenderTarget>(HrMakeSharedPtr<HrD3D11RenderTarget>());
	return nullptr;
}

HrRenderFramePtr HrD3D11RenderFactory::CreateRenderFrameBuffer()
{
	return std::static_pointer_cast<HrRenderFrame>(HrMakeSharedPtr<HrD3D11FrameBuffer>());
}

HrRenderFramePtr HrD3D11RenderFactory::CreateScreenRenderFrameBuffer(uint32 nWidth, uint32 nHeight)
{
	return std::static_pointer_cast<HrRenderFrame>(HrMakeSharedPtr<HrD3D11ScreenFrameBuffer>(nWidth, nHeight));
}

HrTexturePtr HrD3D11RenderFactory::CreateTexture(HrTexture::EnumTextureType texType
	, uint32 nWidth
	, uint32 nHeight
	, uint32 nSampleCount
	, uint32 nSampleQuality)
{
	switch (texType)
	{
	case HrTexture::TEX_TYPE_1D:
		break;
	case HrTexture::TEX_TYPE_2D:
		return HrMakeSharedPtr<HrD3D11Texture2D>(nWidth
			, nHeight
			, nSampleCount
			, nSampleQuality
			, HrD3D11Texture::D3D_TEX_RENDERTARGETVIEW);
	case HrTexture::TEX_TYPE_3D:
		break;
	case HrTexture::TEX_TYPE_CUBE_MAP:
		break;
	case HrTexture::TEX_TYPE_2D_ARRAY:
		break;
	case HrTexture::TEX_TYPE_2D_RECT:
		break;
	default:
		return HrTexturePtr(nullptr);
	}
}

HrRenderLayoutPtr HrD3D11RenderFactory::CreateRenderLayout()
{
	return HrMakeSharedPtr<HrD3D11RenderLayout>();
}

HrVertexPtr HrD3D11RenderFactory::CreateVertex()
{
	return HrMakeSharedPtr<HrVertex>();
}

HrGraphicsBufferPtr HrD3D11RenderFactory::CreateGraphicsBuffer()
{
	return HrMakeSharedPtr<HrD3D11GraphicsBuffer>(HrD3D11Device::Instance()->GetD3DDevice(), HrD3D11Device::Instance()->GetD3DDeviceContext());
}

//HrRenderLayout* HrD3D11RenderFactory::CreateRenderLayout()
//{
//	HrRenderLayout* pRenderLayout = HR_NEW HrD3D11RenderLayout();
//
//	return pRenderLayout;
//}

HrShaderPtr HrD3D11RenderFactory::CreateShader()
{
	HrShaderPtr pD3D11Shader = HrMakeSharedPtr<HrD3D11Shader>();

	return pD3D11Shader;
}

HrShaderCompilerPtr HrD3D11RenderFactory::CreateShaderCompiler(const std::string& strFileName)
{
	HrShaderCompilerPtr pShaderCompiler = HrMakeSharedPtr<HrD3D11ShaderCompiler>(strFileName);

	return pShaderCompiler;
}

//HrTexture* HrD3D11RenderFactory::CreateTexture(HrTexture::EnumTextureType texType
//	, uint32 nSampleCount
//	, uint32 nSampleQuality)
//{
//	HrD3D11Texture2D* pTexture2D = HR_NEW HrD3D11Texture2D(HrD3D11Device::Instance()->GetD3DDevice().get()
//		, HrD3D11Device::Instance()->GetD3DDeviceContext().get()
//		, texType
//		, nSampleCount
//		, nSampleQuality);
//	return pTexture2D;
//}

HrSamplerStatePtr HrD3D11RenderFactory::CreateSamplerState()
{
	return HrMakeSharedPtr<HrD3D11SamplerState>(HrD3D11Device::Instance()->GetD3DDevice()
		, HrD3D11Device::Instance()->GetD3DDeviceContext());
}

HrDepthStencilState* HrD3D11RenderFactory::CreateDepthStencilState(const HrDepthStencilState::HrDepthStencilStateDesc& depthStencilStateDesc)
{
	auto itemBlend = m_mapDepthStencilStatePool.find(depthStencilStateDesc.hashName);
	if (itemBlend != m_mapDepthStencilStatePool.end())
	{
		return static_cast<HrDepthStencilState*>(itemBlend->second);
	}
	else
	{
		HrDepthStencilState* pDepthStencilStawte = HR_NEW HrD3D11DepthStencilState(HrD3D11Device::Instance()->GetD3DDevice().get()
			, HrD3D11Device::Instance()->GetD3DDeviceContext().get(), depthStencilStateDesc);
		m_mapDepthStencilStatePool[depthStencilStateDesc.hashName] = pDepthStencilStawte;

		return pDepthStencilStawte;
	}
}

HrBlendState* HrD3D11RenderFactory::CreateBlendState(const HrBlendState::HrBlendStateDesc& blendDesc)
{
	auto itemBlend = m_mapBlendStatePool.find(blendDesc.hashName);
	if (itemBlend != m_mapBlendStatePool.end())
	{
		return static_cast<HrD3D11BlendState*>(itemBlend->second);
	}
	else
	{
		HrD3D11BlendState* pBlendState = HR_NEW HrD3D11BlendState(HrD3D11Device::Instance()->GetD3DDevice().get()
			, HrD3D11Device::Instance()->GetD3DDeviceContext().get(), blendDesc);
		m_mapBlendStatePool[blendDesc.hashName] = pBlendState;

		return pBlendState;
	}
}

HrRasterizerState* HrD3D11RenderFactory::CreateRasterizerState(HrRasterizerState::RasterizerStateDesc& desc)
{
	HrD3D11RasterizerState* pRasterizer = HR_NEW HrD3D11RasterizerState(HrD3D11Device::Instance()->GetD3DDevice().get()
		, HrD3D11Device::Instance()->GetD3DDeviceContext().get(), desc);

	return pRasterizer;
}
