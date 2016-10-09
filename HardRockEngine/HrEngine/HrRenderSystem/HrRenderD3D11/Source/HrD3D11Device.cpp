#include "HrD3D11Device.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrD3D11Adapter.h"
#include "HrD3D11AdapterList.h"
#include "HrCore/Include/HrLog.h"


using namespace Hr;

HrD3D11Device::HrD3D11Device()
{
	m_pD3D11DXGIFactory = nullptr;
	m_pD3D11Device = nullptr;
	m_pD3D11ImmediateContext = nullptr;

	m_pAdapterList = new HrD3D11AdapterList();
}

HrD3D11Device::~HrD3D11Device()
{
}

bool HrD3D11Device::CreateD3D11Device()
{
	CreateD3DDXDevice();
	
	CreateD3DDXGIFactory();
	
	D3D11EnumerateAdapter();

	return true;
}

bool HrD3D11Device::CreateD3DDXGIFactory()
{
	//if (this->GetDXGIFactory() == nullptr)
	//{
	//	IDXGIFactory1* pDXGIFactory = nullptr;
	//	HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&pDXGIFactory);
	//	if (FAILED(hr))
	//	{
	//		return false;
	//	}
	//	this->SetDXGIFactory(pDXGIFactory);
	//}

	IDXGIDevice1 * pDXGIDevice;
	HRESULT hr = m_pD3D11Device->QueryInterface(__uuidof(IDXGIDevice1), (void **)&pDXGIDevice);

	IDXGIAdapter * pDXGIAdapter;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);

	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory1), (void **)&m_pD3D11DXGIFactory);


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
	//deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

	ID3D11Device* pD3DDevice;
	ID3D11DeviceContext* m_pImmediateContext;
	HRESULT hr = D3D11CreateDevice(pDeviceAdapter
		, driverType
		, NULL
		, deviceFlags
		, pFirstFL
		, nFeatureLevels
		, D3D11_SDK_VERSION
		, &pD3DDevice
		, NULL
		, &m_pImmediateContext);
	if (hr != S_OK)
	{
		HRERROR(_T("D3D11CreateDevice Error!"));
		return false;
	}
	this->SetDevice(pD3DDevice);
	this->SetImmediateContext(m_pImmediateContext);

	return true;
}

bool HrD3D11Device::D3D11EnumerateAdapter()
{
	for (uint32 nAdapter = 0;; ++nAdapter)
	{
		IDXGIAdapter1* pDXGIAdapter = nullptr;
		HRESULT hr = this->GetDXGIFactory()->EnumAdapters1(nAdapter, &pDXGIAdapter);
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
	m_pAdapterList->Release();
	SAFE_DELETE(m_pAdapterList);
	SAFE_RELEASE(m_pD3D11ImmediateContext);
	SAFE_RELEASE(m_pD3D11Device);
	SAFE_RELEASE(m_pD3D11DXGIFactory);
}
