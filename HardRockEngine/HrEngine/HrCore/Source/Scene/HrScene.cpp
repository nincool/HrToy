#include "Scene/HrScene.h"
#include "Scene/HrEntityNode.h"
#include "Scene/HrTransform.h"
#include "Render/HrLight.h"
#include "Kernel/HrDirector.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrScene::HrScene()
{
	m_arrLights[HrLight::LT_POINT] = std::pair<bool, std::vector<HrLightPtr> >();
	m_arrLights[HrLight::LT_DIRECTIONAL] = std::pair<bool, std::vector<HrLightPtr> >();
	m_arrLights[HrLight::LT_SPOTLIGHT] = std::pair<bool, std::vector<HrLightPtr> >();

	m_ambientLightColor = HrMath::MakeColor(120.0f, 120.0f, 120.0f, 255.0f);

	m_pSceneRootNode = HrMakeSharedPtr<HrRootNode>();
	//m_pRootNode = HR_NEW HrRootNode();
}

HrScene::~HrScene()
{
	//SAFE_DELETE(m_pRootNode);
}

void HrScene::OnEnter()
{
	m_pSceneRootNode->OnEnter();
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
	m_pSceneRootNode->RemoveChildren();
}

void HrScene::AddSceneNode(const HrSceneNodePtr& pSceneNode)
{
	m_pSceneRootNode->AddChild(pSceneNode);
}

void HrScene::Update()
{

}

void HrScene::FillRenderQueue(HrRenderQueuePtr& pRenderQueue)
{
	//²éÕÒ¿ÉÊÓ
	m_pSceneRootNode->FindVisibleRenderable(pRenderQueue);
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
			HrLightPtr& pLight = m_arrLights[HrLight::LT_DIRECTIONAL].second[i];
			m_vecDirectionalLightsDirections.push_back(pLight->GetDirection());
			m_vecDirectionalDiffuseColor.push_back(pLight->GetDiffuse().Value());
			m_vecDirectionalSpecularColor.push_back(pLight->GetSpecular().Value());
		}
		m_arrLights[HrLight::LT_DIRECTIONAL].first = false;
	}
	vecDirectionalLightDirections = m_vecDirectionalLightsDirections;
	vecDirectionalDiffuse = m_vecDirectionalDiffuseColor;
	vecDirectionalSpecular = m_vecDirectionalSpecularColor;
}

void HrScene::GetPointLightsParam(std::vector<float3>& vecPointLightPositions, std::vector<float4>& vecRangeAttenuation, std::vector<float4>& vecPointDiffuse, std::vector<float4>& vecPointSpecular)
{
	if (m_arrLights[HrLight::LT_POINT].first)
	{
		m_vecPointLightPositions.clear();
		m_vecRangeAttenuation.clear();
		m_vecPointDiffuse.clear();
		m_vecPointSpecular.clear();
		for (size_t i = 0; i < m_arrLights[HrLight::LT_POINT].second.size(); ++i)
		{
			HrLightPtr& pLight = m_arrLights[HrLight::LT_POINT].second[i];
			m_vecPointLightPositions.push_back(pLight->GetAttachLightNode()->GetTransform()->GetWorldPosition());
			
			float4 attenuation;
			attenuation[0] = pLight->GetAttenuationRange();
			attenuation[1] = pLight->GetAttenuation0();
			attenuation[2] = pLight->GetAttenuation1();
			attenuation[3] = pLight->GetAttenuation2();

			m_vecRangeAttenuation.push_back(attenuation);
			m_vecPointDiffuse.push_back(pLight->GetDiffuse().Value());
			m_vecPointSpecular.push_back(pLight->GetDiffuse().Value());
		}
		m_arrLights[HrLight::LT_POINT].first = false;
	}
	vecPointLightPositions = m_vecPointLightPositions;
	vecRangeAttenuation = m_vecRangeAttenuation;
	vecPointDiffuse = m_vecPointDiffuse;
	vecPointSpecular = m_vecPointSpecular;
}

float4 HrScene::GetAmbientColor()
{
	return m_ambientLightColor.Value();
}

HrSceneNode* HrScene::GetSceneNodeByName(const std::string& strNodeName)
{
	if (strNodeName.empty())
	{
		return nullptr;
	}

	return m_pSceneRootNode->GetNodeByNameFromHierarchy(strNodeName);
}
