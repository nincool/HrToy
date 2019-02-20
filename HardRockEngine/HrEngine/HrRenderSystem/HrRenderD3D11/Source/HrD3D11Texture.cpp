#include "HrD3D11Texture.h"
#include "HrD3D11Mapping.h"
#include "HrCore/Include/Asset/HrStreamData.h"
#include "HrCore/Include/Asset/HrImage.h"

using namespace Hr;

HrD3D11Texture::HrD3D11Texture(EnumTextureType texType
	, uint32 nSampleCount
	, uint32 nSampleQuality
	, uint32 nAccessHint
	, uint32 texUsedFor) : HrTexture(texType, nSampleCount, nSampleQuality, nAccessHint, texUsedFor)
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


const ID3D11ShaderResourceViewPtr& HrD3D11Texture::GetD3D11ShaderResourceView()
{
	return m_pShaderResourceView;
}

const ID3D11ResourcePtr& HrD3D11Texture::GetD3D11Resource()
{
	return m_pD3DResource;
}

UINT HrD3D11Texture::GetD3DTextureBindFlags()
{
	UINT nBindFlags = 0;
	if (m_nUsedFor & HrD3D11Texture::TUF_TEX_DEPTHSTENCILVIEW)
	{
		nBindFlags |= D3D11_BIND_DEPTH_STENCIL;
	}
	
	if (m_nUsedFor & HrD3D11Texture::TUF_TEX_RENDERTARGETVIEW)
	{
		nBindFlags |= D3D11_BIND_RENDER_TARGET;
	}

	if (m_nUsedFor & HrD3D11Texture::TUF_TEX_SHADERRESOURCEVIEW)
	{
		nBindFlags |= D3D11_BIND_SHADER_RESOURCE;
	}

	return nBindFlags;
}

UINT HrD3D11Texture::GetD3DCPUAccessFlags()
{
	UINT nCPUAccessFlags = 0;
	if (m_nAccessHint & EAH_CPU_READ)
	{
		nCPUAccessFlags |= D3D11_CPU_ACCESS_READ;
	}
	if (m_nAccessHint & EAH_CPU_WRITE)
	{
		nCPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;
	}

	return nCPUAccessFlags;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

HrD3D11Texture2D::HrD3D11Texture2D(uint32 nWidth
	, uint32 nHeight
	, uint32 nNumMipMaps
	, uint32 nSampleCount
	, uint32 nSampleQuality
	, uint32 nAccessHint
	, uint32 texUsedFor
	, EnumPixelFormat format) : HrD3D11Texture(HrTexture::TEX_TYPE_2D, nSampleCount, nSampleQuality, nAccessHint, texUsedFor)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nMipMapsNum = nNumMipMaps;
	m_format = format;

	if (!(m_nUsedFor & HrD3D11Texture::TUF_TEX_DEFAULTTEXTURE))
	{
		CreateHWResource(nullptr);
	}
}

HrD3D11Texture2D::HrD3D11Texture2D(const ID3D11Texture2DPtr& pD3DTex2D, EnumTextureUsedFor texUsedFor) : HrD3D11Texture(HrTexture::TEX_TYPE_2D, 0, 0, 0, texUsedFor)
{
	D3D11_TEXTURE2D_DESC desc;
	pD3DTex2D->GetDesc(&desc);

	m_nWidth = desc.Width;
	m_nHeight = desc.Height;
	m_nMipMapsNum = desc.MipLevels;
	m_nArraySize = desc.ArraySize;
	m_format = HrD3D11Mapping::GetPixelFormat(desc.Format);
	m_nSampleCount = desc.SampleDesc.Count;
	m_nSampleQuality = desc.SampleDesc.Quality;
	
	D3D11_USAGE usage = desc.Usage;
	UINT bindFlags = desc.BindFlags;
	UINT nCPUAccessFlags = desc.CPUAccessFlags;
	
	switch (usage)
	{
	case D3D11_USAGE_DEFAULT:
		m_nAccessHint |= EAH_GPU_READ | EAH_GPU_WRITE;
		m_textureUsage = TU_GPUREAD_GPUWRITE;
		break;
	case D3D11_USAGE_IMMUTABLE:
		m_nAccessHint |= EAH_GPU_READ | EAH_CPU_WRITE;
		m_textureUsage = TU_GPUREAD_IMMUTABLE;
		break;
	case D3D11_USAGE_DYNAMIC:
		m_nAccessHint |= EAH_GPU_READ;
		if (nCPUAccessFlags & D3D11_CPU_ACCESS_WRITE)
			m_nAccessHint |= EAH_CPU_WRITE;
		m_textureUsage = TU_GPUREAD_CPUWRITE;
		break;
	case D3D11_USAGE_STAGING:
		if (nCPUAccessFlags & D3D11_CPU_ACCESS_READ)
			m_nAccessHint |= EAH_CPU_READ;
		if (nCPUAccessFlags & D3D11_CPU_ACCESS_WRITE)
			m_nAccessHint |= EAH_CPU_WRITE;
		m_textureUsage = TU_GPUREAD_GPUWRITE_CPUREAD_CPUWRITE;
		break;
	default:
		break;
	}

	//if (bindFlags & D3D11_BIND_UNORDERED_ACCESS)
		//m_nAccessHint |= EAH_GPU_UNORDERED;
	//if (desc.MiscFlags & D3D11_RESOURCE_MISC_GENERATE_MIPS)
		//m_nAccessHint |= EAH_GENERATE_MIPS;

	m_pD3D11Texture2D = pD3DTex2D;
	m_pD3DResource = m_pD3D11Texture2D;

	if (m_nUsedFor & HrD3D11Texture::TUF_TEX_RENDERTARGETVIEW)
	{
		CreateRenderTargetView();
	}
}

HrD3D11Texture2D::~HrD3D11Texture2D()
{

}

bool HrD3D11Texture2D::CreateRenderTargetView()
{
	ID3D11RenderTargetView* pRenderTargetView = nullptr;
	HRESULT hr = m_pD3D11Device->CreateRenderTargetView(m_pD3DResource.get(), 0, &pRenderTargetView);
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
	//Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	descDSV.Format = HrD3D11Mapping::GetPixelFormat(m_format);
	if (m_nSampleCount > 1)
	{
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	}
	else
	{
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	}
	descDSV.Texture2D.MipSlice = 0;
	
	ID3D11DepthStencilView* pDepthStencilView = nullptr;
	HRESULT hr = HrD3D11Device::Instance()->GetD3DDevice()->CreateDepthStencilView(m_pD3DResource.get(), &descDSV, &pDepthStencilView);
	if (FAILED(hr))
	{
		TRE("HrD3D11Texture2D::CreateDepthStencilView  Error!");
		return false;
	}
	m_pDepthStencilView = MakeComPtr(pDepthStencilView);
}

bool HrD3D11Texture2D::CreateShaderResourceView()
{
	if (m_pShaderResourceView)
	{
		return true;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	switch (m_format)
	{
	case PF_D24S8:
		desc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		break;
	default:
		desc.Format = HrD3D11Mapping::GetPixelFormat(m_format);
		break;
	}
	if (m_nArraySize > 1)
	{
		
	}
	else
	{
		if (m_nSampleCount > 1)
		{
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
		}
		else
		{
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		}
		desc.Texture2D.MostDetailedMip = 0;
		desc.Texture2D.MipLevels = m_nMipMapsNum;
	}

	ID3D11ShaderResourceView* pShaderResourceView = nullptr;
	HRESULT hr = m_pD3D11Device->CreateShaderResourceView(m_pD3DResource.get(), &desc, &pShaderResourceView);
	if (FAILED(hr))
	{
		TRE("HrD3D11Texture2D::CreateShaderResourceView error!");
		return false;
	}
	m_pShaderResourceView = MakeComPtr(pShaderResourceView);

	return true;
}

void HrD3D11Texture2D::CreateHWResource(HrImage* pImage)
{
	if (m_pD3D11Texture2D)
	{
		return;
	}

	if (pImage)
	{
		m_nWidth = pImage->GetWidht();
		m_nHeight = pImage->GetHeight();
	}

	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
	textureDesc.Width = m_nWidth;
	textureDesc.Height = m_nHeight;
	textureDesc.MipLevels = m_nMipMapsNum;
	textureDesc.ArraySize = m_nArraySize;
	switch (m_format)
	{
	case PF_D24S8:
		textureDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
		break;
	default:
		textureDesc.Format = HrD3D11Mapping::GetPixelFormat(m_format);
		break;
	}

	textureDesc.SampleDesc.Count = m_nSampleCount;
	textureDesc.SampleDesc.Quality = m_nSampleQuality;

	textureDesc.Usage = HrD3D11Mapping::GetTextureUsage(m_textureUsage);
	
	textureDesc.BindFlags = GetD3DTextureBindFlags();
	textureDesc.CPUAccessFlags = GetD3DCPUAccessFlags();
	textureDesc.MiscFlags = 0;

	std::vector<D3D11_SUBRESOURCE_DATA> vecSubRes;
	if (pImage && pImage->GetData()->GetBufferSize() > 0)
	{
		vecSubRes.resize(1);

		vecSubRes[0].pSysMem = pImage->GetData()->GetBufferPoint();
		vecSubRes[0].SysMemPitch = pImage->GetSrcPitch();
		vecSubRes[0].SysMemSlicePitch = 0;
	}

	ID3D11Texture2D* pTempTexture2D = nullptr;
	HRESULT hr = m_pD3D11Device->CreateTexture2D(&textureDesc, vecSubRes.data(), &pTempTexture2D);
	if (FAILED(hr))
	{
		TRE("HrD3D11Texture2D::CreateDepthStencilView create texture Error!");
		return;
	}
	m_pD3D11Texture2D = MakeComPtr(pTempTexture2D);
	m_pD3DResource = m_pD3D11Texture2D;

	if (m_nUsedFor & HrD3D11Texture::TUF_TEX_DEPTHSTENCILVIEW)
	{
		CreateDepthStencilView();
	}

	if (m_nUsedFor & HrD3D11Texture::TUF_TEX_RENDERTARGETVIEW)
	{
		CreateRenderTargetView();
	}

	if (m_nUsedFor & HrD3D11Texture::TUF_TEX_SHADERRESOURCEVIEW)
	{
		CreateShaderResourceView();
	}
}

ID3D11Texture2DPtr HrD3D11Texture2D::GetD3D11Texture()
{
	return m_pD3D11Texture2D;
}
