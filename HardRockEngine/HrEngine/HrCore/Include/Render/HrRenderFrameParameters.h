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

	protected:
		mutable Matrix4 m_worldMatrix;
		bool m_bWorldMatrixDirty = true;
		mutable Matrix4 m_inverseWorldMatrix;
		bool m_bInverseWorldMatrixDirty = true;

		mutable Matrix4 m_inverseTransposeWorldMatrix;
		bool m_bInverseTransposeWorldMatrix = true;
		mutable Matrix4 m_worldViewProjMatrix;
		bool m_bWorldViewProjMatrixDirty = true;

	private:
		const HrRenderable* m_pCurrentRenderable;
		const HrMaterial* m_pCurrentMaterial;
		HrCamera* m_pCurrentCamera;
	
	};
}

#endif



