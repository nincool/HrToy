#include "HrD3D11SamplerState.h"
#include "HrD3D11Mapping.h"

using namespace Hr;


HrD3D11SamplerState::HrD3D11SamplerState(const HrSamplerState::HrSamplerStateDesc& desc)
{
	CreateSamplerState(desc);
}

const ID3D11SamplerStatePtr& HrD3D11SamplerState::CreateSamplerState(const HrSamplerState::HrSamplerStateDesc& desc)
{
	if (m_pSamplerState == nullptr)
	{
		D3D11_SAMPLER_DESC samplerDesc;
		samplerDesc.Filter = HrD3D11Mapping::GetFilter(desc.samplerFilter);
		samplerDesc.AddressU = HrD3D11Mapping::GetTextureAddressMode(desc.texAddressU);
		samplerDesc.AddressV = HrD3D11Mapping::GetTextureAddressMode(desc.texAddressV);;
		samplerDesc.AddressW = HrD3D11Mapping::GetTextureAddressMode(desc.texAddressW);;
		samplerDesc.MipLODBias = desc.fMipLODBias;
		samplerDesc.MaxAnisotropy = desc.nMaxAnisotropy;
		samplerDesc.ComparisonFunc = HrD3D11Mapping::GetComparisonFunc(desc.comFunc);
		samplerDesc.BorderColor[0] = desc.borderColorArr[0];
		samplerDesc.BorderColor[1] = desc.borderColorArr[1];
		samplerDesc.BorderColor[2] = desc.borderColorArr[2];
		samplerDesc.BorderColor[3] = desc.borderColorArr[3];
		samplerDesc.MinLOD = desc.fMinLOD;
		samplerDesc.MaxLOD = desc.fMaxLOD;

		ID3D11SamplerState* pSamplerState = nullptr;
		HRESULT hr = HrD3D11Device::Instance()->GetD3DDevice()->CreateSamplerState(&samplerDesc, &pSamplerState);
		if (FAILED(hr))
		{
			BOOST_ASSERT(false);
		}
		m_pSamplerState = MakeComPtr(pSamplerState);

	}

	return m_pSamplerState;
}

const ID3D11SamplerStatePtr& HrD3D11SamplerState::RetriveD3DSamplerState()
{
	return m_pSamplerState;
}

void HrD3D11SamplerState::Accept(const HrRenderPtr& pRender)
{

}
