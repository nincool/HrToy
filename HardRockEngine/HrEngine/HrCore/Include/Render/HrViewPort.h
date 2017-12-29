#ifndef _HR_VIEWPORT_H_
#define _HR_VIEWPORT_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrViewPort 
	{
	public:
		HrViewPort(float fLeft, float fTop, float fWidth, float fHeight, int nZOrder, const HrCameraPtr& pCamera);
		~HrViewPort();

		float GetLeft()
		{
			return m_fLeft;
		}
		float GetTop()
		{
			return m_fTop;
		}
		float GetWidth()
		{
			return m_fWidth;
		}
		float GetHeight()
		{
			return m_fHeight;
		}
		int GetZOrder()
		{
			return m_nZOrder;
		}
		HrCameraPtr GetCamera()
		{
			return m_pCamera;
		}


		void Release()
		{
			delete this;
		}
	private:
		HrCameraPtr m_pCamera;

		float m_fLeft;
		float m_fTop;
		float m_fWidth;
		float m_fHeight;
		int m_nZOrder;
	};
}

#endif



