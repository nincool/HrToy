#ifndef _HR_CORECOMPONENT_H_
#define _HR_CORECOMPONENT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/Include/HrComponent.h"

namespace Hr
{
	class HR_CORE_API HrModule : public HrComponent
	{
	public:
		HrModule();
		~HrModule();

		virtual bool InitComponent() override;
		virtual bool Update(float fDelta) override;
	};
}

#endif
