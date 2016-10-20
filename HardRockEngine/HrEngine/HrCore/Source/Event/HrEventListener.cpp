#include "Event/HrEventListener.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrEventListener::HrEventListener(std::string& strListenerID, const std::function<void(HrEvent*)>& callBack)
{
	SetEventListenerStringID(strListenerID);
	m_funcOnEvent = callBack;
}

HrEventListener::~HrEventListener()
{

}

void HrEventListener::SetEventListenerStringID(std::string strEventListenerID)
{
	m_strEventListenerID = strEventListenerID;
	m_nEventListenerID = HrHashValue(strEventListenerID);
}

std::string Hr::HrEventListener::GetEventListenerStringID()
{
	return m_strEventListenerID;
}

size_t HrEventListener::GetEventListenerHashID()
{
	return m_nEventListenerID;
}

void HrEventListener::OnEvent(HrEvent* pEvent)
{
	if (m_funcOnEvent)
	{
		m_funcOnEvent(pEvent);
	}
}












