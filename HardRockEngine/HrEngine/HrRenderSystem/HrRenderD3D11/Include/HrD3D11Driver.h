#ifndef _HR_D3D11DRIVER_H_
#define _HR_D3D11DRIVER_H_

#include "HrD3D11RendererPrerequisites.h"

namespace Hr
{
	class HrD3D11Driver
	{
	public:
		HrD3D11Driver(unsigned int nAdapterNumer, IHRDXGIAdapter* pDXGIAdapter);
		~HrD3D11Driver();

		std::string GetDriverDescription() const;

		IHRDXGIAdapter* GetDeviceAdapter() const
		{
			return m_pDXGIAdapter;
		}
	private:
		unsigned int m_nApdapterNumber;
		DXGI_ADAPTER_DESC1 m_AdapterIdentifier;

		IHRDXGIAdapter* m_pDXGIAdapter;
	};
}

#endif




