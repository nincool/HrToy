#include "Event/HrEventDispatcher.h"
#include "Event/HrEventListener.h"
#include "Event/HrEvent.h"
#include "Event/HrEventListenerKeyboard.h"
#include "HrCore/Include/HrLog.h"
#include <algorithm> 

using namespace Hr;

HrEventDispatcher::HrEventDispatcher()
{

}

HrEventDispatcher::~HrEventDispatcher()
{

}

void HrEventDispatcher::AddEventListener(HrEventListenerPtr& pEventListener)
{
	HRASSERT(pEventListener, "AddEventListener Error");
	size_t nEventListenerID = pEventListener->GetEventListenerHashID();
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

void HrEventDispatcher::RemoveEventListener(HrEventListenerPtr& pEventListener)
{
	size_t nEventListenerID = pEventListener->GetEventListenerHashID();
	auto itemListeners = m_mapEventListener.find(nEventListenerID);
	if (itemListeners != m_mapEventListener.end())
	{
		itemListeners->second.erase(std::find_if(itemListeners->second.begin(), itemListeners->second.end(), [&pEventListener] (HrEventListenerPtr& pListener)
		{
			if (pListener == pEventListener)
			{
				return true;
			}
			return false;
		}));
	}
}

void HrEventDispatcher::DispatcherEvent(HrEvent* pEvent)
{
	if (pEvent->GetType() == HrEvent::EnumEventType::KEYBOARD)
	{
		DispatcherKeyBoardEvent(pEvent);
	}
}

void HrEventDispatcher::DispatcherKeyBoardEvent(HrEvent* pEvent)
{
	size_t nEventListenerID = HrEventListenerKeyboard::m_s_nEventListenerKeyboardHashID;
	auto& listListenersItem = m_mapEventListener.find(nEventListenerID);
	if (listListenersItem != m_mapEventListener.end())
	{
		for (auto& listItem : listListenersItem->second)
		{
			listItem->OnEvent(pEvent);
		}
	}
}

void HrEventDispatcher::DispatcherMouseEvent(HrEvent* pEvent)
{

}

size_t HrEventDispatcher::GetListenerID(HrEvent* pEvent)
{
	switch (pEvent->GetType())
	{
	case HrEvent::EnumEventType::KEYBOARD:
	{
		return HrEventListenerKeyboard::m_s_nEventListenerKeyboardHashID;
	}
	default:
	{
		HRASSERT(NULL, "Invalid type");
		return 0;
	}
	}
}

