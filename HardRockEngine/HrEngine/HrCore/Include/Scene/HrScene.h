#ifndef _HR_SCENE_H_
#define _HR_SCENE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrLight.h"

namespace Hr
{
	class HrSceneLightData
	{
	public:
		void AddLight(const HrLightPtr& pLight);
		
		void DeleteLight(const HrLightPtr& pLight);
		
		size_t GetLightsNum(HrLight::EnumLightType lightType);
		
		const HrLightPtr& GetLight(HrLight::EnumLightType lightType, uint32 nIndex);

	protected:
		std::array<std::pair<bool, std::vector<HrLightPtr> >, HrLight::LT_LIGHTTYPE_NUM> m_arrLights;
	};

	/////////////////////////////////////////////////////////

	class HR_CORE_API HrScene 
	{
	public:
		HrScene();
		virtual ~HrScene();

		virtual void OnEnter();
		virtual void OnExit();

		virtual void AddNode(const HrSceneNodePtr& pSceneNode);
		virtual void ClearSceneNode();

		virtual void Update();
		virtual void FillRenderQueue(HrRenderQueuePtr& pRenderQueue);

		std::shared_ptr<HrSceneLightData>& GetLightsData();

		//bool IsLightsDirty(HrLight::EnumLightType lightType);
		//void GetDirectionalLightsParam(std::vector<float3>& vecDirectionalLightDirections, std::vector<float4>& vecDirectionalDiffuse, std::vector<float4>& vecDirectionalSpecular);
		//void GetPointLightsParam(std::vector<float3>& vecPointLightPositions, std::vector<float4>& vecRangeAttenuation, std::vector<float4>& vecPointDiffuse, std::vector<float4>& vecPointSpecular);

		//HrSceneNode* GetSceneNodeByName(const std::string& strNodeName);

	protected:
		HrSceneNodePtr m_pSceneRootNode;

		std::shared_ptr<HrSceneLightData> m_pLightsData;	

		std::vector<float3> m_vecDirectionalLightsDirections;
		std::vector<float4> m_vecDirectionalDiffuseColor;
		std::vector<float4> m_vecDirectionalSpecularColor;

		std::vector<float3> m_vecPointLightPositions;
		std::vector<float4> m_vecRangeAttenuation;
		std::vector<float4> m_vecPointDiffuse;
		std::vector<float4> m_vecPointSpecular;

	};
}

#endif

