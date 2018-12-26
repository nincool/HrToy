#ifndef _HR_RENDER_H_
#define _HR_RENDER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrRenderFrame.h"

namespace Hr
{
	class HrRender
	{
	public:
		virtual ~HrRender(){};
		
		virtual void BindFrameBuffer(const HrRenderFramePtr& pRenderFrameBuffer) = 0;
		
		virtual const HrRenderFramePtr& GetBindFrameBuffer() = 0;

		virtual void SetRenderTarget(const HrRenderTargetPtr& pRenderTarget, const HrDepthStencilPtr& pDepthStencil) = 0;
		virtual void SetRenderTarget(const std::array<HrRenderTargetPtr, HrRenderFrame::RTL_MAX>& vecRenderTargers, const HrDepthStencilPtr& pDepthStencil) = 0;
		virtual void SetViewPort(const HrViewPortPtr& pViewPort) = 0;

		virtual void BindRasterizerState(const HrRasterizerStatePtr& pRasterizerState) = 0;
		virtual void BindBlendState(const HrBlendStatePtr& pBlendState) = 0;
		virtual void BindDepthStencilState(const HrDepthStencilStatePtr& pDepthStencilState) = 0;

		virtual void BindShader(const HrShaderPtr& pShader) = 0;
		virtual void UnbindShader(const HrShaderPtr& pShader) = 0;

		virtual void Render(const HrRenderTechniquePtr& pRenderTechnique, const HrRenderLayoutPtr& pRenderLayout) = 0;

		virtual void SwapChain() = 0;
		/**
		*	@Brief:  ¥›ªŸ‰÷»æ∆˜[10/28/2015 By Hr]
		*/
		virtual void ReleaseRenderEngine() = 0;

	};
}

#endif




