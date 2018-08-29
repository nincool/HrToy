#ifndef _HR_RENDERFRAMEPARAMETERS_H_
#define _HR_RENDERFRAMEPARAMETERS_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrLight.h"
#include "HrMath/Include/HrMath.h"


namespace Hr
{
	class HrRenderFrameParameters
	{
	public:
		HrRenderFrameParameters();
		~HrRenderFrameParameters();

		//todo
		void SetLightsData(const HrSceneLightDataPtr& pLightData);
		void SetCurrentCamera(const HrCameraPtr& pCamera);

		void SetCurrentSceneNode(const HrSceneNodePtr& pSceneNode);
		void SetCurrentRenderable(const HrRenderablePtr pRenderable);

		const Matrix4& GetViewProjMatrix() const;

		const Matrix4& GetWorldMatrix();
		const Matrix4& GetInverseWroldMatrix();
		const Matrix4& GetInverseTransposeWorldMatrix();
		const Matrix4& GetWorldViewProjMatrix();

		const float3& GetCameraPosition();

		//lights
		const float4 GetAmbientColor();
		const uint4 GetLightsNum();
		const int GetLightNum(HrLight::EnumLightType lightType);
		const float4 GetDirectionalLightDirection(int nLightIndex);
		const float4 GetDirectionalLightColor(int nLightIndex);

		const float4 GetPointLightColor(int nLightIndex);
		const float4 GetPointLightPosition(int nLightIndex);
		const float4 GetPointLightAttenuation(int nLightIndex);

		//fog
		void SetFogParam(float4& fogColor, float fogStart, float fogRange);
		const void GetFogParam(float4& fogColor, float& fogStart, float& fogRange);

		//获取材质信息
		float GetMaterialGlossiness() const;
		float4 GetMaterialAlbedo() const;
		float4 GetMaterialEmissive() const;
		float GetMaterialOpacity() const;

	private:
		void DirtyWorldMatrix();
		void DirtyViewMatrix();
	protected:
		mutable Matrix4 m_worldMatrix;
		bool m_bWorldMatrixDirty = true;
		mutable Matrix4 m_inverseWorldMatrix;
		bool m_bInverseWorldMatrixDirty = true;

		mutable Matrix4 m_inverseTransposeWorldMatrix;
		bool m_bInverseTransposeWorldMatrix = true;
		mutable Matrix4 m_worldViewProjMatrix;
		bool m_bWorldViewProjMatrixDirty = true;

		mutable float3 m_cameraPosition;
		bool m_bCameraDirty = true;

		mutable float4 m_fogColor;
		mutable float m_fogStart;
		mutable float m_fogRange;
	private:
		HrSceneLightDataPtr m_pLightsData;

		HrCameraPtr m_pCurrentCamera;
		HrRenderablePtr m_pRenderable;
		HrSceneNodePtr m_pSceneNode;
		
	};
}

#endif



