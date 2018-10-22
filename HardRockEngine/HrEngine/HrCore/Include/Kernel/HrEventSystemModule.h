#ifndef _HR_EVENTCORECOMPONENT_H_
#define _HR_EVENTCORECOMPONENT_H_

#include "HrCore/Include/Kernel/HrModule.h"

namespace Hr
{
	class HR_CORE_API HrEventSystemModule : public HrModule
	{
	public:
		HrEventSystemModule();
		~HrEventSystemModule();

		void AddEventCustomListener(const std::string& strEvent, const std::function<void(const HrEventPtr&)> &onEvent, void* pTarget);
		
		void AddEventListener(const HrEventListenerPtr& pEventListener, void* pTarget);

		//void RemoveEventCustomListener(const std::string& strEvent, )

		void RemoveEventListener(const HrEventListenerPtr& pEventListener);

		void DispatcherEvent(const HrEventPtr& pEvent);

	private:
		void RegisterListeners(const HrEventListenerPtr& pListener, void* pTarget);
	private:
		HrEventDispatcherPtr m_pEventDispatcher;

		std::unordered_map<size_t, std::list<HrEventListenerPtr> > m_mapRegisterListeners;
	};
}

#endif
