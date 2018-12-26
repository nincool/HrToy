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
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11DepthStencil.h"
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
	return HrCheckPointerCast<HrRender>(HrMakeSharedPtr<HrD3D11Render>());
}

HrRenderFramePtr HrD3D11RenderFactory::CreateRenderFrame(uint32 nWidth, uint32 nHeight)
{
	return HrCheckPointerCast<HrRenderFrame>(HrMakeSharedPtr<HrD3D11FrameBuffer>(nWidth, nHeight));
}

HrRenderTargetPtr HrD3D11RenderFactory::CreateRenderTarget(const HrTexturePtr& pTexture)
{
	HrD3D11Texture2DPtr& pD3DTexture2D = HrCheckPointerCast<HrD3D11Texture2D>(pTexture);
	return HrCheckPointerCast<HrRenderTarget>(HrMakeSharedPtr<HrD3D11RenderTarget>(pD3DTexture2D));
}

HrDepthStencilPtr HrD3D11RenderFactory::CreateDepthStencil(uint32 nWidth, uint32 nHeight)
{
	return HrMakeSharedPtr<HrD3D11DepthStencil>(nWidth, nHeight, PF_D24S8, HrD3D11Texture::TUF_TEX_DEPTHSTENCILVIEW);;
}

HrRenderFramePtr HrD3D11RenderFactory::CreateScreenRenderFrameBuffer(uint32 nWidth, uint32 nHeight)
{
	return std::static_pointer_cast<HrRenderFrame>(HrMakeSharedPtr<HrD3D11ScreenFrameBuffer>(nWidth, nHeight));
}

HrRenderFramePtr HrD3D11RenderFactory::CreateDepthStencilFrameBuffer(uint32 nWidth, uint32 nHeight)
{
	return std::static_pointer_cast<HrRenderFrame>(HrMakeSharedPtr<HrD3D11DepthStencilFrameBuffer>(nWidth, nHeight));
}

HrRenderFramePtr HrD3D11RenderFactory::CreateDeferredFrameBuffer(uint32 nWidth, uint32 nHeight, const HrDeferredGBufferDataPtr& pDeferredGBufferData)
{
	return std::static_pointer_cast<HrRenderFrame>(HrMakeSharedPtr<HrD3D11DeferredFrameBuffer>(nWidth, nHeight, pDeferredGBufferData));
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

HrTexturePtr HrD3D11RenderFactory::CreateTexture2D(uint32 nWidth
	, uint32 nHeight
	, uint32 nNumMipMaps
	, uint32 nSampleCount
	, uint32 nSampleQuality
	, uint32 nAccessHint
	, uint32 texUsedFor
	, EnumPixelFormat format)
{
	return HrMakeSharedPtr<HrD3D11Texture2D>(nWidth, nHeight, nNumMipMaps, nSampleCount, nSampleQuality, nAccessHint, texUsedFor, format);
}

HrSamplerStatePtr HrD3D11RenderFactory::CreateSamplerState(const HrSamplerState::HrSamplerStateDesc& samplerDesc)
{
	return HrMakeSharedPtr<HrD3D11SamplerState>(samplerDesc);
}

HrDepthStencilStatePtr HrD3D11RenderFactory::CreateDepthStencilState(const HrDepthStencilState::HrDepthStencilStateDesc& depthStencilStateDesc)
{
	auto itemDSState = m_mapDepthStencilStatePool.find(depthStencilStateDesc.hashName);
	if (itemDSState != m_mapDepthStencilStatePool.end())
	{
		return itemDSState->second;
	}
	else
	{
		HrDepthStencilStatePtr pDepthStencilState = HrMakeSharedPtr<HrD3D11DepthStencilState>(depthStencilStateDesc);
		m_mapDepthStencilStatePool[depthStencilStateDesc.hashName] = pDepthStencilState;

		return pDepthStencilState;
	}
}

HrBlendStatePtr HrD3D11RenderFactory::CreateBlendState(const HrBlendState::HrBlendStateDesc& blendDesc)
{
	auto itemBlend = m_mapBlendStatePool.find(blendDesc.hashName);
	if (itemBlend != m_mapBlendStatePool.end())
	{
		return HrCheckPointerCast<HrD3D11BlendState>(itemBlend->second);
	}
	else
	{
		auto pBlendState = HrMakeSharedPtr<HrD3D11BlendState>(blendDesc);
		m_mapBlendStatePool[blendDesc.hashName] = pBlendState;

		return pBlendState;
	}
}

HrRasterizerStatePtr HrD3D11RenderFactory::CreateRasterizerState(HrRasterizerState::HrRasterizerStateDesc& desc)
{
	auto itemRState = m_mapRasterizerStatePool.find(desc.hashName);
	if (itemRState != m_mapRasterizerStatePool.end())
	{
		return HrCheckPointerCast<HrD3D11RasterizerState>(itemRState->second);
	}
	else
	{
		auto pRasterizerState = HrMakeSharedPtr<HrD3D11RasterizerState>(desc);
		m_mapRasterizerStatePool[desc.hashName] = pRasterizerState;

		return pRasterizerState;
	}	
}

