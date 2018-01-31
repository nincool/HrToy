#ifndef _HR_RENDERFRAMEPARAMETERS_H_
#define _HR_RENDERFRAMEPARAMETERS_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrMath/Include/HrMath.h"

namespace Hr
{
	class HrRenderFrameParameters
	{
	public:
		HrRenderFrameParameters();
		~HrRenderFrameParameters();

		void SetCurrentScene(const HrScenePtr& pScene);
		void SetCurrentCamera(const HrCameraPtr& pCamera);
		void SetCurrentRenderable(const HrRenderablePtr& rend);
		void SetCurrentMaterial(const HrMaterialPtr& pMaterial);

		const Matrix4& GetViewProjMatrix() const;

		bool WorldMatrixDirty() const { return m_bWorldMatrixDirty; }
		const Matrix4& GetWorldMatrix();
		bool InverseWRoldMatrixDirty() const { return m_bInverseWorldMatrixDirty; }
		const Matrix4& GetInverseWroldMatrix();
		bool InverseTransposeWorldMatrixDirty() const { return m_bInverseTransposeWorldMatrix; }
		const Matrix4& GetInverseTransposeWorldMatrix();
		bool WorldViewProjMatrixDirty() const { return m_bWorldViewProjMatrixDirty; }
		const Matrix4& GetWorldViewProjMatrix();

		const float3& GetCameraPosition();

		//lights
		const float4& GetAmbientColor();
		const int3& GetLightsNum();
		const std::vector<float3>& GetDirectionalLightDirections();
		const std::vector<float4>& GetDirectionalLightDiffuseColors();
		const std::vector<float4>& GetDirectionalLightSpecularColors();

		const std::vector<float4>& GetPointLightDiffuseColors();
		const std::vector<float4>& GetPointLightSpecularColors();
		const std::vector<float3>& GetPointLightPositions();
		const std::vector<float4>& GetPointLightAttenuations();

		//fog
		void SetFogParam(float4& fogColor, float fogStart, float fogRange);
		const void GetFogParam(float4& fogColor, float& fogStart, float& fogRange);

		//获取材质信息
		float4 GetMaterialAmbient() const;
		float4 GetMaterialDiffuse() const;
		float4 GetMaterialSpecular() const;
		float4 GetMaterialEmissive() const;
		float GetMaterialOpacity() const;
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

		//lights
		float4 m_ambientColor;
		int3 m_lightsNum;
		std::vector<float3> m_vecDirectionalDirections;
		std::vector<float4> m_vecDirectionalDiffuseColor;
		std::vector<float4> m_vecDirectionalSpecularColor;

		std::vector<float3> m_vecPointLightPositions;
		std::vector<float4> m_vecPointLightRangeAttenuation;
		std::vector<float4> m_vecPointLightDiffuseColors;
		std::vector<float4> m_vecPointLightSpecularColors;

		mutable float4 m_fogColor;
		mutable float m_fogStart;
		mutable float m_fogRange;
	private:
		HrScenePtr m_pCurrentScene;
		HrRenderablePtr m_pCurrentRenderable;
		HrMaterialPtr m_pCurrentMaterial;
		HrCameraPtr m_pCurrentCamera;
	
	};
}

#endif



