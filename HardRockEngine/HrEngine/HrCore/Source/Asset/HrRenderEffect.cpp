#include "Asset/HrRenderEffect.h"
#include "Asset/HrResourceLoader.h"
#include "Asset/HrResourceManager.h"
#include "Asset/HrShaderCompiler.h"
#include "Asset/HrStreamData.h"
#include "Asset/HrRenderEffectParameter.h"
#include "Render/HrRenderFrameParameters.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderPass.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrDepthStencilState.h"
#include "Render/HrBlendState.h"
#include "Render/HrRasterizerState.h"
#include "Render/HrLight.h"
#include "Render/HrRenderSystem.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrSamplerState.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrRenderModule.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrUtilTools/Include/HrStringUtil.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrDirector.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/format.hpp>
#include <boost/functional/hash.hpp>

using namespace Hr;

HrRenderEffect::HrRenderEffect()
{
}

HrRenderEffect::~HrRenderEffect()
{
}

size_t HrRenderEffect::CreateHashName(const std::string& strFullFilePath)
{
	return HrHashValue(strFullFilePath + ".Hr_Effect");
}

void HrRenderEffect::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFilePath = HrFileUtils::Instance()->GetFullPathForFileName(strFilePath);
	HRASSERT(!m_strFilePath.empty(), "HrRenderEffect::DeclareResource");
	m_strFileName = strFileName;
	m_resType = HrResource::RT_EFFECT;
	m_resStatus = HrResource::RS_DECLARED;
	m_nHashID = CreateHashName(m_strFilePath);
}

bool HrRenderEffect::LoadImpl()
{
	std::string strFullPath = HrFileUtils::Instance()->GetFullPathForFileName(m_strFilePath);
	if (strFullPath.length() <= 0)
	{
		HRERROR("HrRenderEffect::LoadImpl Error! FileName[%s]", m_strFilePath.c_str());
		return false;
	}
	std::string strContentData = HrFileUtils::Instance()->GetFileString(strFullPath);
	rapidjson::Document d;
	d.Parse<0>(strContentData.c_str());
	if (d.HasParseError())
	{
		int nErrorCode = d.GetParseError();
		int nOffset = d.GetErrorOffset();
		HRERROR("HrRenderEffect::LoadImpl Error! ParseJsonFile Error! ErrorCode[%d] Offset[%d] FileName[%s]", nErrorCode, nOffset, m_strFilePath.c_str());
		return false;
	}

	const rapidjson::Value& sceneRootInfo = d["EFFECT_ROOT"];
	{
		std::string strShaderFile = sceneRootInfo["SHADER_FILE"].GetString();
		m_strShaderFile = HrFileUtils::Instance()->GetFullPathForFileName(strShaderFile);

		HrShaderCompilerPtr pShaderCompiler = HrDirector::Instance()->GetRenderModule()->GetRenderFactory()->CreateShaderCompiler(m_strShaderFile);
		LoadTechniques(sceneRootInfo, pShaderCompiler);

		pShaderCompiler->CreateEffectParameters(m_mapRenderEffectParameters, m_mapConstBufferParameters, m_mapShaderResources, m_mapRenderConstantBuffers);
		pShaderCompiler->BindParametersToShader(m_mapRenderEffectParameters, m_mapRenderConstantBuffers, m_mapVertexShaders);
		pShaderCompiler->BindParametersToShader(m_mapRenderEffectParameters, m_mapRenderConstantBuffers, m_mapPixelShaders);
	}

	return true;
}

void HrRenderEffect::LoadTechniques(const rapidjson::Value& sceneRootInfo, const HrShaderCompilerPtr& pShaderCompiler)
{
	m_vecRenderTechnique.clear();

	int nTempTechniqueIndex = 0;
	while (true)
	{
		std::string strTechniqueItem = (boost::format("TECHNIQUE_%1%") % nTempTechniqueIndex).str();
		if (sceneRootInfo.HasMember(strTechniqueItem.c_str()))
		{
			const rapidjson::Value& techniqueInfo = sceneRootInfo[strTechniqueItem.c_str()];
			HrRenderTechniquePtr pRenderTechnique = HrMakeSharedPtr<HrRenderTechnique>(techniqueInfo["NAME"].GetString());
			m_vecRenderTechnique.push_back(pRenderTechnique);

			LoadPasses(techniqueInfo, pShaderCompiler, pRenderTechnique);
		}
		else
		{
			break;
		}
		++nTempTechniqueIndex;
	}
}

void HrRenderEffect::LoadSampler(const rapidjson::Value& passInfo, const HrRenderPassPtr& pRenderPass)
{
	if (passInfo.HasMember("SAMPLER"))
	{
		const rapidjson::Value& samplerInfo = passInfo["SAMPLER"];
		int nSamplerIndex = 0;
		std::vector<HrSamplerStatePtr> vecSamplerState;
		while (true)
		{
			std::string strItem = HrStringUtil::StringFormat("SAMPLER_%d", nSamplerIndex);
			if (samplerInfo.HasMember(strItem.c_str()))
			{
				HrSamplerState::HrSamplerStateDesc samplerDesc;
				if (samplerInfo.HasMember("SAMPLER_FILTER")) samplerDesc.samplerFilter = SamplerFilter(samplerInfo["SAMPLER_FILTER"].GetString());
				if (samplerInfo.HasMember("ADDRESS_U")) samplerDesc.texAddressU = TextureAddressMode(samplerInfo["ADDRESS_U"].GetString());
				if (samplerInfo.HasMember("ADDRESS_V")) samplerDesc.texAddressV = TextureAddressMode(samplerInfo["ADDRESS_V"].GetString());
				if (samplerInfo.HasMember("ADDRESS_W")) samplerDesc.texAddressW = TextureAddressMode(samplerInfo["ADDRESS_W"].GetString());
				if (samplerInfo.HasMember("MIPLODBIAS")) samplerDesc.fMipLODBias = samplerInfo["MIPLODBIAS"].GetFloat();
				if (samplerInfo.HasMember("MAX_ANISOTROPY")) samplerDesc.nMaxAnisotropy = samplerInfo["MAX_ANISOTROPY"].GetInt();
				if (samplerInfo.HasMember("COMPARISON_FUNC")) samplerDesc.comFunc = ComparisonFunc(samplerInfo["COMPARISON_FUNC"].GetString());
				if (samplerInfo.HasMember("MIN_LOD"))
					samplerDesc.fMinLOD = boost::lexical_cast<float>(samplerInfo["MIN_LOD"].GetString());
				if (samplerInfo.HasMember("MAX_LOD"))
				{
					std::string strValue = samplerInfo["MAX_LOD"].GetString();
					if (strValue == "MAX") samplerDesc.fMaxLOD = FLT_MAX;
					else samplerDesc.fMaxLOD = boost::lexical_cast<float>(samplerInfo["MAX_LOD"].GetString());
				}

				boost::hash_combine(samplerDesc.hashName, samplerDesc.samplerFilter);
				boost::hash_combine(samplerDesc.hashName, samplerDesc.texAddressU);
				boost::hash_combine(samplerDesc.hashName, samplerDesc.texAddressV);
				boost::hash_combine(samplerDesc.hashName, samplerDesc.texAddressW);
				boost::hash_combine(samplerDesc.hashName, samplerDesc.fMipLODBias);
				boost::hash_combine(samplerDesc.hashName, samplerDesc.nMaxAnisotropy);
				boost::hash_combine(samplerDesc.hashName, samplerDesc.comFunc);
				boost::hash_combine(samplerDesc.hashName, samplerDesc.fMinLOD);
				boost::hash_combine(samplerDesc.hashName, samplerDesc.fMaxLOD);

				HrSamplerStatePtr pSamplerState = HrDirector::Instance()->GetRenderModule()->GetRenderFactory()->CreateSamplerState(samplerDesc);
				vecSamplerState.push_back(pSamplerState);

				++nSamplerIndex;
			}
			else
			{
				break;
			}
		}

		//pRenderPass->SetSamplerState(pSamplerState);
	}
	else
	{
		HrSamplerState::HrSamplerStateDesc samplerDesc;
		HrSamplerStatePtr pSamplerState = HrDirector::Instance()->GetRenderModule()->GetRenderFactory()->CreateSamplerState(samplerDesc);
		pRenderPass->SetSamplerState(pSamplerState);
	}
}

void HrRenderEffect::LoadRasterizer(const rapidjson::Value& passInfo, const HrRenderPassPtr& pRenderPass)
{
	//Rasterizer
	{
		if (passInfo.HasMember("RASTERIZER"))
		{
			const rapidjson::Value& rasterizerInfo = passInfo["RASTERIZER"];
			HrRasterizerState::HrRasterizerStateDesc rasterizerDesc;
			if (rasterizerInfo.HasMember("FILL_MODE")) rasterizerDesc.fillMode = RasterizerFillMode(rasterizerInfo["FILL_MODE"].GetString());
			if (rasterizerInfo.HasMember("CULL_MODE")) rasterizerDesc.cullMode = RasterizerCullMode(rasterizerInfo["CULL_MODE"].GetString());
			if (rasterizerInfo.HasMember("FRONT_CCW")) rasterizerDesc.bfrontCounterClockWise = rasterizerInfo["FRONT_CCW"].GetBool();
			if (rasterizerInfo.HasMember("DEPTH_BIAS")) rasterizerDesc.nDepthBias = rasterizerInfo["DEPTH_BIAS"].GetInt();
			if (rasterizerInfo.HasMember("DEPTH_BIAS_CLAMP")) rasterizerDesc.fDepthBiasClamp = rasterizerInfo["DEPTH_BIAS_CLAMP"].GetFloat();
			if (rasterizerInfo.HasMember("SLOPSCALEDEPTHBIAS")) rasterizerDesc.fSlopScaleDepthBias = rasterizerInfo["SLOPSCALEDEPTHBIAS"].GetFloat();
			if (rasterizerInfo.HasMember("DEPTH_CLIP_ENABLE")) rasterizerDesc.bScissorEnable = rasterizerInfo["SCISSOR_ENABLE"].GetBool();
			if (rasterizerInfo.HasMember("MULTISAMPLE_ENABLE")) rasterizerDesc.bMultisampleEnalbe = rasterizerInfo["MULTISAMPLE_ENABLE"].GetBool();
			if (rasterizerInfo.HasMember("ANTIALIASEDLINE_ENABLE")) rasterizerDesc.bAntialiaseLineEnable = rasterizerInfo["ANTIALIASEDLINE_ENABLE"].GetBool();

			boost::hash_combine(rasterizerDesc.hashName, rasterizerDesc.fillMode);
			boost::hash_combine(rasterizerDesc.hashName, rasterizerDesc.cullMode);
			boost::hash_combine(rasterizerDesc.hashName, rasterizerDesc.bfrontCounterClockWise);
			boost::hash_combine(rasterizerDesc.hashName, rasterizerDesc.nDepthBias);
			boost::hash_combine(rasterizerDesc.hashName, rasterizerDesc.fDepthBiasClamp);
			boost::hash_combine(rasterizerDesc.hashName, rasterizerDesc.fSlopScaleDepthBias);
			boost::hash_combine(rasterizerDesc.hashName, rasterizerDesc.bScissorEnable);
			boost::hash_combine(rasterizerDesc.hashName, rasterizerDesc.bMultisampleEnalbe);
			boost::hash_combine(rasterizerDesc.hashName, rasterizerDesc.bAntialiaseLineEnable);

			HrRasterizerStatePtr pRasterizerState = HrDirector::Instance()->GetRenderModule()->GetRenderFactory()->CreateRasterizerState(rasterizerDesc);
			pRenderPass->SetRasterizerState(pRasterizerState);
		}
		else
		{
			HrRasterizerState::HrRasterizerStateDesc rasterizerDesc;
			HrRasterizerStatePtr pRasterizerState = HrDirector::Instance()->GetRenderModule()->GetRenderFactory()->CreateRasterizerState(rasterizerDesc);
			pRenderPass->SetRasterizerState(pRasterizerState);
		}
	}
}

void HrRenderEffect::LoadDepthStencil(const rapidjson::Value& passInfo, const HrRenderPassPtr& pRenderPass)
{
	//DepthStencil
	{
		const rapidjson::Value& depthStencil = passInfo["DEPTH_STENCIL"];

		HrDepthStencilState::HrDepthStencilStateDesc depthStencilDesc;
		depthStencilDesc.bDepthEnable = depthStencil["DEPTH_ENABLE"].GetBool();
		depthStencilDesc.depthWriteMask = DepthWriteMash(depthStencil["DEPTH_WRITE_MASK"].GetString());
		depthStencilDesc.depthCompareFunc = ComparisonFunc(depthStencil["COMPARISON_FUNC"].GetString());
		depthStencilDesc.bStencilEnable = depthStencil["STENCIL_ENABLE"].GetBool();
		depthStencilDesc.stencilReadMask = depthStencil["STENCIL_READ_MASK"].GetUint();
		depthStencilDesc.stencilWriteMask = depthStencil["STENCIL_WRITE_MASK"].GetUint();
		depthStencilDesc.frontFaceCompareFunc = ComparisonFunc(depthStencil["FRONT_FACE_COMPARE_FUNC"].GetString());
		depthStencilDesc.frontFaceStencilFailOp = StencilOperation(depthStencil["FRONT_FACE_STENCIL_FAILED_OP"].GetString());
		depthStencilDesc.frontFaceStencilDepthFailOp = StencilOperation(depthStencil["FRONT_FACE_STENCILDEPTH_FAIL_OP"].GetString());
		depthStencilDesc.frontFaceStencilPassOp = StencilOperation(depthStencil["FRONT_FACE_PASS_OP"].GetString());
		depthStencilDesc.backFaceCompareFunc = ComparisonFunc(depthStencil["BACK_FACE_COMPARE_FUNC"].GetString());
		depthStencilDesc.backFaceStencilFailOp = StencilOperation(depthStencil["BACK_FACE_STENCIL_FAILED_OP"].GetString());
		depthStencilDesc.backFaceStencilDepthFailOp = StencilOperation(depthStencil["BACK_FACE_STENCILDEPTH_FAIL_OP"].GetString());
		depthStencilDesc.backFaceStencilPassOp = StencilOperation(depthStencil["BACK_FACE_PASS_OP"].GetString());
		depthStencilDesc.nStencilRef = std::stoul(depthStencil["STENCIL_REF"].GetString());

		depthStencilDesc.hashName = 0;
		boost::hash_combine(depthStencilDesc.hashName, depthStencilDesc.bDepthEnable);
		boost::hash_combine(depthStencilDesc.hashName, depthStencilDesc.depthWriteMask);
		boost::hash_combine(depthStencilDesc.hashName, depthStencilDesc.depthCompareFunc);
		boost::hash_combine(depthStencilDesc.hashName, depthStencilDesc.bStencilEnable);
		boost::hash_combine(depthStencilDesc.hashName, depthStencilDesc.stencilReadMask);
		boost::hash_combine(depthStencilDesc.hashName, depthStencilDesc.stencilWriteMask);
		boost::hash_combine(depthStencilDesc.hashName, depthStencilDesc.frontFaceCompareFunc);
		boost::hash_combine(depthStencilDesc.hashName, depthStencilDesc.frontFaceStencilFailOp);
		boost::hash_combine(depthStencilDesc.hashName, depthStencilDesc.frontFaceStencilDepthFailOp);
		boost::hash_combine(depthStencilDesc.hashName, depthStencilDesc.frontFaceStencilPassOp);
		boost::hash_combine(depthStencilDesc.hashName, depthStencilDesc.backFaceCompareFunc);
		boost::hash_combine(depthStencilDesc.hashName, depthStencilDesc.backFaceStencilFailOp);
		boost::hash_combine(depthStencilDesc.hashName, depthStencilDesc.backFaceStencilDepthFailOp);
		boost::hash_combine(depthStencilDesc.hashName, depthStencilDesc.backFaceStencilPassOp);
		boost::hash_combine(depthStencilDesc.hashName, depthStencilDesc.nStencilRef);

		HrDepthStencilStatePtr pDepthStencilState = HrDirector::Instance()->GetRenderModule()->GetRenderFactory()->CreateDepthStencilState(depthStencilDesc);
		pRenderPass->SetDepthStencilState(pDepthStencilState);
	}
}

void HrRenderEffect::LoadBlendState(const rapidjson::Value& passInfo, const HrRenderPassPtr& pRenderPass)
{
	//Blend
	{
		const rapidjson::Value& blendInfo = passInfo["BLEND"];

		HrBlendState::HrBlendStateDesc blendDesc;
		blendDesc.bBlendEnable = blendInfo["BLEND_ENABLE"].GetBool();
		blendDesc.blendOperation = BlendOperation(blendInfo["BLEND_OP"].GetString());
		blendDesc.srcBlend = AlphaBlendFactor(blendInfo["SRC_BLEND"].GetString());
		blendDesc.dstBlend = AlphaBlendFactor(blendInfo["DEST_BLEND"].GetString());
		blendDesc.blendOperationAlpha = BlendOperation(blendInfo["BLEND_OP_ALPHA"].GetString());
		blendDesc.srcBlendAlpha = AlphaBlendFactor(blendInfo["SRC_BLEND_ALPHA"].GetString());
		blendDesc.dstBlendAlpha = AlphaBlendFactor(blendInfo["DEST_BLEND_ALPHA"].GetString());
		std::vector<std::string> vecMaskColor = HrStringUtil::GetVector(blendInfo["RENDER_TARGET_WRITE_MASK"].GetString(), "|");
		blendDesc.colorMask = ColorMask(vecMaskColor);
		float4 blendFactorColor = HrStringUtil::GetFloat4FromString(blendInfo["BLEND_FACTOR_COLOR"].GetString(), "|");
		blendDesc.blendFactor = HrColor(blendFactorColor[0], blendFactorColor[1], blendFactorColor[2], blendFactorColor[3]);

		std::string strTemp = blendInfo["SAMPLE_MASK"].GetString();
		blendDesc.nSampleMask = std::stoul(blendInfo["SAMPLE_MASK"].GetString(), nullptr, 16);

		blendDesc.hashName = 0;
		boost::hash_combine(blendDesc.hashName, blendDesc.bBlendEnable);
		boost::hash_combine(blendDesc.hashName, blendDesc.blendOperation);
		boost::hash_combine(blendDesc.hashName, blendDesc.blendOperation);
		boost::hash_combine(blendDesc.hashName, blendDesc.srcBlend);
		boost::hash_combine(blendDesc.hashName, blendDesc.dstBlend);
		boost::hash_combine(blendDesc.hashName, blendDesc.blendOperationAlpha);
		boost::hash_combine(blendDesc.hashName, blendDesc.srcBlendAlpha);
		boost::hash_combine(blendDesc.hashName, blendDesc.dstBlendAlpha);
		boost::hash_combine(blendDesc.hashName, blendDesc.nSampleMask);

		auto pBlendState = HrDirector::Instance()->GetRenderModule()->GetRenderFactory()->CreateBlendState(blendDesc);
		pRenderPass->SetBlendState(pBlendState);
	}
}

void HrRenderEffect::LoadPasses(const rapidjson::Value& techniqueInfo, const HrShaderCompilerPtr& pShaderCompiler, const HrRenderTechniquePtr& pRenderTechnique)
{
	int nTempPassIndex = 0;
	while (true)
	{
		std::string strPassName = (boost::format("PASS_%1%") % nTempPassIndex).str();
		if (techniqueInfo.HasMember(strPassName.c_str()))
		{
			const rapidjson::Value& passInfo = techniqueInfo[strPassName.c_str()];
			HrRenderPassPtr pRenderPass = pRenderTechnique->AddPass(passInfo["NAME"].GetString());
			{
				const rapidjson::Value& shaderInfo = passInfo["SHADER"];
				LoadShaders(shaderInfo, pShaderCompiler, pRenderTechnique, pRenderPass);
			}

			LoadSampler(passInfo, pRenderPass);
			LoadRasterizer(passInfo, pRenderPass);
			LoadDepthStencil(passInfo, pRenderPass);
			LoadBlendState(passInfo, pRenderPass);

		}
		else
		{
			break;
		}
		++nTempPassIndex;
	}
}


void HrRenderEffect::LoadShaders(const rapidjson::Value& shaderInfo
	, const HrShaderCompilerPtr& pShaderCompiler
	, const HrRenderTechniquePtr& pRenderTechnique
	, const HrRenderPassPtr& pRenderPass)
{
	//shader
	{
		std::string strVertexEnterPoint = shaderInfo["VERTEX_SHADER"].GetString();
		auto iteVertexShader = m_mapVertexShaders.find(strVertexEnterPoint);
		if (iteVertexShader != m_mapVertexShaders.end())
		{
			pRenderPass->SetShader(iteVertexShader->second, HrShader::ST_VERTEX_SHADER);
		}
		else
		{
			if (pShaderCompiler->CompileShaderFromCode(strVertexEnterPoint, HrShader::ST_VERTEX_SHADER))
			{
				HrShaderPtr pVertexShader = HrDirector::Instance()->GetRenderModule()->GetRenderFactory()->CreateShader();
				pVertexShader->StreamIn(pShaderCompiler->GetCompiledData(strVertexEnterPoint), m_strShaderFile, strVertexEnterPoint, HrShader::ST_VERTEX_SHADER);

				pRenderPass->SetShader(pVertexShader, HrShader::ST_VERTEX_SHADER);
				m_mapVertexShaders.insert(std::make_pair(strVertexEnterPoint, pVertexShader));

				std::vector<std::tuple<EnumVertexElementSemantic, uint32, EnumVertexElementType> > vecInputSimantic, vecOutputSimantic;
				pShaderCompiler->GetVertexInputOutputSimantic(strVertexEnterPoint, vecInputSimantic, vecOutputSimantic);

				//±£Ö¤InputVertexElementÒ»ÖÂ
				if (pRenderTechnique->IsVertexInputSimanticInit())
				{
					if (!pRenderTechnique->IsVertexInputSimanticSame(vecInputSimantic))
					{
						TRE("compiling shader error!");
					}
				}
				else
				{
					pRenderTechnique->SetVertexInputSimantic(std::move(vecInputSimantic));
					pRenderTechnique->SetVertexOutputSimantic(std::move(vecOutputSimantic));
				}
			}
			else
			{
				TRE("compiling shader error!");
			}
		}
	}

	{
		std::string strPixelEnterPoint = shaderInfo["PIXEL_SHADER"].GetString();
		auto itePixShader = m_mapPixelShaders.find(strPixelEnterPoint);
		if (itePixShader != m_mapPixelShaders.end())
		{
			pRenderPass->SetShader(itePixShader->second, HrShader::ST_PIXEL_SHADER);
		}
		else
		{
			if (pShaderCompiler->CompileShaderFromCode(strPixelEnterPoint, HrShader::ST_PIXEL_SHADER))
			{
				HrShaderPtr pPixelShader = HrDirector::Instance()->GetRenderModule()->GetRenderFactory()->CreateShader();
				pPixelShader->StreamIn(pShaderCompiler->GetCompiledData(strPixelEnterPoint), m_strShaderFile, strPixelEnterPoint, HrShader::ST_PIXEL_SHADER);

				pRenderPass->SetShader(pPixelShader, HrShader::ST_PIXEL_SHADER);
				m_mapPixelShaders.insert(std::make_pair(strPixelEnterPoint, pPixelShader));
			}
			else
			{
				TRE("compiler shader error!");
			}
		}
	}
}

bool HrRenderEffect::UnloadImpl()
{
	return true;
}

void HrRenderEffect::UpdateAutoEffectParams(const HrRenderFrameParametersPtr& pRenderFrameParameters)
{
	UpdateLightsEffectParameter(pRenderFrameParameters);

	for (auto& item : m_mapRenderEffectParameters)
	{
		UpdateOneEffectParameter(item.second, pRenderFrameParameters);
	}

	//for (auto& item : m_mapRenderConstantBuffers)
	//{
	//	item.second->UpdateConstantBuffer();
	//}
}

void HrRenderEffect::UpdateLightsEffectParameter(const HrRenderFrameParametersPtr& pRenderFrameParameters)
{
	//ambient
	HrRenderParamDefine* pRenderParamDefine = HrRenderParamDefine::GetRenderParamDefineByType(RPT_AMBIENT_COLOR);
	if (pRenderParamDefine)
	{
		size_t nHashLightNumName = HrHashValue(pRenderParamDefine->strName);
		auto iteEffParam = m_mapRenderEffectParameters.find(nHashLightNumName);
		if (iteEffParam != m_mapRenderEffectParameters.end())
		{
			*(iteEffParam->second) = pRenderFrameParameters->GetAmbientColor();
		}
	}

	pRenderParamDefine = HrRenderParamDefine::GetRenderParamDefineByType(RPT_LIGHTS_NUM);
	BOOST_ASSERT(pRenderParamDefine);
	{
		size_t nHashLightNumName = HrHashValue(pRenderParamDefine->strName);
		auto iteEffParam = m_mapRenderEffectParameters.find(nHashLightNumName);
		if (iteEffParam != m_mapRenderEffectParameters.end())
		{
			*(iteEffParam->second) = pRenderFrameParameters->GetLightsNum();
			//*(iteEffParam->second) = uint4(0, 0, 1, 0);
		}
	}

	//director light
	{
		UpdateDirectionalLightEffectParameter(pRenderFrameParameters);
		UpdatePointLightEffectParameter(pRenderFrameParameters);
	}

}

void HrRenderEffect::UpdateDirectionalLightEffectParameter(const HrRenderFrameParametersPtr& pRenderFrameParameters)
{
	uint32 nDirectLightNum = pRenderFrameParameters->GetLightsNum()[HrLight::LT_DIRECTIONAL];
	for (uint32 i = 0; i < nDirectLightNum; ++i)
	{
		auto pRenderParamDefine = HrRenderParamDefine::GetRenderParamDefineByType(RPT_DIRECTIONAL_LIGHT_COLOR);
		BOOST_ASSERT(pRenderParamDefine);
		{
			size_t nHashParamName = HrHashValue(std::string("directLight"));
			HrHashCombine(nHashParamName, i);
			HrHashCombine(nHashParamName, pRenderParamDefine->strName);
			auto iteRenderParam = m_mapRenderEffectParameters.find(nHashParamName);
			if (iteRenderParam != m_mapRenderEffectParameters.end())
				*(iteRenderParam->second) = pRenderFrameParameters->GetDirectionalLightColor(i);
		}

		pRenderParamDefine = HrRenderParamDefine::GetRenderParamDefineByType(RPT_DIRECTIONAL_LIGHT_DIRECTION);
		BOOST_ASSERT(pRenderParamDefine);
		{
			size_t nHashParamName = HrHashValue(std::string("directLight"));
			HrHashCombine(nHashParamName, i);
			HrHashCombine(nHashParamName, pRenderParamDefine->strName);
			auto iteRenderParam = m_mapRenderEffectParameters.find(nHashParamName);
			if (iteRenderParam != m_mapRenderEffectParameters.end())
				*(iteRenderParam->second) = pRenderFrameParameters->GetDirectionalLightDirection(i);
		}
	}
}

void HrRenderEffect::UpdatePointLightEffectParameter(const HrRenderFrameParametersPtr& pRenderFrameParameters)
{
	uint32 nPointLightNum = pRenderFrameParameters->GetLightNum(HrLight::LT_POINT);
	for (uint32 i = 0; i < nPointLightNum; ++i)
	{
		auto pRenderParamDefine = HrRenderParamDefine::GetRenderParamDefineByType(RPT_POINT_LIGHT_COLOR);
		BOOST_ASSERT(pRenderParamDefine);
		{
			size_t nHashParamName = HrHashValue(std::string("pointLight"));
			HrHashCombine(nHashParamName, i);
			HrHashCombine(nHashParamName, pRenderParamDefine->strName);
			if (m_mapRenderEffectParameters.find(nHashParamName) != m_mapRenderEffectParameters.end())
			{
				auto pEffParam = m_mapRenderEffectParameters[nHashParamName];
				*pEffParam = pRenderFrameParameters->GetPointLightColor(i);
			}
		}

		pRenderParamDefine = HrRenderParamDefine::GetRenderParamDefineByType(RPT_POINT_LIGHT_ATTENUATION);
		BOOST_ASSERT(pRenderParamDefine);
		{
			size_t nHashParamName = HrHashValue(std::string("pointLight"));
			HrHashCombine(nHashParamName, i);
			HrHashCombine(nHashParamName, pRenderParamDefine->strName);
			if (m_mapRenderEffectParameters.find(nHashParamName) != m_mapRenderEffectParameters.end())
			{
				auto pEffParam = m_mapRenderEffectParameters[nHashParamName];
				*pEffParam = pRenderFrameParameters->GetPointLightAttenuation(i);
			}
		}

		pRenderParamDefine = HrRenderParamDefine::GetRenderParamDefineByType(RPT_POINT_LIGHT_POSITION);
		BOOST_ASSERT(pRenderParamDefine);
		{
			size_t nHashParamName = HrHashValue(std::string("pointLight"));
			HrHashCombine(nHashParamName, i);
			HrHashCombine(nHashParamName, pRenderParamDefine->strName);
			if (m_mapRenderEffectParameters.find(nHashParamName) != m_mapRenderEffectParameters.end())
			{
				auto pEffParam = m_mapRenderEffectParameters[nHashParamName];
				*pEffParam = pRenderFrameParameters->GetPointLightPosition(i);
			}
		}
	}	
}

void HrRenderEffect::UpdateOneEffectParameter(const HrRenderEffectParameterPtr& pRenderEffectParameter, const HrRenderFrameParametersPtr& pRenderFrameParameters)
{
	switch (pRenderEffectParameter->ParamType())
	{
	case RPT_WORLD_MATRIX:
	{
		*pRenderEffectParameter = pRenderFrameParameters->GetWorldMatrix();
		break;
	}
	case RPT_INVERSE_WROLD_MATRIX:
	{
		break;
	}
	case RPT_TRANSPOSE_WORLD_MATRIX:
	{
		break;
	}
	case RPT_INVERSE_TRANSPOSE_WORLD_MATRIX:
	{
		*pRenderEffectParameter = pRenderFrameParameters->GetInverseTransposeWorldMatrix();
		break;
	}
	case RPT_VIEW_PROJ_MATRIX:
	{
		*pRenderEffectParameter = pRenderFrameParameters->GetViewProjMatrix();
		break;
	}
	case RPT_WORLD_VIEW_PROJ_MATRIX:
	{
		*pRenderEffectParameter = pRenderFrameParameters->GetWorldViewProjMatrix();
		break;
	}
	case RPT_CAMERA_POSITION:
	{
		*pRenderEffectParameter = pRenderFrameParameters->GetCameraPosition();
		break;
	}

	case RPT_SAMPLER:
	{
		break;
	}
	case RPT_MATERIAL_ALBEDO:
	{
		*pRenderEffectParameter = pRenderFrameParameters->GetMaterialAlbedo();
		break;
	}
	//case RPT_MATERIAL_REFLECTIVE:
	//{
	//	*pRenderEffectParameter = pRenderFrameParameters->GetMaterialReflective();
	//	break;
	//}
	//case RPT_MATERIAL_GLOSSINESS:
	//{
	//	*pRenderEffectParameter = pRenderFrameParameters->GetMaterialGlossiness();
	//	break;
	//}
	default:
		break;
	}

}

const HrRenderTechniquePtr HrRenderEffect::GetBestTechnique(const HrRenderLayoutPtr& pRenderLayout)
{
	for (size_t i = 0; i < m_vecRenderTechnique.size(); ++i)
	{
		if (m_vecRenderTechnique[i]->GetInputSimanticHashValue() == pRenderLayout->GetSimanticHashValue())
		{
			return m_vecRenderTechnique[i];
		}
	}

	return nullptr;
}

const HrRenderTechniquePtr HrRenderEffect::GetTechniqueByIndex(uint32 nIndex)
{
	if (0 <= nIndex && nIndex < m_vecRenderTechnique.size())
	{
		return m_vecRenderTechnique[nIndex];
	}
	return nullptr;
}

const HrRenderTechniquePtr HrRenderEffect::GetTechniqueByName(const std::string& strTechniqueName)
{
	size_t const nHashName = HrHashValue(strTechniqueName);
	for (const auto& item : m_vecRenderTechnique)
	{
		if (item->HashName() == nHashName)
		{
			return item;
		}
	}

	return nullptr;
}

const HrRenderEffectParameterPtr HrRenderEffect::GetParameterByName(const std::string& strParamName)
{
	size_t const nHashName = HrHashValue(strParamName);
	auto& iteParam = m_mapRenderEffectParameters.find(nHashName);
	if (iteParam != m_mapRenderEffectParameters.end())
	{
		return iteParam->second;
	}

	return nullptr;
}

