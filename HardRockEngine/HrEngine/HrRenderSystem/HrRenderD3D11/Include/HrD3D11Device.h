#ifndef _HR_D3D11DEVICE_H_
#define _HR_D3D11DEVICE_H_

#include "HrD3D11RenderPrerequisite.h"
#include <d3d11.h>
#include <dxgi1_5.h>
#include "HrCommon/include/HrSingleton.h"

namespace Hr
{
	class HrD3D11AdapterList;

	class HrD3D11Device : public HrSingleTon<HrD3D11Device>
	{
	public:
		HrD3D11Device();
		~HrD3D11Device();
		
		bool CreateD3D11Device();

		bool CreateD3DDXGIFactory();
		bool CreateD3DDXDevice();

		bool D3D11EnumerateAdapter();

		const IDXGIFactory1Ptr& GetDXGIFactory1();
		const IDXGIFactory2Ptr& GetDXGIFactory2();
		int GetDXGISubVersion();

		const ID3D11DevicePtr& GetD3DDevice();
		const ID3D11DeviceContextPtr& GetD3DDeviceContext();
	public:
		void Release();

		IDXGIFactory1Ptr m_pDXGIFactory1;
		IDXGIFactory2Ptr m_pDXGIFactory2;
		int m_nDXGISubVersion = 1;

		ID3D11DevicePtr m_pD3D11Device;
		ID3D11DeviceContextPtr m_pD3D11ImmediateContext;

		HR_SYNTHESIZE_READONLY(HrD3D11AdapterList*, m_pAdapterList, AdapterList);
		
	};
}


#endif

