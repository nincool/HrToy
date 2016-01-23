#ifndef _HR_D3D11RENDERWINDOW_H_
#define _HR_D3D11RENDERWINDOW_H_

#include "HrRenderSystem/HrRenderCommon/IRenderWindow.h"

namespace Hr
{
	class HrD3D11RenderWindow : public IRenderWindow
	{
	public:
		HrD3D11RenderWindow();

		virtual bool CreateRenderWindow(uint32 nWidth, uint32 nHeight, WNDPROC lpfnProc);

	private:
		HR_SYNTHESIZE_READONLY(uint32, m_nWidth, Width);
		HR_SYNTHESIZE_READONLY(uint32, m_nHeight, Height);

		HR_SYNTHESIZE_READONLY(HWND, m_hWnd, RenderWindowHandle);
	};
}

#endif







