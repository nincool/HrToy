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
		itemPass->CollectShaderParameters(m_vecTechNeedParameter, m_vecTechNeedStruct);
	}
	for (auto& itemParameter : m_vecTechNeedParameter)
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
	for (auto& itemStruct : m_vecTechNeedStruct)
	{
		for (uint32 nIndex = 0; nIndex < itemStruct->ElementNum(); ++nIndex)
		{
			auto posItem = std::find_if(m_vecTechNeedConstBuffer.begin(), m_vecTechNeedConstBuffer.end(), [&](HrRenderEffectConstantBuffer* pConstBuffer)
			{
				if (pConstBuffer->HashName() == itemStruct->ParameterByIndex(nIndex)->GetBindConstantBuffer()->HashName())
				{
					return true;
				}
				return false;
			});
			if (posItem == m_vecTechNeedConstBuffer.end())
			{
				m_vecTechNeedConstBuffer.push_back(itemStruct->ParameterByIndex(nIndex)->GetBindConstantBuffer());
			}
		}
	}
}

void HrRenderTechnique::UpdateEffectParams(HrRenderFrameParameters& renderFrameParameters)
{
	for (auto& item : m_vecTechNeedStruct)
	{
		for (uint32 nIndex = 0; nIndex < item->ElementNum(); ++nIndex)
		{
			UpdateOneEffectParameter(*(item->ParameterByIndex(nIndex)), renderFrameParameters);
		}
	}
	for (auto& item : m_vecTechNeedParameter)
	{
		UpdateOneEffectParameter(*item, renderFrameParameters);
	}

	for (auto& item : m_vecTechNeedConstBuffer)
	{
		item->UpdateConstantBuffer();
	}
}

void HrRenderTechnique::UpdateOneEffectParameter(HrRenderEffectParameter& renderEffectParameter, HrRenderFrameParameters& renderFrameParameters)
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

