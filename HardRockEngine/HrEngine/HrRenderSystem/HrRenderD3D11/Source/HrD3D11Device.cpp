#include "HrD3D11Device.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrD3D11Adapter.h"
#include "HrD3D11AdapterList.h"
#include "HrCore/Include/Kernel/HrLog.h"


using namespace Hr;

HrD3D11Device::HrD3D11Device()
{
	m_pAdapterList = new HrD3D11AdapterList();
}

HrD3D11Device::~HrD3D11Device()
{
	Release();
}

bool HrD3D11Device::CreateD3D11Device()
{
	CreateD3DDXDevice();
	
	CreateD3DDXGIFactory();
	
	D3D11EnumerateAdapter();

	return true;
}

bool HrD3D11Device::CreateD3DDXDevice()
{
	IDXGIAdapter* pDeviceAdapter = nullptr;

	// determine feature levels
	D3D_FEATURE_LEVEL requestedLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};
	D3D_FEATURE_LEVEL* pFirstFL = &requestedLevels[0];
	D3D_FEATURE_LEVEL* pLastFL = &requestedLevels[1];
	UINT nFeatureLevels = static_cast<UINT>(pLastFL - pFirstFL + 1);

	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;

	UINT deviceFlags = 0;
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

	ID3D11Device* pD3DDevice;
	ID3D11DeviceContext* pImmediateContext;
	HRESULT hr = D3D11CreateDevice(pDeviceAdapter
		, driverType
		, NULL
		, deviceFlags
		, pFirstFL
		, nFeatureLevels
		, D3D11_SDK_VERSION
		, &pD3DDevice
		, NULL
		, &pImmediateContext);
	if (hr != S_OK)
	{
		HRERROR(_T("D3D11CreateDevice Error!"));
		return false;
	}

	m_pD3D11Device = MakeComPtr(pD3DDevice);
	m_pD3D11ImmediateContext = MakeComPtr(pImmediateContext);

	return true;
}

bool HrD3D11Device::CreateD3DDXGIFactory()
{
	IDXGIDevice1 * pDXGIDevice;
	HRESULT hr = m_pD3D11Device->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&pDXGIDevice));

	IDXGIAdapter * pDXGIAdapter;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&pDXGIAdapter));

	IDXGIFactory1* pDXGIFactory1;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&pDXGIFactory1));
	m_pDXGIFactory1 = MakeComPtr(pDXGIFactory1);
	m_nDXGISubVersion = 1;

	IDXGIFactory2* pDXGIFactory2 = nullptr;
	pDXGIFactory1->QueryInterface(IID_IDXGIFactory2, reinterpret_cast<void**>(&pDXGIFactory2));
	if (pDXGIFactory2 != nullptr)
	{
		m_pDXGIFactory2 = MakeComPtr(pDXGIFactory2);
		m_nDXGISubVersion = 2;
	}

	return true;
}


bool HrD3D11Device::D3D11EnumerateAdapter()
{
	for (uint32 nAdapter = 0;; ++nAdapter)
	{
		IDXGIAdapter1* pDXGIAdapter = nullptr;
		HRESULT hr = this->GetDXGIFactory1()->EnumAdapters1(nAdapter, &pDXGIAdapter);
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

		HrD3D11Adapter* pAdapter = new HrD3D11Adapter(nAdapter, pDXGIAdapter);
		pAdapter->EnumerateModeList();
		this->GetAdapterList()->AddOneAdapter(pAdapter);
	}

	return true;
}

void HrD3D11Device::Release()
{
	if (m_pAdapterList)
	{
		m_pAdapterList->Release();
	}
	SAFE_DELETE(m_pAdapterList);
}

const IDXGIFactory1Ptr& HrD3D11Device::GetDXGIFactory1()
{
	return m_pDXGIFactory1;
}

const IDXGIFactory2Ptr& HrD3D11Device::GetDXGIFactory2()
{
	return m_pDXGIFactory2;
}

const ID3D11DevicePtr& HrD3D11Device::GetD3DDevice()
{
	return m_pD3D11Device;
}

const ID3D11DeviceContextPtr& HrD3D11Device::GetD3DDeviceContext()
{
	return m_pD3D11ImmediateContext;
}

int HrD3D11Device::GetDXGISubVersion()
{
	return m_nDXGISubVersion;
}
