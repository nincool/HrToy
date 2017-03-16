#ifndef _I_RENDERFACTORY_H_
#define _I_RENDERFACTORY_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Asset/HrTexture.h"
#include "HrCore/Include/Render/HrDepthStencilState.h"
#include "HrCore/Include/Render/HrBlendState.h"
#include "HrCore/Include/Render/HrRasterizerState.h"

namespace Hr
{
	class HR_CORE_API HrRenderFactory
	{
	public:
		virtual ~HrRenderFactory();

		void ReleaseRenderStatePool();
	public:
		
		virtual HrRenderPtr CreateRender() = 0;
		
		virtual HrRenderTargetPtr CreateRenderTarget() = 0;

		virtual HrVertex* CreateVertex() = 0;
		
		virtual HrGraphicsBuffer* CreateHardwareBuffer() = 0;
		
		virtual HrRenderLayout* CreateRenderLayout() = 0;
		
		virtual HrShader* CreateShader() = 0;
		
		virtual HrShaderCompilerPtr CreateShaderCompiler() = 0;

		virtual HrTexture* CreateTexture(HrTexture::EnumTextureType texType
			, uint32 nSampleCount
			, uint32 nSampleQuality) = 0;

		virtual HrSamplerState* CreateSamplerState() = 0;

		virtual HrDepthStencilState* CreateDepthStencilState(const HrDepthStencilState::HrDepthStencilStateDesc& depthStencilStateDesc) = 0;

		virtual HrBlendState* CreateBlendState(const HrBlendState::HrBlendStateDesc& blendDesc) = 0;

		virtual HrRasterizerState* CreateRasterizerState(HrRasterizerState::RasterizerStateDesc& desc) = 0;

		void CreateBuildInRasterizerState();
		HrRasterizerState* GetDefualtRasterizerState();

		void CreateBuildInBlendState();
		HrBlendState* GetDefaultBuildInBlendState();
	protected:
		HrRasterizerState* m_pDefaultRasterizerState;
		std::unordered_map<size_t, HrRasterizerState*> m_mapRasterizerStatePool;

		HrDepthStencilState* m_pDefaultDepthStencilState;
		std::unordered_map<size_t, HrDepthStencilState*> m_mapDepthStencilStatePool;

		HrBlendState* m_pDefaultBlendState;
		std::unordered_map<size_t, HrBlendState*> m_mapBlendStatePool;
	};
}

#endif


