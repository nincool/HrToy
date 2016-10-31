#include "HrD3D11HardwareBuffer.h"
#include "HrCore/Include/Kernel/HrLog.h"

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

void HrD3D11HardwareBuffer::BindStream(char* pBuffer
	, uint32 nBufferSize
	, HrGraphicsBuffer::EnumHardwareBufferUsage usage
	, HrGraphicsBuffer::EnumHardwareBufferBind bindFlag)
{
	if (m_pD3D11Buffer)
	{
		SAFE_RELEASE(m_pD3D11Buffer);
	}

	HrHardwareBuffer::BindStream(pBuffer, nBufferSize, usage, bindFlag);
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
	case HrGraphicsBuffer::HBU_GPUREAD_GPUWRITE:
		usage = D3D11_USAGE_DEFAULT;
		cpuAccessFlags = 0;
		break;
	case HrGraphicsBuffer::HBU_GPUREAD_CPUWRITE:
		usage = D3D11_USAGE_DYNAMIC;
		cpuAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case HrGraphicsBuffer::HBU_GPUREAD_IMMUTABLE:
		usage = D3D11_USAGE_IMMUTABLE;
		cpuAccessFlags = 0;
		break;
	case HrGraphicsBuffer::HBU_GPUREAD_GPUWRITE_CPUREAD_CPUWRITE:
		usage = D3D11_USAGE_STAGING;
		cpuAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	default:
		break;
	}

	switch (m_bindFlag)
	{
	case HrGraphicsBuffer::HBB_VERTEXT:
		bindFlags = D3D11_BIND_VERTEX_BUFFER;
		break;
	case HrGraphicsBuffer::HBB_INDEX:
		bindFlags = D3D11_BIND_INDEX_BUFFER;
		break;
	case HrGraphicsBuffer::HBB_CONST:
		bindFlags = D3D11_BIND_CONSTANT_BUFFER;
		break;
	}
	
	miscFlags = 0;
}

ID3D11Buffer* HrD3D11HardwareBuffer::GetGraphicsBuffer()
{
	return m_pD3D11Buffer;
}

