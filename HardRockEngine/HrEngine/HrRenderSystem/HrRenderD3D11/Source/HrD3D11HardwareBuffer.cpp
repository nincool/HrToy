#include "HrD3D11HardwareBuffer.h"
#include "HrCore/Include/HrLog.h"

using namespace Hr;

HrD3D11HardwareBuffer::HrD3D11HardwareBuffer(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pImmediateContext)
{
	m_pD3D11Device = pD3D11Device;
	m_pImmediateContext = pImmediateContext;

	m_pD3D11Buffer = nullptr;
}

HrD3D11HardwareBuffer::HrD3D11HardwareBuffer(HrD3D11HardwareBuffer& hardwareBuffer)
{
	m_nByteWidth = hardwareBuffer.m_nByteWidth;
	m_pD3D11Device = hardwareBuffer.m_pD3D11Device;
	m_pImmediateContext = hardwareBuffer.m_pImmediateContext;

	m_pD3D11Buffer = nullptr;
}

HrD3D11HardwareBuffer::HrD3D11HardwareBuffer(HrD3D11HardwareBuffer&& hardwareBuffer)
{
	m_nByteWidth = hardwareBuffer.m_nByteWidth;
	m_pD3D11Device = hardwareBuffer.m_pD3D11Device;
	m_pImmediateContext = hardwareBuffer.m_pImmediateContext;

	m_pD3D11Buffer = nullptr;
}

HrD3D11HardwareBuffer::~HrD3D11HardwareBuffer()
{

}

void HrD3D11HardwareBuffer::BindStream(char* pBuffer, uint32 nBufferSize, IGraphicsBuffer::EnumHardwareBufferUsage usage)
{
	HrHardwareBuffer::BindStream(pBuffer, nBufferSize, usage);
	CreateHardwareBuffer(pBuffer);
}

void HrD3D11HardwareBuffer::CreateHardwareBuffer(const void* pResourceData)
{
	D3D11_BUFFER_DESC desc = {0};
	GetD3DBufferDesc(desc.Usage, desc.CPUAccessFlags, desc.BindFlags, desc.MiscFlags);
	desc.ByteWidth = m_nByteWidth;

	D3D11_SUBRESOURCE_DATA subResourceData = { 0 };
	D3D11_SUBRESOURCE_DATA* pSubResourceData = nullptr;
	if (pResourceData != nullptr)
	{
		subResourceData.pSysMem = pResourceData;
		subResourceData.SysMemPitch = 0;
		subResourceData.SysMemSlicePitch = 0;

		pSubResourceData = &subResourceData;
	}

	HRESULT rt = m_pD3D11Device->CreateBuffer(&desc, pSubResourceData, &m_pD3D11Buffer);
	if (FAILED(rt))
	{
		HRERROR("HrD3D11HardwareBuffer CreateHardwareBuffer Error!");
		return;
	}
}

void HrD3D11HardwareBuffer::GetD3DBufferDesc(D3D11_USAGE& usage, UINT& cpuAccessFlags, UINT& bindFlags, UINT& miscFlags)
{
	switch (m_usage)
	{
	case IGraphicsBuffer::HBU_GPUREAD_GPUWRITE:
		usage = D3D11_USAGE_DEFAULT;
		cpuAccessFlags = 0;
		break;
	case IGraphicsBuffer::HBU_GPUREAD_CPUWRITE:
		usage = D3D11_USAGE_DYNAMIC;
		cpuAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case IGraphicsBuffer::HBU_GPUREAD_IMMUTABLE:
		usage = D3D11_USAGE_IMMUTABLE;
		cpuAccessFlags = 0;
		break;
	case IGraphicsBuffer::HBU_GPUREAD_GPUWRITE_CPUREAD_CPUWRITE:
		usage = D3D11_USAGE_STAGING;
		cpuAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	default:
		break;
	}

	bindFlags = D3D11_BIND_VERTEX_BUFFER;
	miscFlags = 0;
}

ID3D11Buffer* HrD3D11HardwareBuffer::GetGraphicsBuffer()
{
	return m_pD3D11Buffer;
}

