#ifndef _HR_D3D11DEVICE_H_
#define _HR_D3D11DEVICE_H_

#include "HrD3D11RendererPrerequisites.h"

namespace Hr
{
	class HrD3D11Device
	{
	public:
		HrD3D11Device();
		~HrD3D11Device();
		
		HR_INSTANCE(HrD3D11Device);
	public:
		void SetDevice(IHRD3D11Device* pDevice);
		void ReleaseDevice();

	protected:
		HR_SYNTHESIZE(IHRDXGIFactory*, m_pD3D11DXGIFactory, DXGIFactory);
		HR_SYNTHESIZE(IHRDXGIAdapter*, m_pAdapter, DXAdapter);
		HR_SYNTHESIZE(DXGI_FORMAT, m_format, Format);
		HR_SYNTHESIZE_READONLY(IHRD3D11Device*, m_pD3D11Device, Device);
		HR_SYNTHESIZE_READONLY(IHRD3D11DeviceContext*, m_pD3D11ImmediateContext, ImmediateContext);


	};
}


#endif

