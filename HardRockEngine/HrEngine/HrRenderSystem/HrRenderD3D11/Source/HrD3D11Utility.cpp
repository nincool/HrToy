#include "HrD3D11Utility.h"
#include "HrD3D11Device.h"

using namespace Hr;

HrD3D11Utility::HrD3D11Utility()
{
}


HrD3D11Utility::~HrD3D11Utility()
{
}

bool HrD3D11Utility::CreateDXGI()
{
	if (HrD3D11Device::GetInstance()->GetDXGIFactory() == nullptr)
	{
		IHRDXGIFactory* pDXGIFactory = nullptr;
		HRESULT hr = CreateDXGIFactory1(__uuidof(IHRDXGIFactory), (void**)&pDXGIFactory);
		if (FAILED(hr))
		{
			return false;
		}
		HrD3D11Device::GetInstance()->SetDXGIFactory(pDXGIFactory);
	}

	return true;
}

