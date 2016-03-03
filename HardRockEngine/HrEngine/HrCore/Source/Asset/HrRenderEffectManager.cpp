#include "Asset/HrRenderEffectManager.h"
#include "Asset/HrRenderEffect.h"
#include "Render/IRenderFactory.h"
#include "HrDirector.h"
#include "HrLog.h"
#include <boost/cast.hpp>

using namespace Hr;

HrRenderEffectManager::HrRenderEffectManager()
{
	m_pShareShaderCompiler = HrDirector::GetInstance().GetRenderFactory()->CreateShaderCompiler();
}

HrRenderEffectManager::~HrRenderEffectManager()
{

}

void HrRenderEffectManager::InitResourceManager()
{
	HrRenderEffect* pRenderEffect = CreateEffect("BasicEffect", "Media\\HrShader\\BasicEffect.xml");
	pRenderEffect->Load();
}

IResource* HrRenderEffectManager::LoadResource(std::string strName, std::string strFilePath)
{
	HrRenderEffect* pRenderEffect = CreateEffect(strName, strFilePath);
	pRenderEffect->Load();

	return nullptr;
}

HrRenderEffect* HrRenderEffectManager::CreateEffect(std::string strName, std::string strFilePath)
{
	auto resItem = m_mapResource.find(strName);
	if (resItem != m_mapResource.end())
	{
		HRERROR(_T("HrRenderEffectManager CreateEffect Error! %s"), strName);
		return boost::polymorphic_downcast<HrRenderEffect*>(resItem->second);
	}
	HrRenderEffect* pRenderEffect = HR_NEW HrRenderEffect(strName, strFilePath);
	m_mapResource.insert(std::make_pair(strName, pRenderEffect));
	
	return pRenderEffect;
}

