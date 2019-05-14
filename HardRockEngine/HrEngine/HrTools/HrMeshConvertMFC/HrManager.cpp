#include "stdafx.h"
#include "HrManager.h"
#include "HrRenderApp.h"

using namespace Hr;
HrManager::HrManager(HrMeshView* pMeshView, HrRenderApp* pRenderApp, CPropertiesWnd* pPropertiesWnd)
{
	m_pConvertUtil = std::make_shared<HrConvertUtil>();
	m_pMeshClassView = pMeshView;
	m_pRenderApp = pRenderApp;
	m_pPropertiesWnd = pPropertiesWnd;
}

HrManager::~HrManager()
{
}

void HrManager::LoadOriginalMeshData(const std::string& strFileName)
{
	if (m_pConvertUtil->LoadOriginalData(strFileName))
	{
		m_pMeshClassView->FillClassView(m_pConvertUtil->GetModelDataInfo());
		m_pRenderApp->GetEditorScene()->DisplayMeshDataInScene(m_pConvertUtil->CreateSceneNode());
		m_pPropertiesWnd->SetSuggestUnitScale(m_pConvertUtil->GetSuggestScale());
	}
}

void HrManager::LoadHrMeshData(const std::string& strFileName)
{
	auto pModel = HrSceneObjectFactory::Instance()->CreateModelNode(strFileName);
	m_pRenderApp->GetEditorScene()->DisplayMeshDataInScene(pModel);
	HrMeshModelObjectPtr pPrefabModel = HrCheckPointerCast<HrMeshModelObject>(HrDirector::Instance()->GetResourceModule()->RetriveResource<HrMeshModel>(strFileName));
	const HrModelDataInfo& modelDataInfo = pPrefabModel->GetModelLoader()->GetModelDataInfo();
	m_pConvertUtil->SetModelDataInfo(modelDataInfo);
	m_pMeshClassView->FillClassView(modelDataInfo);

}

HrMeshView* HrManager::GetMeshView()
{
	return m_pMeshClassView;
}

HrRenderApp* HrManager::GetRenderApp()
{
	return m_pRenderApp;
}

CPropertiesWnd* HrManager::GetPropertiesWnd()
{
	return m_pPropertiesWnd;
}

std::shared_ptr<Hr::HrConvertUtil> Hr::HrManager::GetConvertUtil()
{
	return m_pConvertUtil;
}

