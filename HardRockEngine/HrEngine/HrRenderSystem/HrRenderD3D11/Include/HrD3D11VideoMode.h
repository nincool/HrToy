#ifndef _HR_D3D11VIEDOMODE_H_
#define _HR_D3D11VIEDOMODE_H_

#include "HrD3D11RenderPrerequisite.h"
#include "HrD3D11Device.h"

namespace Hr
{
	class HrD3D11VideoMode
	{
	public:
		HrD3D11VideoMode(uint32 nWidth, uint32 nHeight, DXGI_FORMAT format);
		~HrD3D11VideoMode();

		uint32 GetColorDepth();
	private:
		HR_SYNTHESIZE_READONLY(uint32, m_nWidth, Width);
		HR_SYNTHESIZE_READONLY(uint32, m_nHeight, Height);
		HR_SYNTHESIZE_READONLY(DXGI_FORMAT, m_format, Format);
	};

	bool operator<(HrD3D11VideoMode const & lhs, HrD3D11VideoMode const & rhs);
	bool operator==(HrD3D11VideoMode const & lhs, HrD3D11VideoMode const & rhs);
}

#endif


