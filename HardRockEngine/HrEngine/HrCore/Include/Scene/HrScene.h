#ifndef _HR_SCENE_H_
#define _HR_SCENE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrLight.h"

namespace Hr
{

	/////////////////////////////////////////////////////////
	//
	/////////////////////////////////////////////////////////
	enum EnumSceneItemStatus
	{
		SIS_ENABLE,
		SIS_DISABLE,
	};

	class HrSceneLightData
	{
	public:
		void AddLight(const HrLightPtr& pLight);
		void DeleteLight(const HrLightPtr& pLight);
		
		size_t GetLightsNum(HrLight::EnumLightType lightType);
		const HrLightPtr& GetLight(HrLight::EnumLightType lightType, uint32 nIndex);
	protected:
		std::array<std::pair<EnumSceneItemStatus, std::vector<HrLightPtr> >, HrLight::LT_LIGHTTYPE_NUM> m_arrLights;
	};

	/////////////////////////////////////////////////////////
	//
	/////////////////////////////////////////////////////////

	class HrSceneViewPortData
	{
	public:
		void AddViewPort(const HrViewPortPtr& pViewPort);

		const std::vector< std::pair<EnumSceneItemStatus, HrViewPortPtr> >& GetAllViewPorts();
	protected:
		std::vector< std::pair<EnumSceneItemStatus, HrViewPortPtr> > m_vecViewPorts;
	};

	/////////////////////////////////////////////////////////
	//
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

		virtual void Update(float fDelta);
		virtual void FillRenderQueue(HrRenderQueuePtr& pRenderQueue);
		virtual void FindVisibleRenderables(const HrRenderQueueManagerPtr& pRenderQueueManager);

		const HrSceneNodePtr& GetRootNode();

		const std::shared_ptr<HrSceneLightData>& GetLightsData();
		const std::shared_ptr<HrSceneViewPortData>& GetViewPortsData();
	protected:
		HrSceneNodePtr m_pSceneRootNode;

		std::shared_ptr<HrSceneLightData> m_pLightsData;
		std::shared_ptr<HrSceneViewPortData> m_pViewPortData;

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

