#include "HrCore/Include/Render/HrMeshRenderable.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/HrRenderFrameParameters.h"
#include "HrCore/Include/Asset/HrRenderEffect.h"
#include "HrCore/Include/Asset/HrMesh.h"
#include "HrCore/Include/Asset/HrResourceManager.h"
#include "HrCore/Include/Asset/HrRenderEffectParameter.h"
#include "HrCore/Include/Kernel/HrDirector.h"

using namespace Hr;

HrStaticMeshRenderable::HrStaticMeshRenderable()
{
}

HrStaticMeshRenderable::HrStaticMeshRenderable(const HrSubMeshPtr& pSubMesh)
{
	m_pSubMesh = pSubMesh;
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



////////////////////////////////////////////////////
//
////////////////////////////////////////////////////

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



//////////////////////////////////////////////////////////////////