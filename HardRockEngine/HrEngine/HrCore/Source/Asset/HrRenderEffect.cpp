#include "Asset/HrRenderEffect.h"
#include "Asset/HrResourceLoader.h"
#include "Asset/HrResourceManager.h"
#include "Asset/HrShaderCompiler.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/HrRenderFactory.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "Kernel/HrFileUtils.h"
#include "Kernel/HrDirector.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


using namespace Hr;

HrRenderEffect::HrRenderEffect()
{
	m_pEffectStreamBuffer = MakeSharedPtr<HrStreamData>();
}

HrRenderEffect::~HrRenderEffect()
{
	for (auto& itemRT : m_vecRenderTechnique)
	{
		SAFE_DELETE(itemRT);
	}
	m_vecRenderTechnique.clear();
}

void HrRenderEffect::DeclareResource(const std::string& strFileName, const std::string& strFilePath)
{
	m_strFilePath = HrFileUtils::Instance()->GetFullPathForFileName(strFilePath);
	HRASSERT(!m_strFilePath.empty(), "HrRenderEffect::DeclareResource");
	m_strFileName = strFileName;
	m_resType = HrResource::RT_EFFECT;

	m_nHashID = HrHashValue(m_strFilePath);
}

HrRenderTechnique* HrRenderEffect::GetTechnique(std::string strTechniqueName)
{
	size_t const nHashName = HrHashValue(strTechniqueName);
	for (const auto& item : m_vecRenderTechnique)
	{
		if (item->GetHashName() == nHashName)
		{
			return item;
		}
	}

	return nullptr;
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
								pShaderCompiler->CompileShaderFromCode(m_strEffectFile, *pStreamData.get(), HrShader::ST_VERTEX_SHADER, strParamValue, *m_pEffectStreamBuffer.get());
								

								HrShader* pVertexShader = HrDirector::Instance()->GetRenderFactory()->CreateShader();
								pVertexShader->StreamIn(*m_pEffectStreamBuffer.get(), m_strEffectFile, HrShader::ST_VERTEX_SHADER);

								pRenderPass->SetShader(pVertexShader, HrShader::ST_VERTEX_SHADER);
								m_vecVertexShaders.push_back(pVertexShader);
							}
							else if (strParamName == "pixel_shader")
							{
								//HrShader* pPixelShader = HrDirector::Instance()->GetRenderFactory()->CreateShader();
								//pPixelShader->StreamIn(*pStreamData.get(), m_strEffectFile, strParamValue, HrShader::ST_PIXEL_SHADER);

								//pRenderPass->SetShader(pPixelShader, HrShader::ST_VERTEX_SHADER);
								//m_vecVertexShaders.push_back(pPixelShader);
							}
						}
					}
				}
			}
		}
	}
	return true;
}

bool HrRenderEffect::UnloadImpl()
{
	return true;
}

bool HrRenderEffect::CreateEffectParameters()
{
	return true;
}

bool HrRenderEffect::CreateEffectConstParameters()
{
	return true;
}

