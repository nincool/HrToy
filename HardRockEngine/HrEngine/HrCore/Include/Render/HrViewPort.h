#ifndef _HR_VIEWPORT_H_
#define _HR_VIEWPORT_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrViewPort : public std::enable_shared_from_this<HrViewPort> 
	{
	public:
		HrViewPort(float fTopX, float fTopY, float fWidth, float fHeight, int nZOrder);
		~HrViewPort();

		float GetTopX() const;
		float GetTopY() const;
		float GetWidth() const;
		float GetHeight() const;
		int GetZOrder() const;

		void SetCamera(const HrCameraPtr& pCamera);
		const HrCameraPtr& GetCamera() const;
	private:
		HrCameraPtr m_pCamera;

		float m_fTopX;
		float m_fTopY;
		float m_fWidth;
		float m_fHeight;

		int m_nZOrder;
	};
}

#endif



