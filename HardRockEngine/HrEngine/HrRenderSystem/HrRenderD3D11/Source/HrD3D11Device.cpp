#include "HrD3D11Device.h"

using namespace Hr;

HrD3D11Adapter::HrD3D11Adapter(unsigned int nAdapterNumer, IHRDXGIAdapter* pDXGIAdapter)
{
	m_nApdapterNumber = nAdapterNumer;
	m_pDXGIAdapter = pDXGIAdapter;
	if (m_pDXGIAdapter != nullptr)
	{
		m_pDXGIAdapter->AddRef();
		m_pDXGIAdapter->GetDesc1(&m_AdapterIdentifier);
	}
}

HrD3D11Adapter::~HrD3D11Adapter()
{
	SAFE_RELEASE(m_pDXGIAdapter);
}

HrString Hr::HrD3D11Adapter::GetDriverDescription() const
{
	size_t size = wcslen(m_AdapterIdentifier.Description);
	TCHAR * str = new TCHAR[size + 1];

	//wcstombs(str, m_AdapterIdentifier.Description, size);
	memcpy((void*)str, (void*)(m_AdapterIdentifier.Description), size);
	str[size] = '\0';
	HrString driverDescription = str;
	delete[] str;
	HrStringUtil::Trim(driverDescription);

	return driverDescription;
}

void Hr::HrD3D11Adapter::Release()
{
	for (auto ite : m_vecEnumOutputInfo)
	{
		ite->Release();
		SAFE_DELETE(ite);
	}
	m_vecEnumOutputInfo.clear();
	SAFE_RELEASE(m_pDXGIAdapter);
}

/////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////

HR_INSTANCE_DEF(HrD3D11Device);

HrD3D11Device::HrD3D11Device()
{
	m_pD3D11DXGIFactory = nullptr;
	m_pAdapter = nullptr;
	m_format = DXGI_FORMAT_R8G8B8A8_UNORM;
	
	m_pD3D11Device = nullptr;
	m_pD3D11ImmediateContext = nullptr;
	m_nHeight = 0;
	m_nWidth = 0;

	m_pSwapChain = nullptr;
	m_pRenderTargetView = nullptr;
	m_pDepthStencil = nullptr;
	m_pDepthStencilView = nullptr;

	ZeroMemory(&m_swapChainDesc, sizeof(DXGI_HR_SWAP_CHAIN_DESC));
}

HrD3D11Device::~HrD3D11Device()
{
}

void HrD3D11Device::SetDevice(IHRD3D11Device* pDevice)
{
	if (m_pD3D11Device != nullptr)
	{
		if (m_pD3D11ImmediateContext != nullptr)
		{
			m_pD3D11ImmediateContext->Flush();
		}
		SAFE_RELEASE(m_pD3D11ImmediateContext);
		SAFE_RELEASE(m_pD3D11Device);
	}
	m_pD3D11Device = pDevice;
	m_pD3D11Device->GetImmediateContext(&m_pD3D11ImmediateContext);
	m_pD3D11ImmediateContext->ClearState();
}

void HrD3D11Device::Release()
{
	if (m_pD3D11ImmediateContext != nullptr)
	{
		m_pD3D11ImmediateContext->Flush();
	}
	SAFE_RELEASE(m_pD3D11ImmediateContext);
	SAFE_RELEASE(m_pD3D11Device);
	SAFE_RELEASE(m_pD3D11DXGIFactory);

	for (auto ite : m_vecAdapters)
	{
		ite->Release();
	}
}

HrD3D11Adapter* Hr::HrD3D11Device::GetCurrentAdapter()
{
	if (m_pAdapter == nullptr)
	{
		if (m_vecAdapters.size() > 0)
		{
			m_pAdapter = m_vecAdapters[0];
		}
		else
		{
			return nullptr;
		}
	}

	return m_pAdapter;
}
