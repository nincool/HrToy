#ifndef _HR_DEPTHSTENCIL_H_
#define _HR_DEPTHSTENCIL_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrDepthStencil
	{
	public:
		HrDepthStencil(uint32 nWidth, uint32 nHeight);
		virtual ~HrDepthStencil();

		uint32 GetWidth() const;
		uint32 GetHeight() const;
	protected:
		uint32 m_nWidth;
		uint32 m_nHeight;
	};
}

#endif
