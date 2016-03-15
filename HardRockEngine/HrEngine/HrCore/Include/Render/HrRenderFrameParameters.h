#ifndef _HR_RENDERFRAMEPARAMETERS_H_
#define _HR_RENDERFRAMEPARAMETERS_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"
#include "HrMath/Include/HrMath.h"

namespace Hr
{
	class HrRenderFrameParameters : public RenderSysAllocatedObject
	{
	public:
		HrRenderFrameParameters();
		~HrRenderFrameParameters();

		void SetCurrentRenderable(const IRenderable* rend);

		const Matrix4& GetWorldViewProjMatrix() const;
	protected:
		mutable Matrix4 mWorldViewMatrix;
		mutable Matrix4 mViewProjMatrix;
		mutable Matrix4 mWorldViewProjMatrix;
	private:
		const IRenderable* m_pCurrentRenderable;

		//≤‚ ‘…„œÒª˙
		HrCameraPtr m_pShareCamera;
	};
}

#endif



