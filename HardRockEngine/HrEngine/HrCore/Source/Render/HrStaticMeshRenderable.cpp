#include "Render/HrStaticMeshRenderable.h"
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

HrStaticMeshRenderable::HrStaticMeshRenderable()
{

}

HrStaticMeshRenderable::HrStaticMeshRenderable(const HrSubMeshPtr& pSubMesh, const HrMaterialPtr& pMaterial)
{

}

HrStaticMeshRenderable::~HrStaticMeshRenderable()
{

}

const HrRenderLayoutPtr& HrStaticMeshRenderable::GetRenderLayout()
{
	if (m_pSubMesh != nullptr)
	{
		return m_pSubMesh->GetRenderLayout();
	}
	else
	{
		TRE("HrStaticMeshRenderable::GerRenderLayout Error!");
	}
}
