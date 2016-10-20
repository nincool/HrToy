#include "Event/HrEventKeyboard.h"

using namespace Hr;

HrEventKeyboard::HrEventKeyboard(EnumKeyCode keyCode, bool isPressed)
{
	m_nType = HrEvent::EnumEventType::KEYBOARD;
	m_keyCode = keyCode;
	m_bIsPressed = isPressed;
}

HrEventKeyboard::~HrEventKeyboard()
{

}
