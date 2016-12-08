#include "HrCore/Include/Render/HrSkinnedMeshRenderable.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Asset/HrRenderEffect.h"
#include "HrCore/Include/Asset/HrPrefebModel.h"
#include "HrCore/Include/Asset/HrMesh.h"
#include "HrCore/Include/Asset/HrResourceManager.h"

using namespace Hr;

HrSkinnedMeshRenderable::HrSkinnedMeshRenderable()
{
	m_pPrefebModel = nullptr;
	m_pSubMesh = nullptr;

	m_pRenderEffect = HrResourceManager::Instance()->GetDefaultRenderEffect();
	m_pRenderTechnique = m_pRenderEffect->GetTechnique("Basic");
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

void HrSkinnedMeshRenderable::AttachPrefebModel(HrPrefebModel* pPrefebModel)
{
	m_pPrefebModel = pPrefebModel;

	m_pRenderEffect = HrResourceManager::Instance()->GetDefaultRenderEffect();
	m_pRenderTechnique = m_pRenderEffect->GetTechnique("Basic");
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

		}
	}
}

