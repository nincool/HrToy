#ifndef _HR_D3D11DEVICE_H_
#define _HR_D3D11DEVICE_H_

#include "HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"
#include <d3d11.h>

namespace Hr
{
	class HrD3D11AdapterList;

	class HrD3D11Device : public RenderSysAllocatedObject
	{
	public:
		HrD3D11Device();
		~HrD3D11Device();
		
		static HrD3D11Device& GetInstance();
		static void ReleaseInstance();

		bool CreateD3D11Device();

		bool CreateD3DDXGIFactory();
		bool CreateD3DDXDevice();

		bool D3D11EnumerateAdapter();
	public:
		void Release();

		HR_SYNTHESIZE(IDXGIFactory1*, m_pD3D11DXGIFactory, DXGIFactory);

		HR_SYNTHESIZE(ID3D11Device*, m_pD3D11Device, Device);
		HR_SYNTHESIZE(ID3D11DeviceContext*, m_pD3D11ImmediateContext, ImmediateContext);
		HR_SYNTHESIZE_READONLY(HrD3D11AdapterList*, m_pAdapterList, AdapterList);
	private:
		static HrD3D11DevicePtr m_s_pUniqueDevicePtr;
		
	};
}


#endif

