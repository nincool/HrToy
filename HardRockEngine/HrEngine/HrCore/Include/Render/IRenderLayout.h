#ifndef _I_RENDERLAYOUT_H_
#define _I_RENDERLAYOUT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IRenderLayout : public RenderSysAllocatedObject
	{
	public:

		virtual ~IRenderLayout(){}

		virtual uint32 GetVertextSize() = 0;

		virtual void BindVertextBuffer(IGraphicsBuffer * pGraphicsBuffer, HrVertext* pVertext) = 0;
	};
}

#endif