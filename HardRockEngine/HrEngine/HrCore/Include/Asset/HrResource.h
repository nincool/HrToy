#ifndef _HR_RESOURCE_H_
#define _HR_RESOURCE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HrResource
	{
	public:
		virtual ~HrResource(){}

		virtual size_t HashName() = 0;

		virtual void Load() = 0;
		virtual void Unload() = 0;

	};
}

#endif


