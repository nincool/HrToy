#include "Asset/HrRenderEffectManager.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrResource.h"
#include "Asset/HrResourceManager.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include <boost/cast.hpp>
#include <boost/functional/hash.hpp>

using namespace Hr;

HrRenderEffectManager::HrRenderEffectManager()
{
}

HrRenderEffectManager::~HrRenderEffectManager()
{
	for (auto& itemRes : m_mapResource)
	{
		SAFE_DELETE(itemRes.second);
	}
	m_mapResource.clear();
}

void HrRenderEffectManager::InitResourceManager()
{
	LoadResource("BasicEffect", "Media\\HrShader\\HrBasicEffect.xml");
}

HrResource* HrRenderEffectManager::LoadResource(std::string strName, std::string strFilePath)
{
	HrRenderEffect* pRenderEffect = CreateEffect(strName, strFilePath);
	pRenderEffect->Load();

	return nullptr;
}

HrRenderEffect* HrRenderEffectManager::CreateEffect(std::string strName, std::string strFilePath)
{
	size_t nHashName = boost::hash_range(strName.begin(), strName.end());
	auto resItem = m_mapResource.find(nHashName);
	if (resItem != m_mapResource.end())
	{
		HRERROR(_T("HrRenderEffectManager CreateEffect Error! %s"), strName);
		return boost::polymorphic_downcast<HrRenderEffect*>(resItem->second);
	}
	HrRenderEffect* pRenderEffect = HR_NEW HrRenderEffect(strName, strFilePath);
	m_mapResource.insert(std::make_pair(nHashName, pRenderEffect));
	
	return pRenderEffect;
}

HrResource* HrRenderEffectManager::GetResource(std::string strName)
{
	size_t nHashName = boost::hash_range(strName.begin(), strName.end());
	auto resItem = m_mapResource.find(nHashName);
	if (resItem == m_mapResource.end())
	{
		return nullptr;
	}
	return resItem->second;
}

HrRenderEffect* HrRenderEffectManager::GetRenderEffect(std::string strName)
{
	size_t nHashName = boost::hash_range(strName.begin(), strName.end());
	auto resItem = m_mapResource.find(nHashName);
	if (resItem == m_mapResource.end())
	{
		return nullptr;
	}

	return boost::polymorphic_downcast<HrRenderEffect*>(resItem->second);
}

