/************************************************************************
*
* @Comment：
*
* @Author: Hr
* @Date: [10/29/2015 By Hr]
*
************************************************************************/  
#ifndef _HR_WIN32DWINDOWEVENTUTILITIES_H_
#define _HR_WIN32DWINDOWEVENTUTILITIES_H_

#include "HrCorePrerequisite.h"

namespace Hr
{
	class HrWindowsEventUtilities
	{
	public:
		HrWindowsEventUtilities();
		~HrWindowsEventUtilities();
		/**
		 *	@Brief:  Call this once per frame [10/29/2015 By Hr]
		 *	@Param:
		 *	@Return:
		*/
		static bool MessagePump();

		static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}


#endif // !_HR_WINDOWEVENTUTILITIES_H_


