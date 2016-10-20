#include "Asset/HrRenderEffect.h"
#include "Asset/HrResourceLoader.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


using namespace Hr;

HrRenderEffect::HrRenderEffect(std::string strEffectName, std::string strFilePath)
	:m_strEffectName(strEffectName), m_strFilePath(strFilePath)
{
	m_nHashName = HrHashValue(m_strEffectName);
}

HrRenderEffect::~HrRenderEffect()
{
	for (auto& itemRT : m_vecRenderTechnique)
	{
		SAFE_DELETE(itemRT);
	}
	m_vecRenderTechnique.clear();
}

size_t HrRenderEffect::HashName()
{
	return m_nHashName;
}

void HrRenderEffect::Load()
{
	HrStreamData streamData;
	streamData.SetReadDataType(HrStreamData::RDT_TXT);

	typedef boost::property_tree::ptree::value_type ptValue;
	boost::property_tree::ptree pt;
	boost::property_tree::read_xml(m_strFilePath, pt);

	for (ptValue& rootEffectValue : pt.get_child("effect"))
	{
		if (rootEffectValue.first == "effectfile")
		{
			m_strEffectFile = rootEffectValue.second.get_value<std::string>();

			//加载Shader文件
			if (!HrResourceLoader::LoadFromFile(m_strEffectFile, streamData))
			{
				HRERROR("HrRenderEffect LoadFromFile Error! File[%s]", m_strEffectFile.c_str());
				return;
			}
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
					HrRenderPass* pRenderPass = pRenderTechnique->CreatePass(strPassName);
					for (ptValue& nodePassValue : nodeTechniqueValue.second)
					{
						if (nodePassValue.first == "param")
						{
							std::string strParamName = nodePassValue.second.get<std::string>("<xmlattr>.name");
							std::string strParamValue = nodePassValue.second.get<std::string>("<xmlattr>.value");
							if (strParamName == "vertex_shader")
							{
								std::string strVSEntryPoint = strParamValue;
								pRenderPass->SetVSEntryPoint(strVSEntryPoint);
							}
							else if (strParamName == "pixel_shader")
							{
								std::string strPSEntryPoint = strParamValue;
								pRenderPass->SetPSEntryPoint(strPSEntryPoint);
							}
						}
					}
					//创建shader
					pRenderPass->StreamIn(streamData);
				}
			}
		}

	}
}

void HrRenderEffect::Unload()
{

}

HrRenderTechnique* HrRenderEffect::GetTechnique(std::string strTechniqueName)
{
	size_t const nHashName = boost::hash_range(strTechniqueName.begin(), strTechniqueName.end());
	for (const auto& item : m_vecRenderTechnique)
	{
		if (item->GetHashName() == nHashName)
		{
			return item;
		}
	}

	return nullptr;
}

