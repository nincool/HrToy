#ifndef _HR_D3D11RENDERFACTORY_H_
#define _HR_D3D11RENDERFACTORY_H_

#include "HrCore/Include/Render/HrRenderFactory.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"

namespace Hr
{
	class HrD3D11RenderFactory : public HrRenderFactory
	{
	public:
		HrD3D11RenderFactory();
		~HrD3D11RenderFactory();

	public:
		virtual HrRenderPtr CreateRender() override;
		virtual HrRenderFramePtr CreateRenderFrame(uint32 nWidth, uint32 nHeight) override;

		virtual HrRenderTargetPtr CreateRenderTarget(const HrTexturePtr& pTexture) override;
		virtual HrDepthStencilPtr CreateDepthStencil(uint32 nWidth, uint32 nHeight) override;

		virtual HrTexturePtr CreateTexture2D(uint32 nWidth
			, uint32 nHeight
			, uint32 nNumMipMaps
			, uint32 nSampleCount
			, uint32 nSampleQuality
			, uint32 nAccessHint
			, uint32 texUsedFor
			, EnumPixelFormat format) override;

		virtual HrTexturePtr CreateTextureCubeMap(uint32 nWidth
			, uint32 nHeight
			, uint32 nNumMipMaps
			, uint32 nSampleCount
			, uint32 nSampleQuality
			, uint32 nAccessHint
			, uint32 texUsedFor
			, EnumPixelFormat format) override;





		
		virtual HrRenderFramePtr CreateScreenRenderFrameBuffer(uint32 nWidth, uint32 nHeight) override;
		virtual HrRenderFramePtr CreateDepthStencilFrameBuffer(uint32 nWidth, uint32 nHeight) override;
		virtual HrRenderFramePtr CreateDeferredFrameBuffer(uint32 nWidth, uint32 nHeight, const HrDeferredGBufferDataPtr& pDeferredGBufferData) override;

		virtual HrRenderLayoutPtr CreateRenderLayout() override;

		virtual HrVertexPtr CreateVertex() override;
		
		virtual HrGraphicsBufferPtr CreateGraphicsBuffer() override;
		
		virtual HrShaderPtr CreateShader() override;

		virtual HrShaderCompilerPtr CreateShaderCompiler(const std::string& strFileName) override;




		virtual HrSamplerStatePtr CreateSamplerState(const HrSamplerState::HrSamplerStateDesc& samplerDesc) override;

		virtual HrDepthStencilStatePtr CreateDepthStencilState(const HrDepthStencilState::HrDepthStencilStateDesc& depthStencilStateDesc) override;

		virtual HrBlendStatePtr CreateBlendState(const HrBlendState::HrBlendStateDesc& blendDesc) override;

		virtual HrRasterizerStatePtr CreateRasterizerState(HrRasterizerState::HrRasterizerStateDesc& desc) override;
	};
}

#endif


