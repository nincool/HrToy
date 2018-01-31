#include "Event/HrEventDispatcher.h"
#include "Event/HrEventListener.h"
#include "Event/HrEvent.h"
#include "HrCore/Include/Kernel/HrLog.h"
#include <algorithm> 

using namespace Hr;

HrEventDispatcher::HrEventDispatcher()
{
	m_bDispatching = false;
}

HrEventDispatcher::~HrEventDispatcher()
{

}

void HrEventDispatcher::AddEventListener(const HrEventListenerPtr& pEventListener)
{
	HRASSERT(pEventListener, "AddEventListener Error");

	if (!m_bDispatching)
	{
		ForceAddEventListener(pEventListener);
	}
	else
	{
		m_lisReadyAddListeners.push_back(pEventListener);
	}

}

void HrEventDispatcher::RemoveEventListener(const HrEventListenerPtr& pEventListener)
{
	if (m_bDispatching)
	{
		ForceRemoveEventListener(pEventListener);
	}
	else
	{
		m_lisReadyRemoveListeners.push_back(pEventListener);
	}

}

void HrEventDispatcher::DispatcherEvent(const HrEventPtr& pEvent)
{
	m_bDispatching = true;

	if (pEvent->GetType() == HrEvent::EnumEventType::KEYBOARD)
	{
		DispatcherKeyBoardEvent(pEvent);
	}
	else if (pEvent->GetType() == HrEvent::EnumEventType::MOUSE)
	{
		DispatcherMouseEvent(pEvent);
	}
	else if (pEvent->GetType() == HrEvent::EnumEventType::CUSTOM)
	{
		DispatcherCustomEvent(pEvent);
	}
	else
	{
		BOOST_ASSERT_MSG(false, "unknow event type");
	}

	m_bDispatching = false;

	UpdateListeners();
}

void HrEventDispatcher::DispatcherKeyBoardEvent(const HrEventPtr& pEvent)
{
	size_t nEventListenerID = HrEventKeyboard::m_s_nEventKeyboardHashID;
	auto listListenersItem = m_mapEventListener.find(nEventListenerID);
	if (listListenersItem != m_mapEventListener.end())
	{
		for (auto& listItem : listListenersItem->second)
		{
			listItem->OnEvent(pEvent);
		}
	}
}

void HrEventDispatcher::DispatcherMouseEvent(const HrEventPtr& pEvent)
{
	size_t nEventListenerID = HrEventMouse::m_s_nEventMouseHashID;
	auto listListenersItem = m_mapEventListener.find(nEventListenerID);
	if (listListenersItem != m_mapEventListener.end())
	{
		for (auto& listItem : listListenersItem->second)
		{
			listItem->OnEvent(pEvent);
		}
	}
}

void HrEventDispatcher::DispatcherCustomEvent(const HrEventPtr& pEvent)
{
	size_t nEventListenerID = pEvent->GetHashID();
	auto listListenersItem = m_mapEventListener.find(nEventListenerID);
	if (listListenersItem != m_mapEventListener.end())
	{
		for (auto& listItem : listListenersItem->second)
		{
			listItem->OnEvent(pEvent);
		}
	}
}

size_t HrEventDispatcher::GetListenerID(const HrEventPtr& pEvent)
{
	switch (pEvent->GetType())
	{
	case HrEvent::EnumEventType::KEYBOARD:
	{
		return HrEventKeyboard::m_s_nEventKeyboardHashID;
	}
	default:
	{
		HRASSERT(NULL, "Invalid type");
		return 0;
	}
	}
}

void HrEventDispatcher::ForceAddEventListener(const HrEventListenerPtr& pEventListener)
{
	size_t nEventListenerID = pEventListener->GetEventHashID();
	auto itemListeners = m_mapEventListener.find(nEventListenerID);
	if (itemListeners == m_mapEventListener.end())
	{
		std::list<HrEventListenerPtr> lisEventListener;
		lisEventListener.push_back(pEventListener);
		m_mapEventListener[nEventListenerID] = lisEventListener;
	}
	else
	{
		itemListeners->second.push_back(pEventListener);
	}
}

void HrEventDispatcher::ForceRemoveEventListener(const HrEventListenerPtr& pEventListener)
{
	size_t nEventListenerID = pEventListener->GetEventHashID();
	auto itemListeners = m_mapEventListener.find(nEventListenerID);
	if (itemListeners != m_mapEventListener.end())
	{
		itemListeners->second.erase(std::find_if(itemListeners->second.begin(), itemListeners->second.end(), [&pEventListener](HrEventListenerPtr& pListener)
		{
			if (pListener == pEventListener)
			{
				return true;
			}
			return false;
		}));
	}
}

void HrEventDispatcher::UpdateListeners()
{
	for (auto& iteLis : m_lisReadyAddListeners)
	{
		ForceAddEventListener(iteLis);
	}
	for (auto& iteLis : m_lisReadyRemoveListeners)
	{
		ForceRemoveEventListener(iteLis);
	}
}

