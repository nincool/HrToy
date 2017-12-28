#ifndef _HR_RENDERFRAME_H_
#define _HR_RENDERFRAME_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrRenderFrame
	{
	public:
		HrRenderFrame();
		virtual ~HrRenderFrame();

		void AttachRenderTarget(HrRenderTargetPtr& pRenderTarget);
		void DetachRenderTarget();

		void SetClearColor(const HrColor& color);
		void SetClearDepth(float fDepth);

		virtual void OnBind() = 0;
		virtual void OnUnBind() = 0;

		virtual void ClearTarget() = 0;
		virtual void ClearDepthStencil() = 0;

		uint32 GetLeft() const;
		uint32 GetBottom() const;
		uint32 GetWidht() const;
		uint32 GetHeight() const;

		void SetViewPort(const HrViewPortPtr& pViewPort);
		const HrViewPortPtr& GetViewPort() const;

		//todo test
		const HrRenderTargetPtr& GetRenderTarget()
		{
			return m_pRenderTarget;
		}
	protected:
		HrColor m_clearColor;
		float m_clearDepth;

		uint32 m_nLeft;
		uint32 m_nBottom;
		uint32 m_nWidth;
		uint32 m_nHeight;

		HrRenderTargetPtr m_pRenderTarget;
		HrViewPortPtr m_pCurViewPort;

	};
}


#endif
