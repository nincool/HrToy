﻿#ifndef _HR_D3D11RENDER_H_
#define _HR_D3D11RENDER_H_

#include "HrD3D11RendererPrerequisites.h"
#include "../Include/IRenderer.h"
#include "HrMain/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IDirector;
	class HrD3D11Device;

	class HrD3D11Render : public IRenderer , public RenderSysAllocatedObject
	{
	public:
		HrD3D11Render();
		~HrD3D11Render();

	public:
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
		virtual bool Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc) override;
#else
		virtual bool Init(unsigned int nWidth, unsigned int nHeight) override;
#endif

		virtual void Release() override;

		HR_INSTANCE(HrD3D11Render);
	protected:
		bool CreateD3D11Device();
	};
}


#endif
