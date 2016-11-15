#include "HrCore/Include/Render/HrRenderModel.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Asset/HrRenderEffect.h"
#include "HrCore/Include/Asset/HrPrefebModel.h"
#include "HrCore/Include/Asset/HrMesh.h"
#include "HrCore/Include/Asset/HrResourceManager.h"

using namespace Hr;

HrRenderModel::HrRenderModel()
{
	m_pPrefebModel = nullptr;

	m_pRenderEffect = HrResourceManager::Instance()->GetDefaultRenderEffect();
	m_pRenderTechnique = m_pRenderEffect->GetTechnique("Basic");
}

HrRenderModel::HrRenderModel(HrPrefebModel* pPrefebModel)
{
	m_pPrefebModel = pPrefebModel;

	m_pRenderEffect = HrResourceManager::Instance()->GetDefaultRenderEffect();
	m_pRenderTechnique = m_pRenderEffect->GetTechnique("Basic");
}

HrRenderModel::~HrRenderModel()
{
}

HrRenderLayout* HrRenderModel::GetRenderLayout()
{
	BOOST_ASSERT(m_pPrefebModel);

	return m_pPrefebModel->GetMesh()->GetRenderLayout();
}

void HrRenderModel::AttachPrefebModel(HrPrefebModel* pPrefebModel)
{
	m_pPrefebModel = pPrefebModel;
}






