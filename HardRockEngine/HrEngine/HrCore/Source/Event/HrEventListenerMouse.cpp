#include "Event/HrEventListenerMouse.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

const std::string HrEventListenerMouse::m_s_strEventListenerMouseID = "_HR_EVENT_MOUSE_";
size_t HrEventListenerMouse::m_s_nEventListenerMouseHashID = HrHashValue(HrEventListenerMouse::m_s_strEventListenerMouseID);

HrEventListenerMouse::HrEventListenerMouse(std::function<void(HrEventMouse::EnumMouseButtonID, HrEvent*)> funcPressed
	, std::function<void(HrEventMouse::EnumMouseButtonID, HrEvent*)> funcReleased
	, std::function<void(HrEvent*)> funcMove)
	: HrEventListener(const_cast<std::string&>(m_s_strEventListenerMouseID), nullptr)
{
	m_funcOnMousePressed = funcPressed;
	m_funcOnMouseReleased = funcReleased;
	m_funcOnMouseMove = funcMove;
}

HrEventListenerMouse::~HrEventListenerMouse()
{

}

void HrEventListenerMouse::OnEvent(HrEvent* pEvent)
{
	HrEventMouse* pEventMouse = HrCheckPointerCast<HrEventMouse>(pEvent);
	switch (pEventMouse->GetMouseEventFlag())
	{
	case HrEventMouse::EnumMouseEventFlag::MEF_PRESSED:
		if (m_funcOnMousePressed)
			m_funcOnMousePressed(pEventMouse->GetButtonID(), pEvent);
		break;
	case HrEventMouse::EnumMouseEventFlag::MEF_RELEASED:
		if (m_funcOnMouseReleased)
			m_funcOnMouseReleased(pEventMouse->GetButtonID(), pEvent);
		break;
	case HrEventMouse::EnumMouseEventFlag::MEF_MOVE:
		if (m_funcOnMouseMove)
			m_funcOnMouseMove(pEvent);
		break;
	}
}




