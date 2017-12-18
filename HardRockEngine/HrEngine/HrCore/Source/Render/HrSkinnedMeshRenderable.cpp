#include "HrCore/Include/Render/HrSkinnedMeshRenderable.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/HrRenderFrameParameters.h"
#include "HrCore/Include/Asset/HrRenderEffect.h"
#include "HrCore/Include/Asset/HrPrefabModel.h"
#include "HrCore/Include/Asset/HrMesh.h"
#include "HrCore/Include/Asset/HrResourceManager.h"
#include "HrCore/Include/Asset/HrRenderEffectParameter.h"
#include "HrCore/Include/Kernel/HrDirector.h"

using namespace Hr;

HrSkinnedMeshRenderable::HrSkinnedMeshRenderable()
{
	m_pPrefebModel = nullptr;
	m_pSubMesh = nullptr;

	m_pRenderEffect = HrResourceManager::Instance()->GetDefaultRenderEffect();
	m_pRenderTechnique = m_pRenderEffect->GetTechniqueByName("Technique_1");
	BOOST_ASSERT(m_pRenderTechnique);
}

HrSkinnedMeshRenderable::~HrSkinnedMeshRenderable()
{
	m_pPrefebModel = nullptr;
	m_pSubMesh = nullptr;
}

HrRenderLayout* HrSkinnedMeshRenderable::GetRenderLayout()
{
	if (m_pSubMesh != nullptr)
	{
		return m_pSubMesh->GetRenderLayout();
	}
	return nullptr;
}

void HrSkinnedMeshRenderable::AttachSubMesh(HrSubMesh* pSubMesh)
{
	m_pSubMesh = pSubMesh;
}

bool HrSkinnedMeshRenderable::CanRender()
{
	if (m_pSubMesh == nullptr)
	{
		return false;
	}
	return true;
}

void HrSkinnedMeshRenderable::UpdateRenderFrameParametersImpl(HrRenderFrameParameters& renderFrameParameters)
{
	if (m_pSubMesh != nullptr)
	{
		HrMaterial* pMaterial = m_pSubMesh->GetMaterial();
		if (pMaterial != nullptr)
		{
			renderFrameParameters.SetCurrentMaterial(pMaterial);
		}
	}
}

void HrSkinnedMeshRenderable::UpdateEffectParametersImpl()
{
	if (m_pSubMesh != nullptr)
	{
		if (m_pSubMesh->GetTexture() != nullptr)
		{
			HrRenderEffectParameter* pTexParam = m_pRenderEffect->GetParameterByName("g_tex");
			if (pTexParam != nullptr)
			{
				HrTexture* pTexture = m_pSubMesh->GetTexture();
				if (pTexture == nullptr)
				{
					pTexture = HrResourceManager::Instance()->GetDefaultTexture();
				}
				*pTexParam = pTexture;
			}
		}
	}
}

