#ifndef _HR_RENDERPASS_H_
#define _HR_RENDERPASS_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrShader.h"

namespace Hr
{
	class HR_CORE_API HrRenderPass 
	{
	public:
		HrRenderPass(std::string strPassName);
		~HrRenderPass();

		void BindPass(HrRender* pRender);
		void UnBindPass(HrRender* pRender);

		void CollectShaderParameters(std::vector<HrRenderEffectParameter*>& vecRenderEffectParameter);

		HrShader* GetShader(HrShader::EnumShaderType shaderType);
		void SetShader(HrShader* pShader, HrShader::EnumShaderType shaderType);
	private:
		void StorageShaderParameter(std::vector<HrRenderEffectParameter*>& vecRenderEffectParameter, std::vector<HrRenderEffectParameter*>& vecShaderBindParameter);
	private:
		std::string m_strPassName;

		HrShader* m_pVertexShader;
		HrShader* m_pPixelShader;

		std::array<uint32, HrShader::ST_NUMSHADERTYPES> m_arrShaderIndex;
	};
}

#endif

