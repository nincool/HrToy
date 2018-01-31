#include "Kernel/HrCoreComponentEvent.h"
#include "Event/HrEventDispatcher.h"


using namespace Hr;

HrCoreComponentEvent::HrCoreComponentEvent()
{
	m_pEventDispatcher = HrMakeSharedPtr<HrEventDispatcher>();
}

HrCoreComponentEvent::~HrCoreComponentEvent()
{
}

void HrCoreComponentEvent::AddEventListener(const HrEventListenerPtr& pEventListener, void* pTarget)
{
	m_pEventDispatcher->AddEventListener(pEventListener);

	RegisterListeners(pEventListener, pTarget);
}

void HrCoreComponentEvent::RemoveEventListener(const HrEventListenerPtr& pEventListener)
{
	m_pEventDispatcher->RemoveEventListener(pEventListener);
}

void HrCoreComponentEvent::DispatcherEvent(const HrEventPtr& pEvent)
{
	m_pEventDispatcher->DispatcherEvent(pEvent);
}

void HrCoreComponentEvent::AddEventCustomListener(const std::string& strEvent, const std::function<void(const HrEventPtr&)> &onEvent, void* pTarget)
{
	HrEventListenerPtr pEventCustomListener = HrMakeSharedPtr<HrEventListenerCustom>(strEvent, onEvent);
	m_pEventDispatcher->AddEventListener(pEventCustomListener);

	RegisterListeners(pEventCustomListener, pTarget);
}

void HrCoreComponentEvent::RegisterListeners(const HrEventListenerPtr& pListener, void* pTarget)
{
	size_t nHashID = boost::hash_value(pTarget);
	auto iteListeners = m_mapRegisterListeners.find(nHashID);
	if (iteListeners != m_mapRegisterListeners.end())
	{
		iteListeners->second.push_back(pListener);
	}
	else
	{
		std::list<HrEventListenerPtr> lisListeners;
		lisListeners.push_back(pListener);
		m_mapRegisterListeners[nHashID] = lisListeners;
	}
}

