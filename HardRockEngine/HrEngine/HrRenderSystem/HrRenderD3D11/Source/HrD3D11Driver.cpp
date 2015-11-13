#include "HrD3D11Driver.h"

using namespace Hr;

HrD3D11Driver::HrD3D11Driver(unsigned int nAdapterNumer, IHRDXGIAdapter* pDXGIAdapter)
{
	m_nApdapterNumber = nAdapterNumer;
	m_pDXGIAdapter = pDXGIAdapter;
	if (m_pDXGIAdapter != nullptr)
	{
		m_pDXGIAdapter->AddRef();
		m_pDXGIAdapter->GetDesc1(&m_AdapterIdentifier);
	}
}

HrD3D11Driver::~HrD3D11Driver()
{
	SAFE_RELEASE(m_pDXGIAdapter);
}

std::string Hr::HrD3D11Driver::GetDriverDescription() const
{
	size_t size = wcslen(m_AdapterIdentifier.Description);
	char * str = new char[size + 1];

	wcstombs(str, m_AdapterIdentifier.Description, size);
	str[size] = '\0';
	std::string driverDescription = str;
	delete[] str;
	HrStringUtil::Trim(driverDescription);

	return  driverDescription;
}

