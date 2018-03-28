#include "HrCore/Include/Render/HrSkinnedMeshRenderable.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/HrRenderFrameParameters.h"
#include "HrCore/Include/Asset/HrRenderEffect.h"
#include "HrCore/Include/Asset/HrModel.h"
#include "HrCore/Include/Asset/HrMesh.h"
#include "HrCore/Include/Asset/HrResourceManager.h"
#include "HrCore/Include/Asset/HrRenderEffectParameter.h"
#include "HrCore/Include/Kernel/HrDirector.h"

using namespace Hr;

HrSkinnedMeshRenderable::HrSkinnedMeshRenderable()
{
	m_pSubMesh = nullptr;
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

void HrSkinnedMeshRenderable::SetSubMesh(const HrSubMeshPtr& pSubMesh)
{
	m_pSubMesh = pSubMesh;
}

