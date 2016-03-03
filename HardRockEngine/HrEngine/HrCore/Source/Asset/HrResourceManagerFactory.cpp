#include "Asset/HrResourceManagerFactory.h"
#include "Asset/HrRenderEffectManager.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrResourceManagerFactoryPtr HrResourceManagerFactory::m_s_pUniqueResManagerFactory;

HrResourceManagerFactory& HrResourceManagerFactory::GetInstance()
{
	if (!m_s_pUniqueResManagerFactory)
	{
		m_s_pUniqueResManagerFactory = MakeUniquePtr<HrResourceManagerFactory>();
	}
	return *m_s_pUniqueResManagerFactory;
}

void HrResourceManagerFactory::ReleaseInstance()
{
	if (m_s_pUniqueResManagerFactory)
	{
		m_s_pUniqueResManagerFactory->Release();
	}
	m_s_pUniqueResManagerFactory.reset();
}

HrResourceManagerFactory::HrResourceManagerFactory()
{
}

HrResourceManagerFactory::~HrResourceManagerFactory()
{

}

void HrResourceManagerFactory::Release()
{
	for (auto& item : m_mapResManager)
	{
		HR_DELETE item.second;
	}
	m_mapResManager.clear();
}

void HrResourceManagerFactory::CreateResourceManager()
{
	HrRenderEffectManager* pEffectManager = HR_NEW HrRenderEffectManager();
	pEffectManager->InitResourceManager();
	m_mapResManager[RFT_EFFECTMANAGER] = pEffectManager;
}

HrRenderEffectManager* HrResourceManagerFactory::GetEffectManager()
{
	return GetResourceManager<HrRenderEffectManager>(RFT_EFFECTMANAGER);
}
