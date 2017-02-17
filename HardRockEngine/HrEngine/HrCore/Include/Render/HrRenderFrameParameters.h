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

		void SetCurrentCamera(HrCamera* pCamera);
		void SetCurrentRenderable(const HrRenderable* rend);
		void SetCurrentMaterial(const HrMaterial* pMaterial);

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

		//fog
		void SetFogParam(float4& fogColor, float fogStart, float fogRange);
		const void GetFogParam(float4& fogColor, float& fogStart, float& fogRange);

		//获取材质信息
		float4 GetMaterialAmbient() const;
		float4 GetMaterialDiffuse() const;
		float4 GetMaterialSpecualr() const;
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
	
		mutable float4 m_fogColor;
		mutable float m_fogStart;
		mutable float m_fogRange;
	private:
		const HrRenderable* m_pCurrentRenderable;
		const HrMaterial* m_pCurrentMaterial;
		HrCamera* m_pCurrentCamera;
	
	};
}

#endif



