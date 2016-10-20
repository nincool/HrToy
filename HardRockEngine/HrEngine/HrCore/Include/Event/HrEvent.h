#ifndef _HR_EVENT_
#define _HR_EVENT_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrEvent
	{
	public:
		enum class EnumEventType
		{
			KEYBOARD,
			MOUSE,
		};
	public:
		HrEvent();
		virtual ~HrEvent();

		inline EnumEventType GetType() { return m_nType; };

	protected:
		EnumEventType m_nType;
	};
}

#endif


