#ifndef _HR_EVENTLISTENERKEYBOARD_H_
#define _HR_EVENTLISTENERKEYBOARD_H_

#include "HrCore/Include/Event/HrEventListener.h"
#include "HrCore/Include/Event/HrEventKeyboard.h"

namespace Hr
{
	class HR_CORE_API  HrEventListenerKeyboard : public HrEventListener
	{
	public:
		HrEventListenerKeyboard(std::function<void(HrEventKeyboard::EnumKeyCode, HrEvent*)>
			, std::function<void(HrEventKeyboard::EnumKeyCode, HrEvent*)>);
		~HrEventListenerKeyboard();


		virtual void OnEvent(HrEvent* pEvent) override;
	public:
		static const std::string m_s_strEventListenerKeyboardID;
		static size_t m_s_nEventListenerKeyboardHashID;

	protected:
		std::function<void(HrEventKeyboard::EnumKeyCode, HrEvent*)> m_funcOnKeyPressed;
		std::function<void(HrEventKeyboard::EnumKeyCode, HrEvent*)> m_funcOnKeyReleased;

	};
}



#endif



