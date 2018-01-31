#ifndef _HR_D3D11RENDERWINDOW_H_
#define _HR_D3D11RENDERWINDOW_H_

#include "HrCore/Include/Render/HrRenderTarget.h"
#include "HrD3D11Device.h"

namespace Hr
{
	class HrD3D11RenderTarget : public HrRenderTarget
	{
	public:
		HrD3D11RenderTarget(const ID3D11Texture2DPtr& pBackBuffer);

		const ID3D11RenderTargetViewPtr& GetRenderTargetView();

	private:
		void CreateRenderTargetView(const ID3D11Texture2DPtr& pBackBuffer);
	private:
		HrD3D11Texture2DPtr m_pRenderTargetBuff;
		HrD3D11Texture2DPtr m_pTexRenderTargetView;
	};
}

#endif







