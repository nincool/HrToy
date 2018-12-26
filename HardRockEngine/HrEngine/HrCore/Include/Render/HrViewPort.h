#ifndef _HR_VIEWPORT_H_
#define _HR_VIEWPORT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Render/HrDataDefine.h"

namespace Hr
{
	class HrViewPortDeferredInfo
	{
	public:
		HrViewPortDeferredInfo();
		~HrViewPortDeferredInfo();
		
		//GBuffers
		std::array<bool, EnumGBufferType::GBT_MAXNUM> m_arrGBuffersEnable;
		std::array<HrTexturePtr, EnumGBufferType::GBT_MAXNUM> m_arrGBuffers;
		std::array<HrRenderTargetPtr, EnumGBufferType::GBT_MAXNUM> m_arrGBufferRenderTargets;
	};

	class HR_CORE_API HrViewPort : public std::enable_shared_from_this<HrViewPort> 
	{
	public:
		HrViewPort(const HrCameraPtr& pCamera);
		HrViewPort(const HrCameraPtr& pCamera, float fTopX, float fTopY, float fWidth, float fHeight, int nZOrder);
		~HrViewPort();

		void SetViewPortAttribute(float fTopX, float fTopY, float fWidth, float fHeight, int nZOrder);

		float GetTopX() const;
		float GetTopY() const;
		float GetWidth() const;
		float GetHeight() const;
		int GetZOrder() const;

		const HrCameraPtr& GetCamera() const;
		const HrViewPortDeferredInfoPtr& GetViewPortDeferredInfo() const;
	private:
		HrCameraPtr m_pCamera;

		float m_fTopX;
		float m_fTopY;
		float m_fWidth;
		float m_fHeight;

		int m_nZOrder;
	
		HrViewPortDeferredInfoPtr m_pViewProtDeferredInfo;
		
	};


}

#endif



