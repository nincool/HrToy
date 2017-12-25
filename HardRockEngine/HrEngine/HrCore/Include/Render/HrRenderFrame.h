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

	protected:
		uint32 m_nLefth;
		uint32 m_nTop;
		uint32 m_nWidth;
		uint32 m_nHeight;

		HrViewPortPtr m_pCurViewPort;
	};
}


#endif
