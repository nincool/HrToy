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

	m_pRenderEffect = HrResourceManager::Instance()->GetDefaultRenderEffect();
	m_pRenderTechnique = m_pRenderEffect->GetTechnique("Basic");
}

HrSkinnedMeshRenderable::HrSkinnedMeshRenderable(HrPrefebModel* pPrefebModel)
{
	m_pPrefebModel = pPrefebModel;

	m_pRenderEffect = HrResourceManager::Instance()->GetDefaultRenderEffect();
	m_pRenderTechnique = m_pRenderEffect->GetTechnique("Basic");
}

HrSkinnedMeshRenderable::~HrSkinnedMeshRenderable()
{
}

HrRenderLayout* HrSkinnedMeshRenderable::GetRenderLayout()
{
	BOOST_ASSERT(m_pPrefebModel);

	return m_pPrefebModel->GetMesh()->GetRenderLayout();
}

void HrSkinnedMeshRenderable::AttachPrefebModel(HrPrefebModel* pPrefebModel)
{
	m_pPrefebModel = pPrefebModel;
}






