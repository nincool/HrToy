#ifndef _HR_D3D11RASTERIZERSTATE_H_
#define _HR_D3D11RASTERIZERSTATE_H_

#include "HrCore/Include/Render/HrRasterizerState.h"
#include "HrD3D11RenderPrerequisite.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Device.h"

namespace Hr
{
	class HrD3D11RasterizerState : public HrRasterizerState
	{
	public:
		HrD3D11RasterizerState(ID3D11Device* pD3D11Device
			, ID3D11DeviceContext* pContext
			, HrRasterizerState::RasterizerStateDesc& desc);
		~HrD3D11RasterizerState();

		virtual void Bind(HrRender* pRender) override;

		ID3D11RasterizerState* CreateD3D11RasterizerState(HrRasterizerState::RasterizerStateDesc& desc);
	protected:
		ID3D11Device* m_pD3D11Device;
		ID3D11DeviceContext* m_pImmediateContext;

		ID3D11RasterizerState* m_pRasterizerState;
	};
}

#endif



