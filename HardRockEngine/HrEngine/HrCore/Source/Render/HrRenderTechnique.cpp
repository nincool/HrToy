#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderPass.h"

using namespace Hr;

HrRenderTechnique::HrRenderTechnique(std::string strTechniqueName)
{
	m_strTechniqueName = strTechniqueName;
	
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

