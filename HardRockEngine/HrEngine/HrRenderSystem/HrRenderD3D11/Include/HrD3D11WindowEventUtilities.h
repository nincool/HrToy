/************************************************************************
*
* @Comment£º
*
* @Author: Hr
* @Date: [10/29/2015 By Hr]
*
************************************************************************/  
#ifndef _HR_D3D11WINDOWEVENTUTILITIES_H_
#define _HR_D3D11WINDOWEVENTUTILITIES_H_

#include "HrD3D11RendererPrerequisites.h"

namespace Hr
{
	class HrD3D11WindowEventUtilities
	{
	public:
		HrD3D11WindowEventUtilities();
		~HrD3D11WindowEventUtilities();
		/**
		 *	@Brief:  Call this once per frame [10/29/2015 By Hr]
		 *	@Param:
		 *	@Return:
		*/
		static void MessagePump();

		static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}


#endif // !_HR_WINDOWEVENTUTILITIES_H_


