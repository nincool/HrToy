#include "HrD3D11GraphicsBuffer.h"
#include "HrD3D11Mapping.h"
#include "HrCore/Include/Kernel/HrLog.h"


using namespace Hr;

HrD3D11GraphicsBuffer::HrD3D11GraphicsBuffer(const ID3D11DevicePtr& pD3D11Device, const ID3D11DeviceContextPtr& pImmediateContext)
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
}

void HrD3D11GraphicsBuffer::BindStream(const char* pBuffer
	, uint64 nBufferSize
	, HrGraphicsBuffer::EnumGraphicsBufferUsage usage
	, HrGraphicsBuffer::EnumGraphicsBufferBind bindFlag)
{
	BOOST_ASSERT(m_pD3D11Buffer == nullptr);

	HrGraphicsBuffer::BindStream(pBuffer, nBufferSize, usage, bindFlag);
	CreateHardwareBuffer(pBuffer);
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
	if (pResourceData != nullptr)
	{
		subResourceData.pSysMem = pResourceData;
		subResourceData.SysMemPitch = 0;
		subResourceData.SysMemSlicePitch = 0;

		pSubResourceData = &subResourceData;
	}

	ID3D11Buffer* pD3D11Buffer = nullptr;
	HRESULT rt = m_pD3D11Device->CreateBuffer(&desc, pSubResourceData, &(pD3D11Buffer));
	if (FAILED(rt))
	{
		HRERROR("HrD3D11GraphicsBuffer CreateHardwareBuffer Error!");
		return;
	}
	m_pD3D11Buffer = MakeComPtr(pD3D11Buffer);
	//if (m_usage == HrGraphicsBuffer::HBB_SHADER_RESOURCE)
	//{
	//	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	//	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	//	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

	//}
}

const ID3D11BufferPtr& HrD3D11GraphicsBuffer::GetD3DGraphicsBuffer()
{
	return m_pD3D11Buffer;
}

void* HrD3D11GraphicsBuffer::Map(HrGraphicsBuffer::EnumGraphicsBufferAccess accessFlag)
{
	D3D11_MAPPED_SUBRESOURCE mapped;
	TIF(m_pImmediateContext->Map(m_pD3D11Buffer.get(), 0, HrD3D11Mapping::GetBufferMap(m_usage, accessFlag), 0, &mapped));
	
	return mapped.pData;
}

void HrD3D11GraphicsBuffer::Unmap()
{
	m_pImmediateContext->Unmap(m_pD3D11Buffer.get(), 0);
}

