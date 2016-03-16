#ifndef _HR_COLOR_H_
#define _HR_COLOR_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"
#include "HrMath/Include/HrMath.h"

namespace Hr
{
	class HR_CORE_API HrColor : public ResourceAllocatedObject
	{
	public:
		static const float4 F4Black;
		static const float4 F4White;
		static const float4 F4Red;
		static const float4 F4Green;
		static const float4 F4Blue;
		static const float4 F4Yellow;
		static const float4 F4Cyan;
		static const float4 F4Magenta;
		static const float4 F4Silver;
	};
}

#endif




