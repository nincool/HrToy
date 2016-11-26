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

void HrRenderTechnique::CollectShaderParameters()
{
	for (auto itemPass : m_vecPass)
	{
		itemPass->CollectShaderParameters(m_vecTechNeedParameter);
	}
	for (auto itemParameter : m_vecTechNeedParameter)
	{
		auto posItem = std::find_if(m_vecTechNeedConstBuffer.begin(), m_vecTechNeedConstBuffer.end(), [&](HrRenderEffectConstantBuffer* pConstBuffer)
		{
			if (pConstBuffer->HashName() == itemParameter->GetBindConstantBuffer()->HashName())
			{
				return true;
			}
			return false;
		});
		if (posItem == m_vecTechNeedConstBuffer.end())
		{
			m_vecTechNeedConstBuffer.push_back(itemParameter->GetBindConstantBuffer());
		}
	}
}

void HrRenderTechnique::UpdateEffectParams(HrRenderFrameParameters& renderFrameParameters)
{
	for (auto& item : m_vecTechNeedParameter)
	{
		switch (item->ParamType())
		{
		case RPT_WORLDVIEWPROJ_MATRIX:
		{
			if (renderFrameParameters.WorldViewProjMatrixDirty())
				*item = renderFrameParameters.GetWorldViewProjMatrix();
			break;
		}
		default:
			break;
		}
	}

	for (auto& item : m_vecTechNeedConstBuffer)
	{
		item->UpdateConstantBuffer();
	}
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

