#ifndef _HR_WINCORECOMPONENT_H_
#define _HR_WINCORECOMPONENT_H_

#include "HrCore/Include/Kernel/HrModule.h"

namespace Hr
{
	class HR_CORE_API HrWindowModule : public HrModule
	{
	public:
		HrWindowModule();
		HrWindowModule(void* pWnd);
		~HrWindowModule();

		virtual bool Update(float fDelta) override;
		
		void UpdateWindowMsg();
		void DestroyWindow();

		HWND GetWindowHWnd();
		uint32 GetWindowX();
		uint32 GetWindowY();
		uint32 GetWindowWidth();
		uint32 GetWindowHeight();


	private:
		void CreateAppWindow();
	private:
		HrWindowPtr m_pWindow;

	};
}

#endif
