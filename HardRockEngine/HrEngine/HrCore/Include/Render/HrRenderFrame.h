#ifndef _HR_RENDERFRAME_H_
#define _HR_RENDERFRAME_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrRenderFrame
	{
	public:
		enum EnumRenderTargetLayer
		{
			RTL_0,
			RTL_1,
			RTL_2,
			RTL_3,
			RTL_MAX = 8,
		};
	public:
		HrRenderFrame(uint32 nWidth, uint32 nHeight);
		virtual ~HrRenderFrame();

		uint32 GetFrameWidth();
		uint32 GetFrameHeight();

		virtual void AttachRenderTarget(EnumRenderTargetLayer attachLayer, HrRenderTargetPtr& pRenderTarget);
		virtual void DetachRenderTarget(EnumRenderTargetLayer attachLayer);

		virtual void OnBind(const HrRenderPtr& pRender) = 0;
		virtual void OnUnBind() = 0;

		virtual void ClearTarget() = 0;
		virtual void ClearDepthStencil() = 0;

		virtual void Present() = 0;

		void SetClearColor(const HrColor& color);
		void SetClearDepth(float fDepth);
		
		void AddViewPort(const HrViewPortPtr& pViewPort);
		const HrViewPortPtr& GetViewPort(uint32 zOrder) const;
		const std::map<uint32, HrViewPortPtr>& GetAllViewPorts();

		HrDepthStencilPtr GetDepthStencil();
	protected:
		uint32 m_nWidth;
		uint32 m_nHeight;

		HrColor m_clearColor;
		float m_clearDepth;
		float m_clearStencil;

		std::map<uint32, HrViewPortPtr> m_mapViewPorts;
		std::array<HrRenderTargetPtr, RTL_MAX> m_arrRenderTargets;
		HrDepthStencilPtr m_pDepthStencil;
	};
}


#endif
