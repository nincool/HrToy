#ifndef _HR_RENDEREFFECT_H_
#define _HR_RENDEREFFECT_H_

#include "HrResource.h"
#include "HrCore/Include/Render/HrDataFormat.h"

namespace Hr
{
	class HR_CORE_API HrRenderEffect : public HrResource
	{
	public:
		HrRenderEffect();
		virtual ~HrRenderEffect();

		static size_t CreateHashName(const std::string& strFullFilePath);

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) override;

		const HrRenderTechniquePtr GetTechniqueByIndex(uint32 nIndex);
		const HrRenderTechniquePtr GetTechniqueByName(const std::string& strTechniqueName);

		const HrRenderEffectParameterPtr GetParameterByName(const std::string& strParamName);

		void UpdateAutoEffectParams(const HrRenderFrameParametersPtr& pRenderFrameParameters);
	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;

		void UpdateOneEffectParameter(const HrRenderEffectParameterPtr& renderEffectParameter, const HrRenderFrameParametersPtr&  renderFrameParameters);
		void UpdateLightsEffectParameter(const HrRenderFrameParametersPtr& pRenderFrameParameters);
	private:
		size_t m_nHashName;

		std::string m_strEffectName;
		std::string m_strFilePath;
		std::string m_strShaderFile;
		
		std::unordered_map<std::string, HrShaderPtr> m_mapVertexShaders;
		std::unordered_map<std::string, HrShaderPtr> m_mapPixelShaders;
		//std::vector<HrShaderPtr> m_vecVertexShaders;
		std::vector<HrShaderPtr> m_vecPixelShaders;

		std::vector<HrRenderTechniquePtr> m_vecRenderTechnique;

		std::unordered_map<size_t, HrRenderEffectParameterPtr> m_mapRenderEffectParameters;
		std::unordered_map<size_t, HrRenderEffectConstantBufferPtr> m_mapRenderConstantBuffers;

	};
}

#endif

