#ifndef _I_RENDERTARGET_H_
#define _I_RENDERTARGET_H_

#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HR_CORE_API IRenderTarget : public RenderSysAllocatedObject
	{
	public:
		virtual ~IRenderTarget(){};

		//Create the render window
		virtual bool CreateRenderWindow(uint32 nWidth, uint32 nHeight, WNDPROC lpfnProc) = 0;
		virtual HrViewPort* AddViewPort(HrCamera* pCamera, float fLeft, float fTop, float fWidth, float fHeight, int nZOrder) = 0;
		virtual std::map<int, HrViewPort*>& GetViewPorts() = 0;
	};
}

#endif



