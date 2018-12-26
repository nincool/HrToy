#ifndef _HR_D3D11RENDER_H_
#define _HR_D3D11RENDER_H_

#include "HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/HrRender.h"
#include "HrCore/Include/Render/HrShader.h"

struct ID3D11DeviceContext;
struct ID3D11Device;

struct ID3DX11EffectMatrixVariable;

namespace Hr
{
	class HrD3D11Device;
	class IRenderDemo;

	class HrD3D11Render : public HrRender, public std::enable_shared_from_this<HrD3D11Render>
	{
	public:
		HrD3D11Render();
		~HrD3D11Render();

	public:
		virtual void BindFrameBuffer(const HrRenderFramePtr& pRenderFrameBuffer) override;
		
		virtual const HrRenderFramePtr& GetBindFrameBuffer() override;
		
		virtual void SetRenderTarget(const HrRenderTargetPtr& pRenderTarget, const HrDepthStencilPtr& pDepthStencil) override;
		virtual void SetRenderTarget(const std::array<HrRenderTargetPtr, HrRenderFrame::RTL_MAX>& vecRenderTargers, const HrDepthStencilPtr& pDepthStencil) override;
		virtual void SetViewPort(const HrViewPortPtr& pViewPort) override;

		virtual void BindRasterizerState(const HrRasterizerStatePtr& pRasterizerState) override;
		virtual void BindBlendState(const HrBlendStatePtr& pBlendState) override;
		virtual void BindDepthStencilState(const HrDepthStencilStatePtr& pDepthStencilState) override;

		virtual void BindShader(const HrShaderPtr& pShader) override;
		virtual void UnbindShader(const HrShaderPtr& pShader) override;

		virtual void Render(const HrRenderTechniquePtr& pRenderTechnique, const HrRenderLayoutPtr& pRenderLayout) override;

		virtual void SwapChain() override;

		virtual void ReleaseRenderEngine() override;

		const ID3D11DevicePtr& GetD3D11Device();
		const ID3D11DeviceContextPtr& GetD3D11DeviceContext();

	protected:
		void BindVertexShader(const HrD3D11ShaderPtr& pD3D11Shader);
		void UnbindVertexShader();
		void BindPixelShader(const HrD3D11ShaderPtr& pD3D11Shader);
		void UnbindPixelShader();
		
	private:
		HrRasterizerStatePtr m_pCachedRasterizerState;
		HrBlendStatePtr m_pCachedBindBlendState;
		HrDepthStencilStatePtr m_pCachedDepthStencilState;
		std::array<std::vector<ID3D11Buffer*>, HrShader::ST_NUMSHADERTYPES> m_arrCachedBindShaderBuffers;
		std::array<std::vector<ID3D11ShaderResourceView*>, HrShader::ST_NUMSHADERTYPES> m_arrCachedBindSRVs;
		std::array<std::vector<ID3D11SamplerState*>, HrShader::ST_NUMSHADERTYPES> m_arrCachedBindSSs;

	private:
		HrRenderFramePtr m_pCurFrameBuffer;
	};
}

#endif

