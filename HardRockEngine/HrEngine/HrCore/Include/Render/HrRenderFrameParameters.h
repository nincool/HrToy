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
		void SetCurrentRenderable(const IRenderable* rend);

		const Matrix4& GetWorldViewProjMatrix() const;
	protected:
		mutable Matrix4 mWorldViewMatrix;
		mutable Matrix4 mViewProjMatrix;
		mutable Matrix4 mWorldViewProjMatrix;
	private:
		const IRenderable* m_pCurrentRenderable;
		HrCamera* m_pCurrentCamera;

	};
}

#endif



