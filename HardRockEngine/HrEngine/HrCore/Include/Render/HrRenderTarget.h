#ifndef _HR_RENDERTARGET_H_
#define _HR_RENDERTARGET_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrRenderTarget 
	{
	public:
		HrRenderTarget();
		HrRenderTarget(const HrTexturePtr& pBackBuff);
		virtual ~HrRenderTarget();
	};

	class HR_CORE_API HrRenderTextureTarget : public HrRenderTarget
	{
	public:
		HrRenderTextureTarget();
		~HrRenderTextureTarget();


	};
}

#endif



