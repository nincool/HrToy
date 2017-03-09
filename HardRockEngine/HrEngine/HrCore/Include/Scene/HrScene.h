#ifndef _HR_SCENE_H_
#define _HR_SCENE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrLight.h"

namespace Hr
{
	class HR_CORE_API HrScene 
	{
	public:
		HrScene();
		virtual ~HrScene();

		virtual void OnEnter();
		virtual void OnEnterDidFinish();
		virtual void OnExit();

		virtual void AddSceneNode(HrSceneNode* pSceneNode);
		virtual void ClearSceneNode();

		virtual void Update();
		virtual void FillRenderQueue(HrRenderQueuePtr& pRenderQueue);

		void SetAmbientLight(const HrColor& ambientColor);

		void AddLight(const HrLightPtr& pLight);
		void DeleteLight(const HrLightPtr& pLight);
		size_t GetLightsNum(HrLight::EnumLightType lightType);
		const HrLightPtr& GetLight(HrLight::EnumLightType lightType, uint32 nIndex);

		//Scene Lights
		float4 GetAmbientColor();
		bool IsLightsDirty(HrLight::EnumLightType lightType);
		void GetDirectionalLightsParam(std::vector<float3>& vecDirectionalLightDirections, std::vector<float4>& vecDirectionalDiffuse, std::vector<float4>& vecDirectionalSpecular);
	protected:
		HrSceneNode* m_pRootNode;

		std::array<std::pair<bool, std::vector<HrLightPtr> >, HrLight::LT_LIGHTTYPE_NUM> m_arrLights;
		std::vector<float3> m_vecDirectionalLightsDirections;
		std::vector<float4> m_vecDirectionalDiffuseColor;
		std::vector<float4> m_vecDirectionalSpecularColor;

		HrColor m_ambientLightColor;
	};
}

#endif

