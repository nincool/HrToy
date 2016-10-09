#ifndef _I_RENDERTARGET_H_
#define _I_RENDERTARGET_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API IRenderTarget 
	{
	public:
		virtual ~IRenderTarget(){};

		//Create the render window
		virtual bool CreateRenderWindow(uint32 nWidth, uint32 nHeight, WNDPROC lpfnProc) = 0;
		
		virtual void AddViewPort(HrViewPort* pViewPort) = 0;
		
		virtual std::map<int, HrViewPort*>& GetViewPorts() = 0;
	};
}

#endif



