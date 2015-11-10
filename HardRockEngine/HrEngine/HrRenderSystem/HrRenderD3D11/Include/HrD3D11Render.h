#ifndef _HR_D3D11RENDER_H_
#define _HR_D3D11RENDER_H_

#include "HrD3D11RendererPrerequisites.h"
#include "../Include/IRenderer.h"

namespace Hr
{
	class HrD3D11Render : public IRenderer
	{
	public:
		HrD3D11Render();
		~HrD3D11Render();

	public:
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
		virtual void Create(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc) override;
#else
		virtual void Create(unsigned int nWidth, unsigned int nHeight) override;
#endif

		virtual void Destroy() override;

		HR_INSTANCE(HrD3D11Render);
	protected:
		HWND m_hWnd;
	};
}


#endif

