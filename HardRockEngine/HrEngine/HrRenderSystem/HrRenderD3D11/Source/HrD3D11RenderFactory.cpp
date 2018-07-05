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

HrRenderFramePtr HrD3D11RenderFactory::CreateScreenRenderFrameBuffer(uint32 nWidth, uint32 nHeight)
{
	return std::static_pointer_cast<HrRenderFrame>(HrMakeSharedPtr<HrD3D11ScreenFrameBuffer>(nWidth, nHeight));
}

HrRenderFramePtr HrD3D11RenderFactory::CreateDepthStencilFrameBuffer(uint32 nWidth, uint32 nHeight)
{
	return std::static_pointer_cast<HrRenderFrame>(HrMakeSharedPtr<HrD3D11DepthStencilFrameBuffer>(nWidth, nHeight));
}

//HrTexturePtr HrD3D11RenderFactory::CreateTexture(HrTexture::EnumTextureType texType
//	, uint32 nWidth
//	, uint32 nHeight
//	, uint32 nSampleCount
//	, uint32 nSampleQuality
//	, EnumPixelFormat format)
//{
//	switch (texType)
//	{
//	case HrTexture::TEX_TYPE_1D:
//		break;
//	case HrTexture::TEX_TYPE_2D:
//		return HrMakeSharedPtr<HrD3D11Texture2D>(nWidth
//			, nHeight
//			, nSampleCount
//			, nSampleQuality
//			, format
//			, HrD3D11Texture::D3D_TEX_RENDERTARGETVIEW);
//	case HrTexture::TEX_TYPE_3D:
//		break;
//	case HrTexture::TEX_TYPE_CUBE_MAP:
//		break;
//	case HrTexture::TEX_TYPE_2D_ARRAY:
//		break;
//	case HrTexture::TEX_TYPE_2D_RECT:
//		break;
//	default:
//		return HrTexturePtr(nullptr);
//	}
//}

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

HrTexturePtr HrD3D11RenderFactory::CreateTexture2D(uint32 nWidth
	, uint32 nHeight
	, uint32 nNumMipMaps
	, uint32 nArraySize
	, uint32 nSampleCount
	, uint32 nSampleQuality
	, uint32 nAccessHint
	, EnumPixelFormat format)
{
	return HrMakeSharedPtr<HrD3D11Texture2D>(nWidth, nHeight, nNumMipMaps, nSampleCount, nSampleQuality, nAccessHint, format);
}

HrSamplerStatePtr HrD3D11RenderFactory::CreateSamplerState()
{
	return HrMakeSharedPtr<HrD3D11SamplerState>(HrD3D11Device::Instance()->GetD3DDevice()
		, HrD3D11Device::Instance()->GetD3DDeviceContext());
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


