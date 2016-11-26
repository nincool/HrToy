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

		const Matrix4& GetViewProjMatrix() const;
		bool WorldViewProjMatrixDirty() const { return m_bWorldViewProjMatrixDirty; }
		const Matrix4& GetWorldViewProjMatrix();

		
	protected:
		mutable Matrix4 m_worldMatrix;
		bool m_bWorldMatrixDirty;

		mutable Matrix4 m_worldViewProjMatrix;
		bool m_bWorldViewProjMatrixDirty;

	private:
		const HrRenderable* m_pCurrentRenderable;
		HrCamera* m_pCurrentCamera;
	};
}

#endif



