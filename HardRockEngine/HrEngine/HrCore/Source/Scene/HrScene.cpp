#include "Scene/HrScene.h"
#include "Scene/HrEntityNode.h"
#include "Kernel/HrDirector.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrScene::HrScene()
{
	m_arrLights[HrLight::LT_POINT] = std::pair<bool, std::vector<HrLightPtr> >();
	m_arrLights[HrLight::LT_DIRECTIONAL] = std::pair<bool, std::vector<HrLightPtr> >();
	m_arrLights[HrLight::LT_SPOTLIGHT] = std::pair<bool, std::vector<HrLightPtr> >();

	m_ambientLightColor = HrColor::White;

	m_pRootNode = HR_NEW HrRootNode();
}

HrScene::~HrScene()
{
	SAFE_DELETE(m_pRootNode);
}

void HrScene::OnEnter()
{
	m_pRootNode->OnEnter();
}

void HrScene::OnEnterDidFinish()
{
}

void HrScene::OnExit()
{
	ClearSceneNode();
}

void HrScene::ClearSceneNode()
{
	m_pRootNode->RemoveChildren();
}

void HrScene::AddSceneNode(HrSceneNode* pSceneNode)
{
	m_pRootNode->AddChild(pSceneNode);
}

void HrScene::Update()
{

}

void HrScene::FillRenderQueue(HrRenderQueuePtr& pRenderQueue)
{
	//²éÕÒ¿ÉÊÓ
	m_pRootNode->FindVisibleRenderable(pRenderQueue);
}

void HrScene::SetAmbientLight(const HrColor& ambientColor)
{
	m_ambientLightColor = ambientColor;
}

void HrScene::AddLight(const HrLightPtr& pLight)
{
	HrLight::EnumLightType lightType = pLight->LightType();
	m_arrLights[lightType].first = true;
	m_arrLights[lightType].second.push_back(pLight);
}

void HrScene::DeleteLight(const HrLightPtr& pLight)
{
	HrLight::EnumLightType lightType = pLight->LightType();
	for (std::vector<HrLightPtr>::iterator ite = m_arrLights[lightType].second.begin(); ite != m_arrLights[lightType].second.end(); ++ite)
	{
		if (*ite == pLight)
		{
			m_arrLights[lightType].first = true;
			m_arrLights[lightType].second.erase(ite);
			break;
		}
	}
}

size_t HrScene::GetLightsNum(HrLight::EnumLightType lightType)
{
	return m_arrLights[lightType].second.size();
}

const HrLightPtr& HrScene::GetLight(HrLight::EnumLightType lightType, uint32 nIndex)
{
	BOOST_ASSERT(0 <= nIndex && nIndex < m_arrLights[lightType].second.size());
	return m_arrLights[lightType].second[nIndex];
}

bool HrScene::IsLightsDirty(HrLight::EnumLightType lightType)
{
	return m_arrLights[lightType].first;
}

void HrScene::GetDirectionalLightsParam(std::vector<float3>& vecDirectionalLightDirections, std::vector<float4>& vecDirectionalDiffuse, std::vector<float4>& vecDirectionalSpecular)
{
	if (m_arrLights[HrLight::LT_DIRECTIONAL].first)
	{
		m_vecDirectionalDiffuseColor.clear();
		m_vecDirectionalSpecularColor.clear();
		for (size_t i = 0; i < m_arrLights[HrLight::LT_DIRECTIONAL].second.size(); ++i)
		{
			m_vecDirectionalLightsDirections.push_back(m_arrLights[HrLight::LT_DIRECTIONAL].second[i]->GetDirection());
			m_vecDirectionalDiffuseColor.push_back(m_arrLights[HrLight::LT_DIRECTIONAL].second[i]->GetDiffuse().Value());
			m_vecDirectionalSpecularColor.push_back(m_arrLights[HrLight::LT_DIRECTIONAL].second[i]->GetSpecular().Value());
		}
		m_arrLights[HrLight::LT_DIRECTIONAL].first = false;
	}
	vecDirectionalLightDirections = m_vecDirectionalLightsDirections;
	vecDirectionalDiffuse = m_vecDirectionalDiffuseColor;
	vecDirectionalSpecular = m_vecDirectionalSpecularColor;
}

float4 HrScene::GetAmbientColor()
{
	return m_ambientLightColor.Value();
}
