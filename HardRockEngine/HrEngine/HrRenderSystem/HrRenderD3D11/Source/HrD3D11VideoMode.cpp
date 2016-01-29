#include "HrD3D11VideoMode.h"

namespace Hr
{

	HrD3D11VideoMode::HrD3D11VideoMode(uint32 nWidth, uint32 nHeight, DXGI_FORMAT format)
	{
		m_nWidth = nWidth;
		m_nHeight = nHeight;
		m_format = format;
	}

	HrD3D11VideoMode::~HrD3D11VideoMode()
	{
	}

	uint32 HrD3D11VideoMode::GetColorDepth()
	{
		uint32_t colorDepth;
		if ((m_format == DXGI_FORMAT_R8G8B8A8_UNORM)
			|| (m_format == DXGI_FORMAT_R8G8B8A8_UNORM_SRGB)
			|| (m_format == DXGI_FORMAT_B8G8R8A8_UNORM)
			|| (m_format == DXGI_FORMAT_B8G8R8A8_UNORM_SRGB)
			|| (m_format == DXGI_FORMAT_R10G10B10A2_UNORM))
		{
			colorDepth = 32;
		}
		else
		{
			colorDepth = 16;
		}

		return colorDepth;
	}


	bool operator<(HrD3D11VideoMode const & lhs, HrD3D11VideoMode const & rhs)
	{
		if (lhs.GetWidth() < rhs.GetWidth())
		{
			return true;
		}
		else
		{
			if (lhs.GetWidth() == rhs.GetWidth())
			{
				if (lhs.GetHeight() < rhs.GetHeight())
				{
					return true;
				}
				else
				{
					if (lhs.GetHeight() == rhs.GetHeight())
					{
						if (lhs.GetFormat() < rhs.GetFormat())
						{
							return true;
						}
					}
				}
			}
		}

		return false;
	}

	bool operator==(HrD3D11VideoMode const & lhs, HrD3D11VideoMode const & rhs)
	{
		return (lhs.GetWidth() == rhs.GetWidth())
			&& (lhs.GetHeight() == rhs.GetHeight())
			&& (lhs.GetFormat() == rhs.GetFormat());
	}
}


