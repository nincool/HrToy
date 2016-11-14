#include "HrD3D11GraphicsBuffer.h"
#include "HrD3D11Mapping.h"
#include "HrCore/Include/Kernel/HrLog.h"


using namespace Hr;

HrD3D11GraphicsBuffer::HrD3D11GraphicsBuffer(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pImmediateContext)
{
	m_pD3D11Device = pD3D11Device;
	m_pImmediateContext = pImmediateContext;

	m_pD3D11Buffer = nullptr;
}

HrD3D11GraphicsBuffer::HrD3D11GraphicsBuffer(HrD3D11GraphicsBuffer& hardwareBuffer)
{
	m_nByteWidth = hardwareBuffer.m_nByteWidth;
	m_pD3D11Device = hardwareBuffer.m_pD3D11Device;
	m_pImmediateContext = hardwareBuffer.m_pImmediateContext;

	m_pD3D11Buffer = nullptr;
}

HrD3D11GraphicsBuffer::HrD3D11GraphicsBuffer(HrD3D11GraphicsBuffer&& hardwareBuffer)
{
	m_nByteWidth = hardwareBuffer.m_nByteWidth;
	m_pD3D11Device = hardwareBuffer.m_pD3D11Device;
	m_pImmediateContext = hardwareBuffer.m_pImmediateContext;

	m_pD3D11Buffer = nullptr;
}

HrD3D11GraphicsBuffer::~HrD3D11GraphicsBuffer()
{
	SAFE_RELEASE(m_pD3D11Buffer);
}

void HrD3D11GraphicsBuffer::BindStream(char* pBuffer
	, uint32 nBufferSize
	, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
	, HrGraphicsBuffer::EnumGraphicsBufferBind bindFlag)
{
	BOOST_ASSERT(m_pD3D11Buffer == nullptr);

	HrGraphicsBuffer::BindStream(pBuffer, nBufferSize, usage, bindFlag);
}

void HrD3D11GraphicsBuffer::CreateHardwareBuffer(const void* pResourceData)
{
	D3D11_BUFFER_DESC desc = {0};
	desc.Usage = HrD3D11Mapping::GetGraphicsUsage(m_usage);
	desc.CPUAccessFlags = HrD3D11Mapping::GetCPUAccessFlag(m_usage);
	desc.BindFlags = HrD3D11Mapping::GetGraphicsBindFlag(m_bindFlag);
	desc.ByteWidth = m_nByteWidth;

	D3D11_SUBRESOURCE_DATA subResourceData = { 0 };
	D3D11_SUBRESOURCE_DATA* pSubResourceData = nullptr;

	{
		subResourceData.pSysMem = pResourceData;
		subResourceData.SysMemPitch = 0;
		subResourceData.SysMemSlicePitch = 0;

		pSubResourceData = &subResourceData;
	}

	HRESULT rt = m_pD3D11Device->CreateBuffer(&desc, pSubResourceData, &m_pD3D11Buffer);
	if (FAILED(rt))
	{
		HRERROR("HrD3D11GraphicsBuffer CreateHardwareBuffer Error!");
		return;
	}
}

ID3D11Buffer* HrD3D11GraphicsBuffer::GetGraphicsBuffer()
{
	return m_pD3D11Buffer;
}

void* HrD3D11GraphicsBuffer::Map(HrGraphicsBuffer::EnumGraphicsBufferAccess accessFlag)
{
	D3D11_MAPPED_SUBRESOURCE mapped;
	TIF(m_pImmediateContext->Map(m_pD3D11Buffer, 0, HrD3D11Mapping::GetBufferMap(m_usage, accessFlag), 0, &mapped));
	return mapped.pData;
}

void HrD3D11GraphicsBuffer::Unmap()
{
	m_pImmediateContext->Unmap(m_pD3D11Buffer, 0);
}

