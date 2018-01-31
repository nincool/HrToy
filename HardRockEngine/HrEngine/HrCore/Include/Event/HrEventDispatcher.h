#ifndef _HR_EVENTDISPATCHER_H_
#define _HR_EVENTDISPATCHER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/include/HrSingleton.h"
#include "HrCore/Include/Event/HrEvent.h"
#include "HrCore/Include/Event/HrEventListener.h"

namespace Hr
{
	class HR_CORE_API  HrEventDispatcher : public HrSingleTon<HrEventDispatcher>, public boost::noncopyable
	{
	public:
		HrEventDispatcher();
		~HrEventDispatcher();

		void AddEventListener(const HrEventListenerPtr& pEventListener);

		void RemoveEventListener(const HrEventListenerPtr& pEventListener);

		void DispatcherEvent(const HrEventPtr& pEvent);
	private:
		void DispatcherKeyBoardEvent(const HrEventPtr& pEvent);
		void DispatcherMouseEvent(const HrEventPtr& pEvent);
		void DispatcherCustomEvent(const HrEventPtr& pEvent);

		size_t GetListenerID(const HrEventPtr& pEvent);

		void ForceAddEventListener(const HrEventListenerPtr& pEventListener);
		void ForceRemoveEventListener(const HrEventListenerPtr& pEventListener);

		void UpdateListeners();
	private:
		uint32 m_nEventListenerIDCounter;
		bool m_bDispatching;

		std::list<HrEventListenerPtr> m_lisReadyAddListeners;
		std::list<HrEventListenerPtr> m_lisReadyRemoveListeners;

		std::unordered_map<size_t, std::list<HrEventListenerPtr>> m_mapEventListener;

	};
}

#endif



