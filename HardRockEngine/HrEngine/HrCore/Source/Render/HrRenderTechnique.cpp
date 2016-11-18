#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrRenderTechnique::HrRenderTechnique(std::string strTechniqueName)
{
	m_strTechniqueName = strTechniqueName;
	m_nHashName = HrHashValue(strTechniqueName);
}

HrRenderTechnique::~HrRenderTechnique()
{
	for (auto& itemPass : m_vecPass)
	{
		SAFE_DELETE(itemPass);
	}
	m_vecPass.clear();
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

HrRenderPass* HrRenderTechnique::AddPass(std::string strPassName)
{
	HrRenderPass* pRenderPass = HR_NEW HrRenderPass(strPassName);
	m_vecPass.push_back(pRenderPass);

	return pRenderPass;
}




