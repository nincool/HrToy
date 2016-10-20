#include "Event/HrEventListenerKeyboard.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

const std::string HrEventListenerKeyboard::m_s_strEventListenerKeyboardID = "_HR_EVENT_KEYBOARD_";
size_t HrEventListenerKeyboard::m_s_nEventListenerKeyboardHashID = HrHashValue(HrEventListenerKeyboard::m_s_strEventListenerKeyboardID);

HrEventListenerKeyboard::HrEventListenerKeyboard(std::function<void(HrEventKeyboard::EnumKeyCode, HrEvent*)>funcPressed
	, std::function<void(HrEventKeyboard::EnumKeyCode, HrEvent*)>funcReleased)
	:HrEventListener(const_cast<std::string&>(m_s_strEventListenerKeyboardID), nullptr)
{
	m_funcOnKeyPressed = funcPressed;
	m_funcOnKeyReleased = funcReleased;
}

HrEventListenerKeyboard::~HrEventListenerKeyboard()
{

}

void HrEventListenerKeyboard::OnEvent(HrEvent* pEvent)
{
	HrEventKeyboard* pEventKeyboard = CheckPointerCast<HrEventKeyboard>(pEvent);
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




