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
		virtual void Create(unsigned int nWidth, unsigned int nHeight) override;

		virtual void Destroy() override;

	protected:
		HWND m_hWnd;
	};
}


#endif

