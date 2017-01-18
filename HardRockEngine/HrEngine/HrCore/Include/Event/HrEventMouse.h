#ifndef _HR_EVENTMOUSE_H_
#define _HR_EVENTMOUSE_H_

#include "HrCore/Include/Event/HrEvent.h"

namespace Hr
{
	class HrEventMouse : public HrEvent
	{
	public:
		enum class EnumMouseButtonID
		{
			MBI_UNKNOW,
			MBI_LEFT, 
			MBI_RIGHT,
			MBI_MIDDLE,
			MBI_BUTTON3,
			MBI_BUTTON4,
			MBI_BUTTON5,
			MBI_BUTTON6,
			MBI_BUTTON7
		};

		enum class EnumMouseEventFlag
		{
			MEF_PRESSED,
			MEF_RELEASED,
			MEF_MOVE,
		};
	public:
		HrEventMouse(EnumMouseButtonID id, EnumMouseEventFlag mouseEventFlag, float x, float y);
		~HrEventMouse();

		EnumMouseButtonID GetButtonID() { return m_buttonID; }
		EnumMouseEventFlag GetMouseEventFlag() { return m_mouseEventFlag; }
		float GetX() { return m_fX; }
		float GetY() { return m_fY; }

	public:
		static const std::string m_s_strEventListenerMouseID;
		static size_t m_s_nEventListenerMouseHashID;

	private:
		EnumMouseButtonID m_buttonID;
		EnumMouseEventFlag m_mouseEventFlag;
		float m_fX;
		float m_fY;
	};
}

#endif


