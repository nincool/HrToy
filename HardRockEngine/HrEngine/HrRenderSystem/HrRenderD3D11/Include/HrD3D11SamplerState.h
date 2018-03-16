#ifndef _HR_D3D11SAMPLERSTATE_H_
#define _HR_D3D11SAMPLERSTATE_H_

#include "HrCore/Include/Render/HrSamplerState.h"
#include "HrD3D11RenderPrerequisite.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Device.h"

namespace Hr
{
	class HrD3D11SamplerState : public HrSamplerState
	{
	public:
		HrD3D11SamplerState(const ID3D11DevicePtr& pD3D11Device
			, const ID3D11DeviceContextPtr& pContext);
		
		const ID3D11SamplerStatePtr& GetD3D11SamplerState();

	protected:
		ID3D11DevicePtr m_pD3D11Device;
		ID3D11DeviceContextPtr m_pImmediateContext;

		ID3D11SamplerStatePtr m_pSamplerState;
	};
}

#endif


//HrD3D11Texture(ID3D11Device* pD3D11Device
//	, ID3D11DeviceContext* pContext
//	, EnumTextureType texType
//	, uint32 nSampleCount
//	, uint32 nSampleQuality);
//~HrD3D11Texture();