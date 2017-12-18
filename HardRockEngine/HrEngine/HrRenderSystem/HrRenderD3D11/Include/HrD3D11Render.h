#ifndef _HR_D3D11RENDER_H_
#define _HR_D3D11RENDER_H_

#include "HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/HrRender.h"

struct ID3D11DeviceContext;
struct ID3D11Device;

struct ID3DX11EffectMatrixVariable;

namespace Hr
{
	class HrD3D11Device;
	class IRenderDemo;

	class HrD3D11Render : public HrRender
	{
	public:
		HrD3D11Render();
		~HrD3D11Render();

	public:
		virtual bool Init() override;
		virtual void SetRenderTarget(HrRenderTargetPtr& renderTarget) override;
		virtual void SetCurrentViewPort(HrViewPort* pViewPort) override;
		
		virtual void ClearRenderTargetView() override;
		virtual void ClearDepthStencilView() override;

		virtual void Render(HrRenderTechnique* pRenderTechnique, HrRenderLayout* pRenderLayout) override;
		virtual void SwapChain() override;

		virtual void ReleaseRenderEngine() override;
		virtual bool StartRender() override;

		const ID3D11DevicePtr& GetD3D11Device();
		const ID3D11DeviceContextPtr& GetD3D11DeviceContext();
	private:
		/////////////////////////////--- RenderTest ---/////////////////////////////////
	public:
		HR_SYNTHESIZE_READONLY(HrD3D11RenderWindowPtr, m_pRenderWindow, RenderWindow);

	};
}


#endif

