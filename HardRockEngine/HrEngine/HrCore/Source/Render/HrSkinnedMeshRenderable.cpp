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
	m_pSubMesh = nullptr;

	//m_pRenderEffect = HrResourceManager::Instance()->GetDefaultRenderEffect();
	//m_pRenderTechnique = m_pRenderEffect->GetTechniqueByName("Technique_1");
	//BOOST_ASSERT(m_pRenderTechnique);
}

HrSkinnedMeshRenderable::~HrSkinnedMeshRenderable()
{
	m_pSubMesh = nullptr;
}

const HrRenderLayoutPtr& HrSkinnedMeshRenderable::GetRenderLayout()
{
	if (m_pSubMesh != nullptr)
	{
		return m_pSubMesh->GetRenderLayout();
	}
	else
	{
		TRE("HrSkinnedMeshRenderable::GerRenderLayout Error!");
	}
}

void HrSkinnedMeshRenderable::AttachSubMesh(HrSubMeshPtr pSubMesh)
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

const HrMaterialPtr& HrSkinnedMeshRenderable::GetMaterial()
{
	return m_pSubMesh->GetMaterial();
}

