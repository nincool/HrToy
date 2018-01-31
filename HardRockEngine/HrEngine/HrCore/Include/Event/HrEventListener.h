#ifndef _HR_EVENTLISTENER_H_
#define _HR_EVENTLISTENER_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Event/HrEvent.h"

namespace Hr
{
	class HR_CORE_API  HrEventListener
	{
	public:
		HrEventListener(const std::string& strEvent, const std::function<void(const HrEventPtr&)>& callBack);
		virtual ~HrEventListener();

		void SetEvent(const std::string& strEventListenerID);
		const std::string& GetEvent();
		size_t GetEventHashID();

		virtual void OnEvent(const HrEventPtr& pEvent);
	protected:
		std::string m_strEvent;
		size_t m_nEventHashID;

		std::function<void(const HrEventPtr&)> m_funcOnEvent;
	};

	class HR_CORE_API  HrEventListenerKeyboard : public HrEventListener
	{
	public:
		HrEventListenerKeyboard(std::function<void(HrEventKeyboard::EnumKeyCode, const HrEventPtr&)>
			, std::function<void(HrEventKeyboard::EnumKeyCode, const HrEventPtr&)>);
		~HrEventListenerKeyboard();


		virtual void OnEvent(const HrEventPtr& pEvent) override;


	protected:
		std::function<void(HrEventKeyboard::EnumKeyCode, const HrEventPtr&)> m_funcOnKeyPressed;
		std::function<void(HrEventKeyboard::EnumKeyCode, const HrEventPtr&)> m_funcOnKeyReleased;

	};


	class HR_CORE_API  HrEventListenerMouse : public HrEventListener
	{
	public:
		HrEventListenerMouse(std::function<void(HrEventMouse::EnumMouseButtonID, const HrEventPtr&)>
			, std::function<void(HrEventMouse::EnumMouseButtonID, const HrEventPtr&)>
			, std::function<void(const HrEventPtr&)>);
		~HrEventListenerMouse();


		virtual void OnEvent(const HrEventPtr& pEvent) override;


	protected:
		std::function<void(HrEventMouse::EnumMouseButtonID, const HrEventPtr&)> m_funcOnMousePressed;
		std::function<void(HrEventMouse::EnumMouseButtonID, const HrEventPtr&)> m_funcOnMouseReleased;
		std::function<void(const HrEventPtr&)> m_funcOnMouseMove;

	};

	class HR_CORE_API HrEventListenerCustom : public HrEventListener
	{
	public:
		HrEventListenerCustom(const std::string& strEvent, const std::function<void(const HrEventPtr&)>& callBack);
		~HrEventListenerCustom();

		virtual void OnEvent(const HrEventPtr& pEvent) override;

	};

}


#endif






