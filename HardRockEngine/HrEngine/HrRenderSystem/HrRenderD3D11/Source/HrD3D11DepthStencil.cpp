#include "HrD3D11DepthStencil.h"
#include "HrD3D11Texture.h"

using namespace Hr;

HrD3D11DepthStencil::HrD3D11DepthStencil(uint32 nWidth, uint32 nHeight, EnumPixelFormat format, uint32 texD3DUsage) : HrDepthStencil(nWidth, nHeight, format)
{
	m_texD3DUsage = texD3DUsage;
	CreateDepthStencilView();
}

HrD3D11DepthStencil::~HrD3D11DepthStencil()
{
}


HrTexturePtr HrD3D11DepthStencil::GetDepthStencilSRV()
{
	return m_pTexDepthStencilView;
}

const ID3D11DepthStencilViewPtr& HrD3D11DepthStencil::GetDepthStencilView()
{
	BOOST_ASSERT(m_pTexDepthStencilView);
	return m_pTexDepthStencilView->GetD3DDepthStencilView();
}

bool HrD3D11DepthStencil::CreateDepthStencilView()
{
	m_pTexDepthStencilView = HrMakeSharedPtr<HrD3D11Texture2D>(m_nWidth
		, m_nHeight
		, 1, 1, 0
		, HrTexture::EAH_GPU_READ | HrTexture::EAH_GPU_WRITE
		, m_texD3DUsage
		, m_format);

	return true;
}

const ID3D11ShaderResourceViewPtr& HrD3D11DepthStencil::GetDepthStencilShaderResouceView()
{
	return m_pTexDepthStencilView->GetD3D11ShaderResourceView();
}

