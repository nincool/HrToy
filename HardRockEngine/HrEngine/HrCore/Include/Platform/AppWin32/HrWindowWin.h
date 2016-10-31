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

	protected:
		HR_SYNTHESIZE_READONLY(HWND, m_hWnd, Hwnd);
		HR_SYNTHESIZE_READONLY(uint32, m_nWidth, Width);
		HR_SYNTHESIZE_READONLY(uint32, m_nHeight, Height);

	};
}


#endif



