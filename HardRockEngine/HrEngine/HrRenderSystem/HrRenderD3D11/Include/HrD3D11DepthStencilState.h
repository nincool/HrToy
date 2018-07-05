#ifndef _HR_D3D11DEPTHSTENCILSTATE_H_
#define _HR_D3D11DEPTHSTENCILSTATE_H_

#include "HrCore/Include/Render/HrDepthStencilState.h"
#include "HrD3D11RenderPrerequisite.h"
#include "HrD3D11Device.h"

namespace Hr
{
	class HrD3D11DepthStencilState : public HrDepthStencilState, public std::enable_shared_from_this<HrD3D11DepthStencilState>
	{
	public:
		HrD3D11DepthStencilState(const HrDepthStencilState::HrDepthStencilStateDesc& depthStencilDesc);
		virtual ~HrD3D11DepthStencilState();

		virtual void Accept(const HrRenderPtr& pRender) override;

		const ID3D11DepthStencilStatePtr& RetriveD3D11DepthStencil();

		uint32 GetStencilRef();
	protected:
		ID3D11DepthStencilStatePtr m_pD3D11DepthStencilState;

		uint32 m_nStencilRef;
	};
}


#endif


