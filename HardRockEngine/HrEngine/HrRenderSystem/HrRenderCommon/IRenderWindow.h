#ifndef _I_RENDERWINDOW_H_
#define _I_RENDERWINDOW_H_

#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IRenderWindow : public RenderSysAllocatedObject
	{
	public:
		~IRenderWindow();

		//Create the render window
		virtual bool CreateRenderWindow(uint32 nWidth, uint32 nHeight, WNDPROC lpfnProc) = 0;
	};
}

#endif



