#ifndef _HR_VIEWPORT_H_
#define _HR_VIEWPORT_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrViewPortDeferredInfo
	{
	public:
		HrViewPortDeferredInfo();
		~HrViewPortDeferredInfo();

	private:
		HrTexturePtr m_pPositionSRV;
		HrTexturePtr m_pNormalSRV;
		HrTexturePtr m_pAlbedoSRV;

		
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
	private:
		HrCameraPtr m_pCamera;

		float m_fTopX;
		float m_fTopY;
		float m_fWidth;
		float m_fHeight;

		int m_nZOrder;


		//deferred
		
	};


}

#endif



