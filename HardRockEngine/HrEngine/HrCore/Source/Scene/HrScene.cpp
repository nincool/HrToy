#include "Scene/HrScene.h"
#include "Scene/HrTransform.h"
#include "Scene/HrSceneNode.h"
#include "Render/HrLight.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrLog.h"
#include "Asset/HrSceneObjectFactory.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

////////////////////////////////////////////////
//
////////////////////////////////////////////////

void HrSceneLightData::AddLight(const HrLightPtr& pLight)
{
	HrLight::EnumLightType lightType = pLight->LightType();
	m_arrLights[lightType].second.push_back(pLight);
}

void HrSceneLightData::DeleteLight(const HrLightPtr& pLight)
{
	HrLight::EnumLightType lightType = pLight->LightType();
	for (std::vector<HrLightPtr>::iterator ite = m_arrLights[lightType].second.begin(); ite != m_arrLights[lightType].second.end(); ++ite)
	{
		if (*ite == pLight)
		{
			m_arrLights[lightType].second.erase(ite);
			break;
		}
	}
}

size_t HrSceneLightData::GetLightsNum(HrLight::EnumLightType lightType)
{
	return m_arrLights[lightType].second.size();
}

const HrLightPtr& HrSceneLightData::GetLight(HrLight::EnumLightType lightType, uint32 nIndex)
{
	BOOST_ASSERT(0 <= nIndex && nIndex < m_arrLights[lightType].second.size());
	return m_arrLights[lightType].second[nIndex];
}

////////////////////////////////////////////////
//
////////////////////////////////////////////////

void HrSceneViewPortData::AddViewPort(const HrViewPortPtr& pViewPort)
{
	m_vecViewPorts.push_back(std::make_pair(SIS_ENABLE, pViewPort));
}

const std::vector< std::pair<EnumSceneItemStatus, HrViewPortPtr> >& HrSceneViewPortData::GetAllViewPorts()
{
	return m_vecViewPorts;
}

////////////////////////////////////////////////
//
////////////////////////////////////////////////

HrScene::HrScene()
{
	m_pLightsData = HrMakeSharedPtr<HrSceneLightData>();
	m_pViewPortData = HrMakeSharedPtr<HrSceneViewPortData>();
	m_pSceneRootNode = HrMakeSharedPtr<HrSceneNode>("Hr_Root");
}

HrScene::~HrScene()
{
	HRLOG("HrScene Destroy!");
}

void HrScene::OnEnter()
{
	m_pSceneRootNode->OnEnter();

	auto pAmbientLight = HrSceneObjectFactory::Instance()->CreateLightNode("Default Ambient Light", HrLight::LT_AMBIENT);
	m_pSceneRootNode->AddChild(pAmbientLight);
}

void HrScene::OnExit()
{
	ClearSceneNode();
}

void HrScene::ClearSceneNode()
{
	m_pSceneRootNode->RemoveChildren();
}

void HrScene::AddNode(const HrSceneNodePtr& pSceneNode)
{
	m_pSceneRootNode->AddChild(pSceneNode);
}

void HrScene::Update(float fDelta)
{
	m_pSceneRootNode->UpdateNode(fDelta);
}

void HrScene::FillRenderQueue(HrRenderQueuePtr& pRenderQueue)
{
	//���ҿ���
	m_pSceneRootNode->FindVisibleRenderable(pRenderQueue);
}

void HrScene::FindVisibleRenderables(const HrRenderQueueManagerPtr& pRenderQueueManager)
{
	m_pSceneRootNode->FindVisibleRenderables(pRenderQueueManager);
}

const std::shared_ptr<HrSceneLightData>& HrScene::GetLightsData()
{
	return m_pLightsData;
}

const std::shared_ptr<HrSceneViewPortData>& HrScene::GetViewPortsData()
{
	return m_pViewPortData;
}

const HrSceneNodePtr& HrScene::GetRootNode()
{
	return m_pSceneRootNode;
}
