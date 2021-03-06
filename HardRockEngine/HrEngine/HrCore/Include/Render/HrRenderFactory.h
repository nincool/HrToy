#ifndef _I_RENDERFACTORY_H_
#define _I_RENDERFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Asset/HrTexture.h"
#include "HrCore/Include/Render/HrDepthStencilState.h"
#include "HrCore/Include/Render/HrBlendState.h"
#include "HrCore/Include/Render/HrRasterizerState.h"
#include "HrCore/Include/Render/HrSamplerState.h"

namespace Hr
{
	class HR_CORE_API HrRenderFactory
	{
	public:
		virtual ~HrRenderFactory();

	public:
		virtual HrRenderPtr CreateRender() = 0;
		virtual HrRenderFramePtr CreateRenderFrame(uint32 nWidth, uint32 nHeight) = 0;
		/*
			@brief	render target [12/17/2018 By Hr]
		*/
		virtual HrRenderTargetPtr CreateRenderTarget(const HrTexturePtr& pTexture) = 0;
		/*
			@brief	depth stencil [12/17/2018 By Hr]
		*/
		virtual HrDepthStencilPtr CreateDepthStencil(uint32 nWidth, uint32 nHeight) = 0;
		/*
			@brief ����Textue2D [3/21/2019 By Hr]
		*/
		virtual HrTexturePtr CreateTexture2D(uint32 nWidth
			, uint32 nHeight
			, uint32 nNumMipMaps
			, uint32 nSampleCount
			, uint32 nSampleQuality
			, uint32 nAccessHint
			, uint32 nUsedFor
			, EnumPixelFormat format) = 0;

		virtual HrTexturePtr CreateTextureCubeMap(uint32 nWidth
			, uint32 nHeight
			, uint32 nNumMipMaps
			, uint32 nSampleCount
			, uint32 nSampleQuality
			, uint32 nAccessHint
			, uint32 texUsedFor
			, EnumPixelFormat format) = 0;





		virtual HrRenderFramePtr CreateScreenRenderFrameBuffer(uint32 nWidth, uint32 nHeight) = 0;
		virtual HrRenderFramePtr CreateDepthStencilFrameBuffer(uint32 nWidth, uint32 nHeight) = 0;
		virtual HrRenderFramePtr CreateDeferredFrameBuffer(uint32 nWidth, uint32 nHeight, const HrDeferredGBufferDataPtr& pDeferredGBufferData) = 0;

		virtual HrRenderLayoutPtr CreateRenderLayout() = 0;

		virtual HrVertexPtr CreateVertex() = 0;
		
		virtual HrGraphicsBufferPtr CreateGraphicsBuffer() = 0;
		
		virtual HrShaderPtr CreateShader() = 0;
		
		virtual HrShaderCompilerPtr CreateShaderCompiler(const std::string& strFileName) = 0;



		virtual HrSamplerStatePtr CreateSamplerState(const HrSamplerState::HrSamplerStateDesc& samplerDesc) = 0;

		virtual HrDepthStencilStatePtr CreateDepthStencilState(const HrDepthStencilState::HrDepthStencilStateDesc& depthStencilStateDesc) = 0;

		virtual HrBlendStatePtr CreateBlendState(const HrBlendState::HrBlendStateDesc& blendDesc) = 0;

		virtual HrRasterizerStatePtr CreateRasterizerState(HrRasterizerState::HrRasterizerStateDesc& desc) = 0;

		void CreateBuildInRasterizerState();
		void CreateBuildInBlendState();
	protected:
		std::unordered_map<size_t, HrRasterizerStatePtr> m_mapRasterizerStatePool;
		std::unordered_map<size_t, HrDepthStencilStatePtr> m_mapDepthStencilStatePool;
		std::unordered_map<size_t, HrBlendStatePtr> m_mapBlendStatePool;
	};
}

#endif


