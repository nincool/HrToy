#include "HrD3D11Texture.h"
#include "HrD3D11Mapping.h"
#include "HrCore/Include/Asset/HrStreamData.h"

#include "ThirdParty/DirectXTK/Inc/DDSTextureLoader.h"

using namespace Hr;
using namespace DirectX;

HrD3D11Texture::HrD3D11Texture(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pContext, EnumTextureType texType, uint32 nSampleCount, uint32 nSampleQuality)
	:HrTexture(texType, nSampleCount, nSampleQuality), m_pD3D11Device(pD3D11Device), m_pImmediateContext(pContext)
{
	m_pD3DResource = nullptr;
	m_pD3DSRV = nullptr;
}

HrD3D11Texture::~HrD3D11Texture()
{
	SAFE_DELETE(m_pTexData);
}

void HrD3D11Texture::CreateTexture()
{
	BOOST_ASSERT(false);
}

void HrD3D11Texture::CreateSRV()
{
	BOOST_ASSERT(false);
}

////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
HrD3D11Texture2D::HrD3D11Texture2D(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pContext, EnumTextureType texType, uint32 nSampleCount, uint32 nSampleQuality)
	:HrD3D11Texture(pD3D11Device, pContext, texType, nSampleCount, nSampleQuality), m_pD3DTexture2D(nullptr)
{

}

HrD3D11Texture2D::~HrD3D11Texture2D()
{

}

void HrD3D11Texture2D::CreateTexture()
{
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = m_nWidth;
	desc.Height = m_nHeight;
	
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	
	desc.Format = HrD3D11Mapping::GetPixelFormat(m_format);
	
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA subRes;
	subRes.pSysMem = m_pTexData->GetBufferPoint();
	subRes.SysMemPitch = m_nSrcPitch;
	subRes.SysMemSlicePitch = 0;

	HRESULT hr = m_pD3D11Device->CreateTexture2D(&desc, &subRes, &m_pD3DTexture2D);
	if (FAILED(hr))
	{
		BOOST_ASSERT(false);
	}
	m_pD3DResource = m_pD3DTexture2D;
}

void HrD3D11Texture2D::CreateSRV()
{
	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	desc.Format = HrD3D11Mapping::GetPixelFormat(m_format);
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MostDetailedMip = 0;
	desc.Texture2D.MipLevels = 1;

	HRESULT hr = m_pD3D11Device->CreateShaderResourceView(m_pD3DResource, &desc, &m_pD3DSRV);
	if (FAILED(hr))
	{
		BOOST_ASSERT(false);
	}
}
