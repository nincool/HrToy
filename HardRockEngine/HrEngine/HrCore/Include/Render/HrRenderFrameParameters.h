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

		void SetLightsData(const HrSceneLightDataPtr& pLightData);
		const HrCameraPtr& GetActiveCamera();
		void SetCurViewPort(const HrViewPortPtr& pViewPort);
		const HrViewPortPtr& GetViewPort();

		//transform
		void SetTransform(HrTransform* pTransfrom);

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

		//Material
		void SetMaterial(HrMaterial* pMaterial);
		float4 GetMaterialAlbedo() const;
		float GetMaterialMetalness() const;
		float GetMaterialRoughness() const;

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

		mutable float4 m_fogColor;
		mutable float m_fogStart;
		mutable float m_fogRange;
	private:
		HrSceneLightDataPtr m_pLightsData;

		HrViewPortPtr m_pCurViewPort;
		
		HrSceneNode* m_pCurSceneNode;
		
		HrTransform* m_pTransfrom;
		HrMaterial* m_pMaterial;
	};
}

#endif



