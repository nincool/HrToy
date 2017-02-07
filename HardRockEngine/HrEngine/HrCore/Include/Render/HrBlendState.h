#ifndef _HR_BLENDSTATE_H_
#define _HR_BLENDSTATE_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrBlendState
	{
	public:
		HrBlendState();
		virtual ~HrBlendState();

		virtual void Bind() = 0;
	};
}

#endif
