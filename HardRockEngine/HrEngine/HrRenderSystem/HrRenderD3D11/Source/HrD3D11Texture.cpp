#include "HrD3D11Texture.h"
#include "HrD3D11Mapping.h"
#include "HrCore/Include/Asset/HrStreamData.h"

using namespace Hr;

HrD3D11Texture::HrD3D11Texture(EnumTextureType texType
	, uint32 nWidth
	, uint32 nHeight
	, uint32 nSampleCount
	, uint32 nSampleQuality
	, EnumD3DTEXTURE_USED texUsage):HrTexture(texType, nWidth, nHeight, nSampleCount, nSampleQuality)
	, m_texUsage(texUsage)
{
	m_pD3D11Device = HrD3D11Device::Instance()->GetD3DDevice();
	m_pD3D11Context = HrD3D11Device::Instance()->GetD3DDeviceContext();
}

HrD3D11Texture::~HrD3D11Texture()
{
}

const ID3D11RenderTargetViewPtr& HrD3D11Texture::GetD3DRenderTargetView()
{
	return m_pRenderTargetView;
}

const ID3D11DepthStencilViewPtr& HrD3D11Texture::GetD3DDepthStencilView()
{
	return m_pDepthStencilView;
}

const ID3D11ResourcePtr& HrD3D11Texture::GetD3D11Resource()
{
	return m_pD3DTexture;
}

//void HrD3D11Texture::CreateTexture()
//{
//	BOOST_ASSERT(false);
//}
//
//void HrD3D11Texture::CreateSRV()
//{
//	BOOST_ASSERT(false);
//}

////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
HrD3D11Texture2D::HrD3D11Texture2D(uint32 nWidth
	, uint32 nHeight
	, EnumD3DTEXTURE_USED texUsage) : HrD3D11Texture(HrTexture::TEX_TYPE_2D, nWidth, nHeight, 1, 0, texUsage)
{
	switch (texUsage)
	{
	case D3D_TEX_DEPTHSTENCILVIEW:
		CreateDepthStencilView();
		break;
	default:
		TRE("Invalid texUsage");
		break;

	}
}

HrD3D11Texture2D::HrD3D11Texture2D(uint32 nWidth
	, uint32 nHeight
	, uint32 nSampleCount
	, uint32 nSampleQuality
	, EnumD3DTEXTURE_USED texUsage): HrD3D11Texture(HrTexture::TEX_TYPE_2D, nWidth, nHeight, nSampleCount, nSampleQuality, texUsage)
{
}

HrD3D11Texture2D::HrD3D11Texture2D(const ID3D11Texture2DPtr& pD3DTex2D, EnumD3DTEXTURE_USED texUsage)
	: HrD3D11Texture(HrTexture::TEX_TYPE_2D, 0, 0, 1, 0, texUsage)
{

	D3D11_TEXTURE2D_DESC texDesc;
	m_pD3DTexture = pD3DTex2D;
	pD3DTex2D->GetDesc(&texDesc);

	m_nWidth = texDesc.Width;
	m_nHeight = texDesc.Height;
	
	m_nSampleCount = texDesc.SampleDesc.Count;
	m_nSampleQuality = texDesc.SampleDesc.Quality;

	m_format = HrD3D11Mapping::GetPixelFormat(texDesc.Format);
	m_textureUsage = HrD3D11Mapping::GetTextureUsage(texDesc.Usage);

	switch (texUsage)
	{
	case HrD3D11Texture::D3D_TEX_RENDERTARGETVIEW:
		CreateRenderTargetView();
		break;
	default:
		TRE("Invalid texUsage")
		break;
	}
}


HrD3D11Texture2D::~HrD3D11Texture2D()
{

}

bool HrD3D11Texture2D::CreateRenderTargetView()
{
	ID3D11RenderTargetView* pRenderTargetView = nullptr;
	HRESULT hr = m_pD3D11Device->CreateRenderTargetView(m_pD3DTexture.get(), 0, &pRenderTargetView);
	if (FAILED(hr))
	{
		TRE("HrD3D11Texture2D::CreateRenderTargetView Error!");
		return false;
	}
	m_pRenderTargetView = MakeComPtr(pRenderTargetView);

	return true;
}

bool HrD3D11Texture2D::CreateDepthStencilView()
{
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthStencilDesc.Width = m_nWidth;
	depthStencilDesc.Height = m_nHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencil = nullptr;
	HRESULT hr = m_pD3D11Device->CreateTexture2D(&depthStencilDesc, nullptr, &pDepthStencil);
	if (FAILED(hr))
	{
		TRE("HrD3D11Texture2D::CreateDepthStencilView create texture Error!");
		return false;
	}
	m_pD3DTexture = MakeComPtr(pDepthStencil);

	//Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	descDSV.Format = depthStencilDesc.Format;
	if (depthStencilDesc.SampleDesc.Count > 1)
	{
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	}
	else
	{
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	}
	descDSV.Texture2D.MipSlice = 0;
	
	ID3D11DepthStencilView* pDepthStencilView = nullptr;
	hr = HrD3D11Device::Instance()->GetD3DDevice()->CreateDepthStencilView(pDepthStencil, &descDSV, &pDepthStencilView);
	if (FAILED(hr))
	{
		TRE("HrD3D11Texture2D::CreateDepthStencilView  Error!");
		return false;
	}
	m_pDepthStencilView = MakeComPtr(pDepthStencilView);
}
