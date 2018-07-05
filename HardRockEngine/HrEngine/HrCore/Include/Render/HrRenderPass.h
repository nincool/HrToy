#ifndef _HR_RENDERPASS_H_
#define _HR_RENDERPASS_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrShader.h"

namespace Hr
{
	class HR_CORE_API HrRenderPass 
	{
	public:
		HrRenderPass(const std::string& strPassName);
		~HrRenderPass();

		void BindPass(const HrRenderPtr& pRender);
		void UnBindPass(const HrRenderPtr& pRender);

		const HrShaderPtr& GetShader(HrShader::EnumShaderType shaderType);
		void SetShader(const HrShaderPtr& pShader, HrShader::EnumShaderType shaderType);

		void SetRasterizerState(const HrRasterizerStatePtr& pRasterizerState);
		void SetDepthStencilState(const HrDepthStencilStatePtr& pDepthStencilState);
		void SetBlendState(const HrBlendStatePtr& pBlendState);

	private:

	private:
		std::string m_strPassName;

		HrShaderPtr m_pVertexShader;
		HrShaderPtr m_pPixelShader;
		
		//BlendState
		HrBlendStatePtr m_pBlendState;
		HrDepthStencilStatePtr m_pDepthStencilState;
		HrRasterizerStatePtr m_pRasterizerState;


	};
}

#endif

