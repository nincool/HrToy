#ifndef _HR_D3D11RENDER_H_
#define _HR_D3D11RENDER_H_

#include "HrD3D11RendererPrerequisites.h"
#include "../Include/IRenderer.h"

namespace Hr
{
	class HrD3D11DriverList;
	class HrD3D11Device;

	class HrD3D11Render : public IRenderer
	{
	public:
		HrD3D11Render();
		~HrD3D11Render();

	public:
#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
		virtual bool Create(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc) override;
#else
		virtual bool Create(unsigned int nWidth, unsigned int nHeight) override;
#endif

		virtual void Destroy() override;

		HR_INSTANCE(HrD3D11Render);

	protected:
		bool CreateRenderWindow(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc);
		bool CreateD3D11Device();
	protected:
		HWND m_hWnd;

		IDXGIFactory1* m_pDXGIFactory;
		HrD3D11DriverList* m_pDriverList;

		HrD3D11Device* m_pD3D11Device;
	};
}


#endif

