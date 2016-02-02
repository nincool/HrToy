#ifndef _I_ASSET_H_
#define _I_ASSET_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IAsset : public GeneralAllocatedObject
	{
	public:
		virtual ~IAsset(){}
	};
}

#endif


