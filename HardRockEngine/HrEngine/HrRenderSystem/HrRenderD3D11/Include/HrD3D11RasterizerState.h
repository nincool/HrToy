#ifndef _HR_D3D11RASTERIZERSTATE_H_
#define _HR_D3D11RASTERIZERSTATE_H_

#include "HrCore/Include/Render/HrRasterizerState.h"
#include "HrD3D11RenderPrerequisite.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Device.h"

namespace Hr
{
	class HrD3D11RasterizerState : public HrRasterizerState, public std::enable_shared_from_this<HrD3D11RasterizerState>
	{
	public:
		HrD3D11RasterizerState(HrRasterizerState::HrRasterizerStateDesc& desc);
		~HrD3D11RasterizerState();

		virtual void Accept(const HrRenderPtr& pRender) override;

		const ID3D11RasterizerStatePtr& RetriveD3D11RasterizerState();

	protected:
		void CreateD3D11RasterizerState(HrRasterizerState::HrRasterizerStateDesc& desc);
	protected:

		ID3D11RasterizerStatePtr m_pRasterizerState;
	};
}

#endif



