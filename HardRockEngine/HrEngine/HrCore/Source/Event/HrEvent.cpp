#include "Event/HrEvent.h"

using namespace Hr;

const std::string HrEvent::scEventBeginUpdateScene = "_HR_EVENT_BEGINUPDATESCENE_";
const std::string HrEvent::scEventEndUpdateScene = "_HR_EVENT_ENDUPDATESCENE_";

HrEvent::HrEvent(const std::string& strEvent) : m_strEvent(strEvent), m_nHashID(boost::hash_value(strEvent))
{
}

HrEvent::~HrEvent()
{

}

////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////

const std::string HrEventKeyboard::m_s_strEventKeyboardID = "_HR_EVENT_KEYBOARD_";
size_t HrEventKeyboard::m_s_nEventKeyboardHashID = HrHashValue(HrEventKeyboard::m_s_strEventKeyboardID);

HrEventKeyboard::HrEventKeyboard(EnumKeyCode keyCode, bool isPressed) : HrEvent(m_s_strEventKeyboardID)
{
	m_nType = HrEvent::EnumEventType::KEYBOARD;
	m_keyCode = keyCode;
	m_bIsPressed = isPressed;
}

HrEventKeyboard::~HrEventKeyboard()
{

}

////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////

const std::string HrEventMouse::m_s_strEventMouseID = "_HR_EVENT_MOUSE_";
size_t HrEventMouse::m_s_nEventMouseHashID = HrHashValue(HrEventMouse::m_s_strEventMouseID);

HrEventMouse::HrEventMouse(EnumMouseButtonID id, EnumMouseEventFlag mouseEventFlag, float x, float y) : HrEvent(m_s_strEventMouseID)
{
	m_nType = HrEvent::EnumEventType::MOUSE;
	m_buttonID = id;
	m_mouseEventFlag = mouseEventFlag;
	m_fX = x;
	m_fY = y;
}

HrEventMouse::~HrEventMouse()
{

}

/////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////

HrEventCustom::HrEventCustom(const std::string& strEvent) : HrEvent(strEvent)
{
	m_nType = HrEvent::EnumEventType::CUSTOM;
	m_pData = nullptr;
}

HrEventCustom::HrEventCustom(const std::string& strEvent, void* pData) : HrEvent(strEvent)
{
	m_nType = HrEvent::EnumEventType::CUSTOM;
	m_pData = pData;
}

HrEventCustom::~HrEventCustom()
{
}

void HrEventCustom::SetData(void* pData)
{
	m_pData = pData;
}

void* HrEventCustom::GetData()
{
	return m_pData;
}

/////////////////////////////////////////////////////
//
////////////////////////////////////////////////////
