#include "HrD3D11HardwareBuffer.h"

using namespace Hr;

HrD3D11HardwareBuffer::HrD3D11HardwareBuffer(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pImmediateContext, UINT nByteWidth) : HrHardwareBuffer(nByteWidth)
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

	}
}

void HrD3D11HardwareBuffer::GetD3DBufferDesc(D3D11_USAGE& usage, UINT& cpuAccessFlags, UINT& bindFlags, UINT& miscFlags)
{
	usage = D3D11_USAGE_DEFAULT;
	cpuAccessFlags = 0;
	bindFlags = D3D11_BIND_VERTEX_BUFFER;
	miscFlags = 0;
}



//VertexPos vertices[] =
//{
//	XMFLOAT3(0.5f, 0.5f, 0.5f),
//	XMFLOAT3(0.5f, -0.5f, 0.5f),
//	XMFLOAT3(-0.5f, -0.5f, 0.5f)
//};
//
//D3D11_BUFFER_DESC vertexDesc;
//ZeroMemory(&vertexDesc, sizeof(vertexDesc));
//vertexDesc.Usage = D3D11_USAGE_DEFAULT;
//vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//vertexDesc.ByteWidth = sizeof(VertexPos) * 3;
//
//D3D11_SUBRESOURCE_DATA resourceData;
//ZeroMemory(&resourceData, sizeof(resourceData));
//resourceData.pSysMem = vertices;
//
//d3dResult = m_pD3D11Device->CreateBuffer(&vertexDesc, &resourceData, &m_pVertexBuffer);
//
//if (FAILED(d3dResult))
//{
//	return false;
//}
