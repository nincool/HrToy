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
		
		virtual HrRenderTargetPtr CreateRenderTarget(const HrTexturePtr& pTexture) override;

		virtual HrRenderFramePtr CreateRenderFrameBuffer() override;
		virtual HrRenderFramePtr CreateScreenRenderFrameBuffer(uint32 nWidth, uint32 nHeight) override;

		//virtual HrTexturePtr CreateTexture(HrTexture::EnumTextureType texType
		//	, uint32 nWidth
		//	, uint32 nHeight
		//	, uint32 nSampleCount
		//	, uint32 nSampleQuality) override;

		virtual HrRenderLayoutPtr CreateRenderLayout() override;

		virtual HrVertexPtr CreateVertex() override;
		
		virtual HrGraphicsBufferPtr CreateGraphicsBuffer() override;
		
		virtual HrShaderPtr CreateShader() override;

		virtual HrShaderCompilerPtr CreateShaderCompiler(const std::string& strFileName) override;

		virtual HrTexturePtr CreateTexture2D(uint32 nWidth
			, uint32 nHeight
			, uint32 nNumMipMaps
			, uint32 nArraySize
			, uint32 nSampleCount
			, uint32 nSampleQuality
			, uint32 nAccessHint) override;


		virtual HrSamplerStatePtr CreateSamplerState() override;

		virtual HrDepthStencilState* CreateDepthStencilState(const HrDepthStencilState::HrDepthStencilStateDesc& depthStencilStateDesc) override;

		virtual HrBlendState* CreateBlendState(const HrBlendState::HrBlendStateDesc& blendDesc) override;

		virtual HrRasterizerState* CreateRasterizerState(HrRasterizerState::RasterizerStateDesc& desc) override;
	};
}

#endif


