#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/HrRenderFrameParameters.h"
#include "HrCore/Include/Render/HrVertex.h"
#include "HrCore/Include/Asset/HrRenderEffectParameter.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrRenderTechnique::HrRenderTechnique(std::string strTechniqueName)
{
	m_strTechniqueName = strTechniqueName;
	m_nHashName = HrHashValue(strTechniqueName);
	m_nInputSimanticHash = 0;
}

HrRenderTechnique::~HrRenderTechnique()
{
	m_vecPass.clear();
}

size_t HrRenderTechnique::HashName()
{
	return m_nHashName;
}


const HrRenderPassPtr& HrRenderTechnique::GetRenderPass(uint32 nIndex)
{
	BOOST_ASSERT(nIndex < m_vecPass.size());

	return m_vecPass[nIndex];
}

HrRenderPassPtr HrRenderTechnique::AddPass(const std::string& strPassName)
{
	HrRenderPassPtr pRenderPass = HrMakeSharedPtr<HrRenderPass>(strPassName);
	m_vecPass.push_back(pRenderPass);

	return pRenderPass;
}

void HrRenderTechnique::SetVertexInputSimantic(std::vector<std::tuple<EnumVertexElementSemantic, uint32, EnumVertexElementType> >&& vecVertexInputSimantic)
{
	m_vecVertexInputSimantic.swap(vecVertexInputSimantic);
	m_nInputSimanticHash = CreateInputSimanticHashValue(m_vecVertexInputSimantic);
}

void HrRenderTechnique::SetVertexOutputSimantic(std::vector<std::tuple<EnumVertexElementSemantic, uint32, EnumVertexElementType> >&& vecVertexOutputSimantic)
{
	m_vecVertexOutputSimantic.swap(vecVertexOutputSimantic);
}

bool HrRenderTechnique::IsVertexInputSimanticInit()
{
	return m_vecVertexInputSimantic.size() > 0;
}

bool HrRenderTechnique::IsVertexInputSimanticSame(const std::vector<std::tuple<EnumVertexElementSemantic, uint32, EnumVertexElementType> >& vecVertexInputSimantic)
{
	if (m_vecVertexInputSimantic.size() == vecVertexInputSimantic.size())
	{
		for (size_t i = 0; i < vecVertexInputSimantic.size(); ++i)
		{
			if (m_vecVertexInputSimantic[i] != vecVertexInputSimantic[i])
			{
				return false;
			}
		}
	}

	return false;
}

size_t HrRenderTechnique::CreateInputSimanticHashValue(const std::vector<std::tuple<EnumVertexElementSemantic, uint32, EnumVertexElementType> >& vecVertexInputSimantic)
{
	size_t nInputSimanticHash = 0;
	for (size_t i = 0; i < vecVertexInputSimantic.size(); ++i)
	{
		HrHashCombine(nInputSimanticHash, std::get<0>(vecVertexInputSimantic[i]));
		HrHashCombine(nInputSimanticHash, std::get<1>(vecVertexInputSimantic[i]));
		HrHashCombine(nInputSimanticHash, std::get<2>(vecVertexInputSimantic[i]));
	}

	return nInputSimanticHash;
}


bool HrRenderTechnique::IsVertexElementMatch(const std::vector<HrVertexDataPtr>& vecVertexData)
{
	for (size_t i = 0; i < m_vecVertexInputSimantic.size(); ++i)
	{
		for (size_t j = 0; j < vecVertexData.size(); ++j)
		{
			const std::vector<HrVertexElement>& vecVertexElement = vecVertexData[j]->GetVertex()->GetVertexElement();
			for (size_t k = 0; k < vecVertexElement.size(); ++k)
			{
				if (vecVertexElement[k].m_elementSemantic == std::get<0>(m_vecVertexInputSimantic[i]))
				{
					goto NEXT_INPUT_SIMANTIC;
				}
			}
		}

		return false;

	NEXT_INPUT_SIMANTIC:
		continue;
	}

	return true;
}

