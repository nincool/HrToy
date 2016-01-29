#ifndef _HR_D3D11RENDER_H_
#define _HR_D3D11RENDER_H_

#include "HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/IRender.h"

struct ID3D11DeviceContext;

namespace Hr
{
	class HrD3D11Device;
	class IRenderDemo;

	class HrD3D11Render : public IRender
	{
	public:
		HrD3D11Render();
		~HrD3D11Render();

	public:
		virtual bool Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc) override;
		virtual void Release() override;
		virtual bool StartRender() override;

		
	public:
		virtual void Render(HrRenderTechnique* pRenderTechnique, IRenderLayout* pRenderLayout) override;

	private:
		HR_SYNTHESIZE_READONLY(ID3D11DeviceContext*, m_pD3D11ImmediateContext, D3D11ImmediateContext);

		/////////////////////////////--- RenderTest ---/////////////////////////////////
	public:
		IRenderDemo* m_pRenderDemo;

		HR_SYNTHESIZE_READONLY(HrD3D11RenderWindowPtr, m_pShareRenderWindow, RenderWindow);


	};
}


#endif

