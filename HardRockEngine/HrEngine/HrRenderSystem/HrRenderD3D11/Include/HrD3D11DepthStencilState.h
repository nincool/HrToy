#ifndef _HR_D3D11DEPTHSTENCILSTATE_H_
#define _HR_D3D11DEPTHSTENCILSTATE_H_

#include "HrCore/Include/Render/HrDepthStencilState.h"
#include "HrD3D11RenderPrerequisite.h"
#include "HrD3D11Device.h"

namespace Hr
{
	class HrD3D11DepthStencilState : public HrDepthStencilState
	{
	public:
		HrD3D11DepthStencilState(ID3D11Device* pD3D11Device
			, ID3D11DeviceContext* pContext
			, const HrDepthStencilState::HrDepthStencilStateDesc& depthStencilDesc);
		virtual ~HrD3D11DepthStencilState();

		virtual void Bind(HrRender* pRender) override;

	protected:
		ID3D11Device* m_pD3D11Device;
		ID3D11DeviceContext* m_pImmediateContext;

		ID3D11DepthStencilState* m_pD3D11DepthStencilState;
	};
}


#endif


