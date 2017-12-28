#ifndef _HR_CORECOMPONENT_H_
#define _HR_CORECOMPONENT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/Include/HrComponent.h"

namespace Hr
{
	class HR_CORE_API HrCoreComponent : public HrComponent
	{
	public:
		HrCoreComponent();
		~HrCoreComponent();

		virtual bool InitComponent() override;
		virtual bool Update(float fDelta) override;
	};
}

#endif
