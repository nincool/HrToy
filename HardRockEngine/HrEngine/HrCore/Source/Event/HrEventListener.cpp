#include "Event/HrEventListener.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrEventListener::HrEventListener(const std::string& strEvent, const std::function<void(const HrEventPtr&)>& callBack)
{
	SetEvent(strEvent);
	m_funcOnEvent = callBack;
}

HrEventListener::~HrEventListener()
{

}

void HrEventListener::SetEvent(const std::string& strEvent)
{
	m_strEvent = strEvent;
	m_nEventHashID = HrHashValue(strEvent);
}

const std::string& HrEventListener::GetEvent()
{
	return m_strEvent;
}

size_t HrEventListener::GetEventHashID()
{
	return m_nEventHashID;
}

void HrEventListener::OnEvent(const HrEventPtr& pEvent)
{
	if (m_funcOnEvent)
	{
		m_funcOnEvent(pEvent);
	}
}

/////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////



HrEventListenerKeyboard::HrEventListenerKeyboard(std::function<void(HrEventKeyboard::EnumKeyCode, const HrEventPtr&)> funcPressed
	, std::function<void(HrEventKeyboard::EnumKeyCode, const HrEventPtr&)> funcReleased)
	:HrEventListener(const_cast<std::string&>(HrEventKeyboard::m_s_strEventKeyboardID), nullptr)
{
	m_funcOnKeyPressed = funcPressed;
	m_funcOnKeyReleased = funcReleased;
}

HrEventListenerKeyboard::~HrEventListenerKeyboard()
{

}

void HrEventListenerKeyboard::OnEvent(const HrEventPtr& pEvent)
{
	HrEventKeyboardPtr pEventKeyboard = HrCheckPointerCast<HrEventKeyboard>(pEvent);
	if (pEventKeyboard->GetPressed())
	{
		if (m_funcOnKeyPressed)
		{
			m_funcOnKeyPressed(pEventKeyboard->GetKeyCode(), pEvent);
		}
	}
	else
	{
		if (m_funcOnKeyReleased)
		{
			m_funcOnKeyReleased(pEventKeyboard->GetKeyCode(), pEvent);
		}
	}
}

////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////



HrEventListenerMouse::HrEventListenerMouse(std::function<void(HrEventMouse::EnumMouseButtonID, const HrEventPtr&)> funcPressed
	, std::function<void(HrEventMouse::EnumMouseButtonID, const HrEventPtr&)> funcReleased
	, std::function<void(const HrEventPtr&)> funcMove)
	: HrEventListener(const_cast<std::string&>(HrEventMouse::m_s_strEventMouseID), nullptr)
{
	m_funcOnMousePressed = funcPressed;
	m_funcOnMouseReleased = funcReleased;
	m_funcOnMouseMove = funcMove;
}

HrEventListenerMouse::~HrEventListenerMouse()
{

}

void HrEventListenerMouse::OnEvent(const HrEventPtr& pEvent)
{
	HrEventMousePtr pEventMouse = HrCheckPointerCast<HrEventMouse>(pEvent);
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

//////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////

HrEventListenerCustom::HrEventListenerCustom(const std::string& strEvent, const std::function<void(const HrEventPtr&)>& callBack)
	: HrEventListener(strEvent, callBack)
{
}

HrEventListenerCustom::~HrEventListenerCustom()
{
}

void HrEventListenerCustom::OnEvent(const HrEventPtr& pEvent)
{
	m_funcOnEvent(pEvent);
}
