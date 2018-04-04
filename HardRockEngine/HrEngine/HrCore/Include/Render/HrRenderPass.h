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

		void SetDepthStencilState(HrDepthStencilState* pDepthStencilState);
		void SetBlendState(HrBlendState* pBlendState);
	private:

	private:
		std::string m_strPassName;

		HrDepthStencilState* m_pDepthStencilState;
		HrBlendState* m_pBlendState;
		HrRasterizerState* m_pRasterizerState;

		HrShaderPtr m_pVertexShader;
		HrShaderPtr m_pPixelShader;

		std::array<uint32, HrShader::ST_NUMSHADERTYPES> m_arrShaderIndex;


	};
}

#endif

