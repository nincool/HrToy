#ifndef _HR_WINDOWWIN_H_
#define _HR_WINDOWWIN_H_

#include "HrCore/Include/Kernel/HrWindow.h"

namespace Hr
{
	class HR_CORE_API HrWindowWin : public HrWindow
	{
	public:
		HrWindowWin();
		~HrWindowWin();

		virtual bool CreateAppWidnow() override;
		virtual void Update() override;
		virtual void Destroy() override;

		HWND GetHWnd();
		uint32 GetWidth();
		uint32 GetHeight();
	protected:
		HWND m_hWnd;
		uint32 m_nWidth;
		uint32 m_nHeight;

	};
}


#endif



