#include "HrD3D11Device.h"

using namespace Hr;

HR_INSTANCE_DEF(HrD3D11Device);

HrD3D11Device::HrD3D11Device()
{
	m_pD3D11DXGIFactory = nullptr;

	m_pD3D11Device = nullptr;
	m_pD3D11ImmediateContext = nullptr;
}

HrD3D11Device::~HrD3D11Device()
{
}

void HrD3D11Device::SetDevice(IHRD3D11Device* pDevice)
{
	ReleaseDevice();
	
	m_pD3D11Device = pDevice;
	m_pD3D11ImmediateContext->ClearState();

	m_pD3D11Device->GetImmediateContext(&m_pD3D11ImmediateContext);
}

void HrD3D11Device::ReleaseDevice()
{
	if (m_pD3D11ImmediateContext != nullptr)
	{
		m_pD3D11ImmediateContext->Flush();
	}
	SAFE_RELEASE(m_pD3D11Device);
}
