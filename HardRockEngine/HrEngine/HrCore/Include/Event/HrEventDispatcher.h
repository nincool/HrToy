#ifndef _HR_EVENTDISPATCHER_H_
#define _HR_EVENTDISPATCHER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/include/HrSingleton.h"

namespace Hr
{
	class HR_CORE_API  HrEventDispatcher : public HrSingleTon<HrEventDispatcher>
	{
	public:
		HrEventDispatcher();
		~HrEventDispatcher();

		void AddEventListener(HrEventListenerPtr& pEventListener);

		void RemoveEventListener(HrEventListenerPtr& pEventListener);

		void DispatcherEvent(HrEvent* pEvent);

	private:
		void DispatcherKeyBoardEvent(HrEvent* pEvent);
		void DispatcherMouseEvent(HrEvent* pEvent);

		size_t GetListenerID(HrEvent* pEvent);
	private:
		uint32 m_nEventListenerIDCounter;
		std::unordered_map<size_t, std::list<HrEventListenerPtr>> m_mapEventListener;

	};
}

#endif



