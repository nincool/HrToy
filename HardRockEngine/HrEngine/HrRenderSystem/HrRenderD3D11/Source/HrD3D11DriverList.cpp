#include "HrD3D11DriverList.h"
#include "HrD3D11Driver.h"

using namespace Hr;

HrD3D11DriverList::HrD3D11DriverList(IHRDXGIFactory* pDXGIFactory)
{
	Enumerate(pDXGIFactory);
}

HrD3D11DriverList::~HrD3D11DriverList()
{
	for (uint32 i = 0; i < m_vecDrivers.size(); ++i)
	{
		delete (m_vecDrivers[i]);
	}
	m_vecDrivers.clear();
}

bool HrD3D11DriverList::Enumerate(IHRDXGIFactory* pDXGIFactory)
{
	for (uint32 nAdapter = 0; ; ++nAdapter)
	{
		IHRDXGIAdapter* pDXGIAdapter = nullptr;
		HRESULT hr = pDXGIFactory->EnumAdapters1(nAdapter, &pDXGIAdapter);
		if (DXGI_ERROR_NOT_FOUND == hr)
		{
			hr = S_OK;
			break;
		}
		if (FAILED(hr))
		{
			SAFE_DELETE(pDXGIAdapter);
			return false;
		}

		HrD3D11Driver* pDriver = new HrD3D11Driver(nAdapter, pDXGIAdapter);
		m_vecDrivers.push_back(pDriver);

		SAFE_RELEASE(pDXGIAdapter);
	}

	return true;
}

HrD3D11Driver* Hr::HrD3D11DriverList::GetDefaultDriver()
{
	if (m_vecDrivers.size() > 0)
	{
		return m_vecDrivers[0];
	}

	return nullptr;
}
