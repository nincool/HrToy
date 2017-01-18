#include "Event/HrEventMouse.h"

using namespace Hr;

HrEventMouse::HrEventMouse(EnumMouseButtonID id, EnumMouseEventFlag mouseEventFlag, float x, float y)
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

