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


using namespace Hr;

HrRenderEffect::HrRenderEffect()
{
	//m_pEffectStreamBuffer = MakeSharedPtr<HrStreamData>();
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
}

void HrRenderEffect::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFilePath = HrFileUtils::Instance()->GetFullPathForFileName(strFilePath);
	HRASSERT(!m_strFilePath.empty(), "HrRenderEffect::DeclareResource");
	m_strFileName = strFileName;
	m_resType = HrResource::RT_EFFECT;

	m_nHashID = HrHashValue(m_strFilePath);
}

bool HrRenderEffect::LoadImpl()
{
	HrStreamDataPtr pStreamData;
	HrShaderCompilerPtr pShaderCompiler = HrDirector::Instance()->GetRenderFactory()->CreateShaderCompiler();

	typedef boost::property_tree::ptree::value_type ptValue;
	boost::property_tree::ptree pt;
	boost::property_tree::read_xml(m_strFilePath, pt);

	for (ptValue& rootEffectValue : pt.get_child("effect"))
	{
		if (rootEffectValue.first == "effectfile")
		{
			m_strEffectFile = HrFileUtils::Instance()->GetFullPathForFileName(rootEffectValue.second.get_value<std::string>());
			
			//加载Shader文件
			pStreamData = HrFileUtils::Instance()->GetFileData(m_strEffectFile);
		}
		else if (rootEffectValue.first == "technique")
		{
			std::string strTechniqueName = rootEffectValue.second.get<std::string>("<xmlattr>.name");

			//创建Technique
			HrRenderTechnique* pRenderTechnique = HR_NEW HrRenderTechnique(strTechniqueName);
			m_vecRenderTechnique.push_back(pRenderTechnique);

			for (ptValue& nodeTechniqueValue : rootEffectValue.second)
			{
				if (nodeTechniqueValue.first == "pass")
				{
					std::string strPassName = nodeTechniqueValue.second.get<std::string>("<xmlattr>.name");

					//创建Pass
					HrRenderPass* pRenderPass = pRenderTechnique->AddPass(strPassName);
					for (ptValue& nodePassValue : nodeTechniqueValue.second)
					{
						if (nodePassValue.first == "param")
						{
							std::string strParamName = nodePassValue.second.get<std::string>("<xmlattr>.name");
							std::string strParamValue = nodePassValue.second.get<std::string>("<xmlattr>.value");
							if (strParamName == "vertex_shader")
							{
								HrStreamData effectStreamBuffer;
								pShaderCompiler->CompileShaderFromCode(m_strEffectFile, *pStreamData.get(), HrShader::ST_VERTEX_SHADER, strParamValue, effectStreamBuffer);
								pShaderCompiler->ReflectEffectParameters(effectStreamBuffer, strParamValue, HrShader::ST_VERTEX_SHADER);
								pShaderCompiler->StripCompiledCode(effectStreamBuffer);
								
								HrShader* pVertexShader = HrDirector::Instance()->GetRenderFactory()->CreateShader();
								pVertexShader->StreamIn(effectStreamBuffer, m_strEffectFile, strParamValue, HrShader::ST_VERTEX_SHADER);

								pRenderPass->SetShader(pVertexShader, HrShader::ST_VERTEX_SHADER);
								m_vecVertexShaders.push_back(pVertexShader);
							}
							else if (strParamName == "pixel_shader")
							{
								HrStreamData effectStreamBuffer;
								pShaderCompiler->CompileShaderFromCode(m_strEffectFile, *pStreamData.get(), HrShader::ST_PIXEL_SHADER, strParamValue, effectStreamBuffer);
								pShaderCompiler->ReflectEffectParameters(effectStreamBuffer, strParamValue, HrShader::ST_PIXEL_SHADER);
								pShaderCompiler->StripCompiledCode(effectStreamBuffer);

								HrShader* pPixelShader = HrDirector::Instance()->GetRenderFactory()->CreateShader();
								pPixelShader->StreamIn(effectStreamBuffer, m_strEffectFile, strParamValue, HrShader::ST_PIXEL_SHADER);

								pRenderPass->SetShader(pPixelShader, HrShader::ST_PIXEL_SHADER);
								m_vecPixelShaders.push_back(pPixelShader);
							}
						}
					}
				}
			}
		}
	}


	pShaderCompiler->CreateEffectParameters(m_vecRenderEffectParameter, m_vecRenderEffectStruct, m_vecRenderConstantBuffer);
	pShaderCompiler->BindParametersToShader(m_vecRenderEffectParameter, m_vecRenderEffectStruct, m_vecRenderConstantBuffer, m_vecVertexShaders);
	pShaderCompiler->BindParametersToShader(m_vecRenderEffectParameter, m_vecRenderEffectStruct, m_vecRenderConstantBuffer, m_vecPixelShaders);

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
	case RPT_AMBIENT_LIGHT_COLOR:
	{
		renderEffectParameter = HrColor::White.Value();
		break;
	}
	case RPT_DIFFUSE_LIGHT_COLOR:
	{
		renderEffectParameter = HrColor::White.Value();
		break;
	}
	case RPT_SPECULAR_LIGHT_COLOR:
	{
		renderEffectParameter = HrColor::White.Value();
		break;
	}
	case RPT_LIGHT_DIRECTION:
	{
		renderEffectParameter = float3(-1.0, -1.0, -1.0);
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
		renderEffectParameter = renderFrameParameters.GetMaterialSpecualr();
		break;
	}
	case RPT_REFLECT_MATERIAL_COLOR:
	{
		renderEffectParameter = renderFrameParameters.GetMaterialSpecualr();
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

