#ifndef _HR_APPLICAION_H_
#define _HR_APPLICAION_H_

#include <Windows.h>
#include "HrDefine.h"

namespace HR
{
	class CHrApplication
	{
	public:
		CHrApplication(void);
		virtual ~CHrApplication(void);

	public:
		void                    AppGo();

		virtual void            AppSetup();
		virtual void            AppRelease();

		virtual void            PreRender();
		virtual void            RenderScene();
		virtual void            PostRender();

		virtual void            UpdateScene();
	protected:
		void                    InitParam();
		bool                    InitWindow(HINSTANCE hInstance, int nCmdShow);
		
		bool                    InitD3D();

		static LRESULT CALLBACK WinProc( HWND hWnd, UINT message, WPARAM wParam,  LPARAM lParam);

	protected:
		HWND                    m_hWnd;
		HINSTANCE               m_hInstance;
		
		int                     m_nWndWidth;
		int                     m_nWndHeight;
	};
}

#endif
