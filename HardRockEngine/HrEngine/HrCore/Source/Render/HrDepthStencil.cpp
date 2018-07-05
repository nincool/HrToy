#include "Render/HrDepthStencil.h"

using namespace Hr;

HrDepthStencil::HrDepthStencil(uint32 nWidth, uint32 nHeight, EnumPixelFormat format) : m_nWidth(nWidth), m_nHeight(nHeight), m_format(format)
{
}

HrDepthStencil::~HrDepthStencil()
{

}

uint32 HrDepthStencil::GetWidth() const
{
	return m_nWidth;
}

uint32 HrDepthStencil::GetHeight() const
{
	return m_nHeight;
}

HrTexturePtr HrDepthStencil::GetDepthStencilSRV()
{
	return nullptr;
}
