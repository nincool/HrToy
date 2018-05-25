#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/HrRenderFrameParameters.h"
#include "HrCore/Include/Asset/HrRenderEffectParameter.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrRenderTechnique::HrRenderTechnique(std::string strTechniqueName)
{
	m_strTechniqueName = strTechniqueName;
	m_nHashName = HrHashValue(strTechniqueName);
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

void HrRenderTechnique::SetVertexInputSimantic(std::vector<std::pair<EnumVertexElementSemantic, uint32> >&& vecVertexInputSimantic)
{
	m_vecVertexInputSimantic.swap(vecVertexInputSimantic);
}

void HrRenderTechnique::SetVertexOutputSimantic(std::vector<std::pair<EnumVertexElementSemantic, uint32> >&& vecVertexOutputSimantic)
{
	m_vecVertexOutputSimantic.swap(vecVertexOutputSimantic);
}

bool HrRenderTechnique::IsVertexInputSimanticInit()
{
	return m_vecVertexInputSimantic.size() > 0;
}

bool HrRenderTechnique::IsVertexInputSimanticSame(const std::vector<std::pair<EnumVertexElementSemantic, uint32> >& vecVertexInputSimantic)
{
	if (m_vecVertexInputSimantic.size() == vecVertexInputSimantic.size())
	{
		for (size_t i = 0; i < m_vecVertexInputSimantic.size(); ++i)
		{
			if ((m_vecVertexInputSimantic[i].first != vecVertexInputSimantic[i].first) || (m_vecVertexInputSimantic[i].second != vecVertexInputSimantic[i].second))
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

