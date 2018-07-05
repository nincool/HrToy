#ifndef _HR_D3D11BLENDSTATE_H_
#define _HR_D3D11BLENDSTATE_H_

#include "HrCore/Include/Render/HrBlendState.h"
#include "HrD3D11RenderPrerequisite.h"
#include "HrD3D11Device.h"
#include "HrMath/Include/HrColor.h"

namespace Hr
{
	class HrD3D11BlendState : public HrBlendState, public std::enable_shared_from_this<HrD3D11BlendState>
	{
	public:
		HrD3D11BlendState(const HrBlendState::HrBlendStateDesc& blendDesc);
		virtual ~HrD3D11BlendState();

		virtual void Accept(const HrRenderPtr& pRender) override;

		const ID3D11BlendStatePtr& RetriveD3D11BlendState();
		const HrColor& GetBlendFactor();
		uint32 GetSampleMask();
	protected:
		ID3D11BlendStatePtr m_pD3D11BlendState;
		HrColor m_blendFactorColor;
		uint32 m_nSampleMask;
	};
}


#endif


