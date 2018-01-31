#ifndef _HR_VIEWPORT_H_
#define _HR_VIEWPORT_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrViewPort : public std::enable_shared_from_this<HrViewPort> 
	{
	public:
		HrViewPort(uint32 nTopX, uint32 nTopY, uint32 nWidth, uint32 nHeight, int nZOrder);
		~HrViewPort();

		uint32 GetTopX() const;
		uint32 GetTopY() const;
		uint32 GetWidth() const;
		uint32 GetHeight() const;
		int GetZOrder() const;

		void SetCamera(const HrCameraPtr& pCamera);
		const HrCameraPtr& GetCamera() const;
	private:
		HrCameraPtr m_pCamera;

		uint32 m_nTopX;
		uint32 m_nTopY;
		uint32 m_nWidth;
		uint32 m_nHeight;

		int m_nZOrder;
	};
}

#endif



