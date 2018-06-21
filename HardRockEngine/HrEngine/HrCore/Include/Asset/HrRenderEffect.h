#ifndef _HR_RENDEREFFECT_H_
#define _HR_RENDEREFFECT_H_

#include "HrResource.h"
#include "HrCore/Include/Render/HrDataFormat.h"
#include "ThirdParty/rapidjson/include/rapidjson/document.h"

namespace Hr
{
	class HR_CORE_API HrRenderEffect : public HrResource
	{
	public:
		HrRenderEffect();
		virtual ~HrRenderEffect();

		static size_t CreateHashName(const std::string& strFullFilePath);

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) override;

		const HrRenderTechniquePtr GetBestTechnique(const std::vector<HrVertexDataPtr>& vecVertexData);
		const HrRenderTechniquePtr GetTechniqueByIndex(uint32 nIndex);
		const HrRenderTechniquePtr GetTechniqueByName(const std::string& strTechniqueName);

		const HrRenderEffectParameterPtr GetParameterByName(const std::string& strParamName);

		void UpdateAutoEffectParams(const HrRenderFrameParametersPtr& pRenderFrameParameters);
	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;

		void LoadTechniques(const rapidjson::Value& sceneRootInfo, const HrShaderCompilerPtr& pShaderCompiler);
		void LoadPasses(const rapidjson::Value& techniqueInfo, const HrShaderCompilerPtr& pShaderCompiler, const HrRenderTechniquePtr& pRenderTechnique);
		void LoadShaders(const rapidjson::Value& shaderInfo
			, const HrShaderCompilerPtr& pShaderCompiler
			, const HrRenderTechniquePtr& pRenderTechnique
			, const HrRenderPassPtr& pRenderPass);

		void UpdateOneEffectParameter(const HrRenderEffectParameterPtr& renderEffectParameter, const HrRenderFrameParametersPtr&  renderFrameParameters);
		void UpdateLightsEffectParameter(const HrRenderFrameParametersPtr& pRenderFrameParameters);
		void UpdateDirectionalLightEffectParameter(const HrRenderFrameParametersPtr& pRenderFrameParameters);
		void UpdatePointLightEffectParameter(const HrRenderFrameParametersPtr& pRenderFrameParameters);
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
		std::unordered_map<size_t, HrRenderEffectParameterPtr> m_mapConstBufferParameters;
		std::unordered_map<size_t, HrRenderEffectParameterPtr> m_mapShaderResources;
		std::unordered_map<size_t, HrRenderEffectConstantBufferPtr> m_mapRenderConstantBuffers;

	};
}

#endif

