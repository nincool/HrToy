#ifndef _HR_D3D11BLENDSTATE_H_
#define _HR_D3D11BLENDSTATE_H_

#include "HrCore/Include/Render/HrBlendState.h"
#include "HrD3D11RenderPrerequisite.h"
#include "HrD3D11Device.h"

namespace Hr
{
	class HrD3D11BlendState : public HrBlendState
	{
	public:
		HrD3D11BlendState(ID3D11Device* pD3D11Device
			, ID3D11DeviceContext* pContext);
		virtual ~HrD3D11BlendState();

		virtual void Bind(HrRender* pRender) override;

	protected:
		ID3D11Device* m_pD3D11Device;
		ID3D11DeviceContext* m_pImmediateContext;

		ID3D11BlendState* m_pD3D11BlendState;
	};
}


#endif


