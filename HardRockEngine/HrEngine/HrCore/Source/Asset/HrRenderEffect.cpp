#include "Asset/HrRenderEffect.h"
#include "Asset/HrResourceLoader.h"
#include "Asset/HrResourceManager.h"
#include "Asset/HrShaderCompiler.h"
#include "HrCore/Include/Render/HrRenderFrameParameters.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/HrRenderFactory.h"
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
							std::string strVertexEnterPoint = passInfo["VERTEX_SHADER"].GetString();
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
							std::string strPixelEnterPoint = passInfo["PIXEL_SHADER"].GetString();
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
	case RPT_SHININESS:
	{
		renderEffectParameter = 10u;
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

HrRenderTechnique* HrRenderEffect::GetTechnique(const std::string& strTechniqueName)
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

