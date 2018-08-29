#ifndef _HR_WRAPPERWIN_H_
#define _HR_WRAPPERWIN_H_

#include "HrCore/Include/Kernel/HrWindow.h"

namespace Hr
{
	class HR_CORE_API HrWrapperWin : public HrWindow
	{
	public:
		HrWrapperWin(HWND hWnd);
		~HrWrapperWin();

		virtual bool CreateAppWidnow() override;
		virtual void UpdateMsg() override;
		virtual void Destroy() override;

		virtual HWND GetHWnd() override;
		virtual uint32 GetTopX() override;
		virtual uint32 GetTopY() override;
		virtual uint32 GetWidth() override;
		virtual uint32 GetHeight() override;

	private:
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	protected:
		HWND m_hWnd;

		uint32 m_nLeft;
		uint32 m_nTop;

		uint32 m_nWidth;
		uint32 m_nHeight;

		WNDPROC default_wnd_proc_;
	};
}


#endif



