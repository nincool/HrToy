#ifndef _I_SHADER_H_
#define _I_SHADER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IShader : public RenderSysAllocatedObject
	{
	public:
		virtual ~IShader(){};

		virtual void Bind(IRender* pRender) = 0;
		virtual void UnBind(IRender* pRender) = 0;
	};
}

#endif



