#include "HrD3D11DepthStencil.h"
#include "HrD3D11Texture.h"

using namespace Hr;

HrD3D11DepthStencil::HrD3D11DepthStencil(uint32 nWidth, uint32 nHeight) : HrDepthStencil(nWidth, nHeight)
{
	CreateDepthStencilView();
}

HrD3D11DepthStencil::~HrD3D11DepthStencil()
{
}

const ID3D11DepthStencilViewPtr& HrD3D11DepthStencil::GetDepthStencilView()
{
	BOOST_ASSERT(m_pTexDepthStencilView);
	return m_pTexDepthStencilView->GetD3DDepthStencilView();
}

bool HrD3D11DepthStencil::CreateDepthStencilView()
{
	m_pTexDepthStencilView = HrMakeSharedPtr<HrD3D11Texture2D>(m_nWidth, m_nHeight, HrD3D11Texture::D3D_TEX_DEPTHSTENCILVIEW);

	return true;
}

