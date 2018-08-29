#ifndef _HR_WINDOWWIN_H_
#define _HR_WINDOWWIN_H_

#include "HrCore/Include/Kernel/HrWindow.h"

namespace Hr
{
	class HR_CORE_API HrWindowWin : public HrWindow
	{
	public:
		HrWindowWin(uint32 nWidth, uint32 nHeight);
		~HrWindowWin();

		virtual bool CreateAppWidnow() override;
		virtual void UpdateMsg() override;
		virtual void Destroy() override;

		virtual HWND GetHWnd() override;
		virtual uint32 GetTopX() override;
		virtual uint32 GetTopY() override;
		virtual uint32 GetWidth() override;
		virtual uint32 GetHeight() override;
	protected:
		HWND m_hWnd;
		uint32 m_nWidth;
		uint32 m_nHeight;

	};
}


#endif



