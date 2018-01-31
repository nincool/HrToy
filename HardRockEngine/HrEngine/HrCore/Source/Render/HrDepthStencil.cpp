#include "Render/HrDepthStencil.h"

using namespace Hr;

HrDepthStencil::HrDepthStencil(uint32 nWidth, uint32 nHeight) : m_nWidth(nWidth), m_nHeight(nHeight)
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
