#include "Asset/HrRenderEffect.h"
#include "Asset/HrResourceLoader.h"
#include "Asset/HrResourceManager.h"
#include "Asset/HrShaderCompiler.h"
#include "HrCore/Include/Render/HrRenderFrameParameters.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/HrRenderFactory.h"
#include "HrCore/Include/Render/HrDepthStencilState.h"
#include "HrCore/Include/Render/HrBlendState.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Asset/HrRenderEffectParameter.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrDirector.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "ThirdParty/rapidjson/include/rapidjson/document.h"

#include <boost/format.hpp>
#include <boost/functional/hash.hpp>


using namespace Hr;

HrRenderEffect::HrRenderEffect()
{
	//m_pEffectStreamBuffer = MakeSharedPtr<HrStreamData>();
	//for testing
}

HrRenderEffect::~HrRenderEffect()
{
	for (auto& itemRT : m_vecRenderTechnique)
	{
		SAFE_DELETE(itemRT);
	}
	m_vecRenderTechnique.clear();

	for (auto& item : m_vecRenderEffectStruct)
	{
		SAFE_DELETE(item);
	}
	m_vecRenderEffectStruct.clear();

	for (auto item : m_vecRenderEffectParameter)
	{
		SAFE_DELETE(item);
	}
	m_vecRenderEffectParameter.clear();

	for (auto item : m_vecRenderConstantBuffer)
	{
		SAFE_DELETE(item);
	}
	m_vecRenderConstantBuffer.clear();

	for (auto& item : m_vecVertexShaders)
	{
		SAFE_DELETE(item);
	}
	for (auto& item : m_vecPixelShaders)
	{
		SAFE_DELETE(item);
	}
}

size_t HrRenderEffect::CreateHashName(const std::string& strFullFilePath)
{
	return HrHashValue(strFullFilePath);
}

void HrRenderEffect::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFilePath = HrFileUtils::Instance()->GetFullPathForFileName(strFilePath);
	HRASSERT(!m_strFilePath.empty(), "HrRenderEffect::DeclareResource");
	m_strFileName = strFileName;
	m_resType = HrResource::RT_EFFECT;

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
	HrStreamDataPtr pStreamData = HrFileUtils::Instance()->GetFileData(strFullPath);
	rapidjson::Document d;
	d.Parse<0>(pStreamData->GetBufferPoint());
	if (d.HasParseError())
	{
		int nErrorCode = d.GetParseError();
		int nOffset = d.GetErrorOffset();
		HRERROR("HrRenderEffect::LoadImpl Error! ParseJsonFile Error! ErrorCode[%d] Offset[%d]", nErrorCode, nOffset);
		return false;
	}

	const rapidjson::Value& sceneRootInfo = d["EFFECT_ROOT"];

	{
		std::string strShadeFile = sceneRootInfo["SHADER_FILE"].GetString();
		m_strShaderFile = HrFileUtils::Instance()->GetFullPathForFileName(strShadeFile);

		HrStreamDataPtr pShaderFileData = HrFileUtils::Instance()->GetFileData(m_strShaderFile);
		HrShaderCompilerPtr pShaderCompiler = HrDirector::Instance()->GetRenderFactory()->CreateShaderCompiler();

		int nTempTechniqueIndex = 0;
		while (true)
		{
			boost::format fmtTechniqueItem("TECHNIQUE_%1%");
			std::string strTechniqueItem = (fmtTechniqueItem % nTempTechniqueIndex).str();
			if (sceneRootInfo.HasMember(strTechniqueItem.c_str()))
			{
				const rapidjson::Value& techniqueInfo = sceneRootInfo[strTechniqueItem.c_str()];
				HrRenderTechnique* pRenderTechnique = HR_NEW HrRenderTechnique(techniqueInfo["NAME"].GetString());
				m_vecRenderTechnique.push_back(pRenderTechnique);

				int nTempPassIndex = 0;
				while (true)
				{
					boost::format fmtPassItem("PASS_%1%");
					std::string strPassName = (fmtPassItem % nTempPassIndex).str();
					if (techniqueInfo.HasMember(strPassName.c_str()))
					{
						const rapidjson::Value& passInfo = techniqueInfo[strPassName.c_str()];
						HrRenderPass* pRenderPass = pRenderTechnique->AddPass(passInfo["NAME"].GetString());
						{
							const rapidjson::Value& shaderInfo = passInfo["SHADER"];
							//shader
							{
								std::string strVertexEnterPoint = shaderInfo["VERTEX_SHADER"].GetString();
								HrStreamData effectStreamBuffer;
								pShaderCompiler->CompileShaderFromCode(m_strShaderFile, *pShaderFileData.get(), HrShader::ST_VERTEX_SHADER, strVertexEnterPoint, effectStreamBuffer);
								pShaderCompiler->ReflectEffectParameters(effectStreamBuffer, strVertexEnterPoint, HrShader::ST_VERTEX_SHADER);
								pShaderCompiler->StripCompiledCode(effectStreamBuffer);

								HrShader* pVertexShader = HrDirector::Instance()->GetRenderFactory()->CreateShader();
								pVertexShader->StreamIn(effectStreamBuffer, m_strShaderFile, strVertexEnterPoint, HrShader::ST_VERTEX_SHADER);

								pRenderPass->SetShader(pVertexShader, HrShader::ST_VERTEX_SHADER);
								m_vecVertexShaders.push_back(pVertexShader);
							}
							{
								std::string strPixelEnterPoint = shaderInfo["PIXEL_SHADER"].GetString();
								HrStreamData effectStreamBuffer;
								pShaderCompiler->CompileShaderFromCode(m_strShaderFile, *pShaderFileData.get(), HrShader::ST_PIXEL_SHADER, strPixelEnterPoint, effectStreamBuffer);
								pShaderCompiler->ReflectEffectParameters(effectStreamBuffer, strPixelEnterPoint, HrShader::ST_PIXEL_SHADER);
								pShaderCompiler->StripCompiledCode(effectStreamBuffer);

								HrShader* pPixelShader = HrDirector::Instance()->GetRenderFactory()->CreateShader();
								pPixelShader->StreamIn(effectStreamBuffer, m_strShaderFile, strPixelEnterPoint, HrShader::ST_PIXEL_SHADER);

								pRenderPass->SetShader(pPixelShader, HrShader::ST_PIXEL_SHADER);
								m_vecPixelShaders.push_back(pPixelShader);
							}
						}
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

							HrDepthStencilState* pDepthStencilState = HrDirector::Instance()->GetRenderFactory()->CreateDepthStencilState(depthStencilDesc);
							pRenderPass->SetDepthStencilState(pDepthStencilState);
						}
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
							blendDesc.hashName = 0;
							boost::hash_combine(blendDesc.hashName, blendDesc.bBlendEnable);
							boost::hash_combine(blendDesc.hashName, blendDesc.blendOperation);
							boost::hash_combine(blendDesc.hashName, blendDesc.blendOperation);
							boost::hash_combine(blendDesc.hashName, blendDesc.srcBlend);
							boost::hash_combine(blendDesc.hashName, blendDesc.dstBlend);
							boost::hash_combine(blendDesc.hashName, blendDesc.blendOperationAlpha);
							boost::hash_combine(blendDesc.hashName, blendDesc.srcBlendAlpha);
							boost::hash_combine(blendDesc.hashName, blendDesc.dstBlendAlpha);
							
							HrBlendState* pBlendState = HrDirector::Instance()->GetRenderFactory()->CreateBlendState(blendDesc);
							pRenderPass->SetBlendState(pBlendState);
						}
					}
					else
					{
						break;
					}
					++nTempPassIndex;
				}
			}
			else
			{
				break;
			}
			++nTempTechniqueIndex;
		}

		pShaderCompiler->CreateEffectParameters(m_vecRenderEffectParameter, m_vecRenderEffectStruct, m_vecRenderConstantBuffer);
		pShaderCompiler->BindParametersToShader(m_vecRenderEffectParameter, m_vecRenderEffectStruct, m_vecRenderConstantBuffer, m_vecVertexShaders);
		pShaderCompiler->BindParametersToShader(m_vecRenderEffectParameter, m_vecRenderEffectStruct, m_vecRenderConstantBuffer, m_vecPixelShaders);
	}

	return true;
}

bool HrRenderEffect::UnloadImpl()
{
	return true;
}

void HrRenderEffect::UpdateAutoEffectParams(HrRenderFrameParameters& renderFrameParameters)
{
	for (auto& item : m_vecRenderEffectStruct)
	{
		for (uint32 nIndex = 0; nIndex < item->ElementNum(); ++nIndex)
		{
			UpdateOneEffectParameter(*(item->ParameterByIndex(nIndex)), renderFrameParameters);
		}
	}
	for (auto& item : m_vecRenderEffectParameter)
	{
		UpdateOneEffectParameter(*item, renderFrameParameters);
	}

	for (auto& item : m_vecRenderConstantBuffer)
	{
		item->UpdateConstantBuffer();
	}
}

void HrRenderEffect::UpdateOneEffectParameter(HrRenderEffectParameter& renderEffectParameter, HrRenderFrameParameters& renderFrameParameters)
{
	switch (renderEffectParameter.ParamType())
	{
	case RPT_WORLD_MATRIX:
	{
		if (renderFrameParameters.WorldMatrixDirty())
			renderEffectParameter = renderFrameParameters.GetWorldMatrix();
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
		if (renderFrameParameters.InverseTransposeWorldMatrixDirty())
			renderEffectParameter = renderFrameParameters.GetInverseTransposeWorldMatrix();
		break;
	}
	case RPT_WORLD_VIEW_PROJ_MATRIX:
	{
		if (renderFrameParameters.WorldViewProjMatrixDirty())
			renderEffectParameter = renderFrameParameters.GetWorldViewProjMatrix();
		break;
	}
	case RPT_CAMERA_POSITION:
	{
		renderEffectParameter = renderFrameParameters.GetCameraPosition();
		break;
	}

	case RPT_SAMPLER:
	{
		break;
	}
	case RPT_AMBIENT_COLOR:
	{
		renderEffectParameter = renderFrameParameters.GetAmbientColor();
		break;
	}
	case RPT_LIGHTS_NUM:
	{
		renderEffectParameter = renderFrameParameters.GetLightsNum();
		break;
	}
	case RPT_DIRECTIONAL_DIFFUSE_COLOR_ARRAY:
	{
		renderEffectParameter = renderFrameParameters.GetDirectionalLightDiffuseColors();
		break;
	}
	case RPT_DIRECTIONAL_SPECULAR_COLOR_ARRAY:
	{
		renderEffectParameter = renderFrameParameters.GetDirectionalLightSpecularColors();
		break;
	}
	case RPT_DIRECTIONAL_LIGHT_DIRECTION_ARRAY:
	{
		renderEffectParameter = renderFrameParameters.GetDirectionalLightDirections();
		break;
	}
	//µ„π‚‘¥
	case RPT_POINT_LIGHT_DIFFUSE_COLOR_ARRAY:
	{
		renderEffectParameter = renderFrameParameters.GetPointLightDiffuseColors();
		break;
	}
	case RPT_POINT_LIGHT_SPECULAR_COLOR_ARRAY:
	{
		renderEffectParameter = renderFrameParameters.GetPointLightSpecularColors();
		break;
	}
	case RPT_POINT_LIGHT_POSITION_ARRAY:
	{
		renderEffectParameter = renderFrameParameters.GetPointLightPositions();
		break;
	}
	case RPT_POINT_LIGHT_ATTENUATION_ARRAY:
	{
		renderEffectParameter = renderFrameParameters.GetPointLightAttenuations();
		break;
	}
	case RPT_AMBIENT_MATERIAL_COLOR:
	{
		renderEffectParameter = renderFrameParameters.GetMaterialAmbient();
		break;
	}
	case RPT_DIFFUSE_MATERIAL_COLOR:
	{
		renderEffectParameter = renderFrameParameters.GetMaterialDiffuse();
		break;
	}
	case RPT_SPECULAR_MATERIAL_COLOR:
	{
		renderEffectParameter = renderFrameParameters.GetMaterialSpecular();
		break;
	}
	case RPT_REFLECT_MATERIAL_COLOR:
	{
		renderEffectParameter = renderFrameParameters.GetMaterialSpecular();
		break;
	}
	default:
		break;
	}

}

HrRenderTechnique* HrRenderEffect::GetTechniqueByIndex(uint32 nIndex)
{
	if (0 <= nIndex && nIndex < m_vecRenderTechnique.size())
	{
		return m_vecRenderTechnique[nIndex];
	}
	return nullptr;
}

HrRenderTechnique* HrRenderEffect::GetTechniqueByName(const std::string& strTechniqueName)
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

HrRenderEffectParameter* HrRenderEffect::GetParameterByName(const std::string& strParamName)
{
	size_t const nHashName = HrHashValue(strParamName);
	for (const auto& item : m_vecRenderEffectParameter)
	{
		if (item->HashName() == nHashName)
		{
			return item;
		}
	}
	return nullptr;
}

HrRenderEffectStructParameter* HrRenderEffect::GetStructParameterByName(const std::string& strStructName)
{
	size_t const nHashName = HrHashValue(strStructName);
	for (const auto& item : m_vecRenderEffectStruct)
	{
		if (item->HashName() == nHashName)
		{
			return item;
		}
	}
	return nullptr;
}

