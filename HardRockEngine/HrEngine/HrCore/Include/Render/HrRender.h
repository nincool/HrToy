#ifndef _HR_RENDER_H_
#define _HR_RENDER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrRender
	{
	public:
		virtual ~HrRender(){};
		/**
		*	@Brief:  ������Ⱦ��[10/28/2015 By Hr]
		*/
		virtual bool Init() = 0;
		
		virtual void BindFrameBuffer(const HrRenderFramePtr& pRenderFrameBuffer) = 0;
		
		virtual const HrRenderFramePtr& GetBindFrameBuffer() = 0;

		virtual void SetRenderTarget(const HrRenderTargetPtr& pRenderTarget, const HrDepthStencilPtr& pDepthStencil) = 0;
		virtual void SetViewPort(const HrViewPortPtr& pViewPort) = 0;

		virtual void BindRasterizerState(const HrRasterizerStatePtr& pRasterizerState) = 0;
		virtual void BindBlendState(const HrBlendStatePtr& pBlendState) = 0;
		virtual void BindDepthStencilState(const HrDepthStencilStatePtr& pDepthStencilState) = 0;

		virtual void BindShader(const HrShaderPtr& pShader) = 0;

		virtual void Render(const HrRenderTechniquePtr& pRenderTechnique, const HrRenderLayoutPtr& pRenderLayout) = 0;

		virtual void SwapChain() = 0;
		/**
		*	@Brief:  �ݻ���Ⱦ��[10/28/2015 By Hr]
		*/
		virtual void ReleaseRenderEngine() = 0;

	};
}

#endif




