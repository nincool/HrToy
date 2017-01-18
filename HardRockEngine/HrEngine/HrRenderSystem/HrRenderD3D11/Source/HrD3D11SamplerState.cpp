#include "HrD3D11SamplerState.h"

using namespace Hr;


HrD3D11SamplerState::HrD3D11SamplerState(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pContext):
	m_pD3D11Device(pD3D11Device), m_pImmediateContext(pContext)
{
}

ID3D11SamplerState* HrD3D11SamplerState::GetD3D11SamplerState()
{
	if (m_pSamplerState == nullptr)
	{
		D3D11_SAMPLER_DESC samplerDesc;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDesc.BorderColor[0] = 0.0f;
		samplerDesc.BorderColor[1] = 0.0f;
		samplerDesc.BorderColor[2] = 0.0f;
		samplerDesc.BorderColor[3] = 0.0f;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = FLT_MAX;

		HRESULT hr = m_pD3D11Device->CreateSamplerState(&samplerDesc, &m_pSamplerState);
		if (FAILED(hr))
		{
			BOOST_ASSERT(false);
		}

	}

	return m_pSamplerState;
}
