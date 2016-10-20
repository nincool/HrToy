#ifndef _HR_EVENTLISTENER_H_
#define _HR_EVENTLISTENER_H_

#include "HrCore/Include/HrCorePrerequisite.h"


namespace Hr
{
	class HR_CORE_API  HrEventListener
	{
	public:
		HrEventListener(std::string& strListenerID, const std::function<void(HrEvent*)>& callBack);
		virtual ~HrEventListener();

		void SetEventListenerStringID(std::string strEventListenerID);
		std::string GetEventListenerStringID();
		size_t GetEventListenerHashID();


		virtual void OnEvent(HrEvent* pEvent);
	protected:
		std::string m_strEventListenerID;
		size_t m_nEventListenerID;

		std::function<void(HrEvent*)> m_funcOnEvent;
	};
}


#endif






