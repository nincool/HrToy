#ifndef _HR_EVENTLISTENERMOUSE_H_
#define _HR_EVENTLISTENERMOUSE_H_

#include "HrCore/Include/Event/HrEventListener.h"
#include "HrCore/Include/Event/HrEventMouse.h"

namespace Hr
{
	class HR_CORE_API  HrEventListenerMouse : public HrEventListener
	{
	public:
		HrEventListenerMouse(std::function<void(HrEventMouse::EnumMouseButtonID, HrEvent*)>
			, std::function<void(HrEventMouse::EnumMouseButtonID, HrEvent*)>
			, std::function<void(HrEvent*)>);
		~HrEventListenerMouse();


		virtual void OnEvent(HrEvent* pEvent) override;
	public:
		static const std::string m_s_strEventListenerMouseID;
		static size_t m_s_nEventListenerMouseHashID;

	protected:
		std::function<void(HrEventMouse::EnumMouseButtonID, HrEvent*)> m_funcOnMousePressed;
		std::function<void(HrEventMouse::EnumMouseButtonID, HrEvent*)> m_funcOnMouseReleased;
		std::function<void(HrEvent*)> m_funcOnMouseMove;

	};
}


#endif



