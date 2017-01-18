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
		HrD3D11SamplerState(ID3D11Device* pD3D11Device
			, ID3D11DeviceContext* pContext);
		
		ID3D11SamplerState* GetD3D11SamplerState();

	protected:
		ID3D11Device* m_pD3D11Device;
		ID3D11DeviceContext* m_pImmediateContext;

		ID3D11SamplerState* m_pSamplerState;
	};
}

#endif


//HrD3D11Texture(ID3D11Device* pD3D11Device
//	, ID3D11DeviceContext* pContext
//	, EnumTextureType texType
//	, uint32 nSampleCount
//	, uint32 nSampleQuality);
//~HrD3D11Texture();