#include "HrD3D11Texture.h"
#include "HrD3D11Mapping.h"

using namespace Hr;

HrD3D11Texture::HrD3D11Texture(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pContext, EnumTextureType texType, uint32 nSampleCount, uint32 nSampleQuality)
	:HrTexture(texType, nSampleCount, nSampleQuality)
{
	m_pD3DResource = nullptr;
	m_pD3DSRV = nullptr;
}

HrD3D11Texture::~HrD3D11Texture()
{
}

////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
HrD3D11Texture2D::HrD3D11Texture2D(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pContext, EnumTextureType texType, uint32 nSampleCount, uint32 nSampleQuality)
	:HrD3D11Texture(pD3D11Device, pContext, texType, nSampleCount, nSampleQuality)
{

}

HrD3D11Texture2D::~HrD3D11Texture2D()
{

}

void HrD3D11Texture2D::Create2DTexture()
{
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = m_nWidth;
	desc.Height = m_nHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = HrD3D11Mapping::GetPixelFormat(m_format);
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 1;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;

}

void HrD3D11Texture2D::Create2DResourceView()
{

}
