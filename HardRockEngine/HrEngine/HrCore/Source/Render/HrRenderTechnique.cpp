#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderPass.h"
#include <boost/functional/hash.hpp>

using namespace Hr;

HrRenderTechnique::HrRenderTechnique(std::string strTechniqueName)
{
	m_strTechniqueName = strTechniqueName;
	m_nHashName = boost::hash_range(m_strTechniqueName.begin(), m_strTechniqueName.end());
}

size_t HrRenderTechnique::GetHashName()
{
	return m_nHashName;
}

void HrRenderTechnique::UpdateEffectParams(HrRenderFrameParameters& renderFrameParameters)
{
	m_vecPass[0]->UpdateShaderParams(renderFrameParameters);
}

HrRenderPass* HrRenderTechnique::GetRenderPass(uint32 nIndex)
{
	BOOST_ASSERT(nIndex < m_vecPass.size());

	return m_vecPass[nIndex];
}

HrRenderPass* HrRenderTechnique::CreatePass(std::string strPassName)
{
	HrRenderPass* pRenderPass = HR_NEW HrRenderPass(strPassName);
	m_vecPass.push_back(pRenderPass);

	return pRenderPass;
}




