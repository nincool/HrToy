#include "HrRenderD3D11Demo.h"
#include <D3Dcompiler.h>

using namespace Hr;
using namespace DirectX;

HrRenderD3D11Demo::HrRenderD3D11Demo()
{
	m_pD3D11Device = nullptr;
	m_pD3D11ImmediateContext = nullptr;

	m_pSolidColorVS = nullptr;
	m_pSolidColorPS = nullptr;

	m_pInputLayout = nullptr;
	m_pVertexBuffer = nullptr;
}

void HrRenderD3D11Demo::SetD3DDevice(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContex)
{
	m_pD3D11Device = pDevice;
	m_pD3D11ImmediateContext = pDeviceContex;
}

bool HrRenderD3D11Demo::Init()
{

	return true;
}

bool HrRenderD3D11Demo::Render()
{
	unsigned int stride = sizeof(VertexPos);
	unsigned int offset = 0;

	m_pD3D11ImmediateContext->IASetInputLayout(m_pInputLayout);
	m_pD3D11ImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pD3D11ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pD3D11ImmediateContext->VSSetShader(m_pSolidColorVS, 0, 0);
	m_pD3D11ImmediateContext->PSSetShader(m_pSolidColorPS, 0, 0);
	m_pD3D11ImmediateContext->Draw(3, 0);

	return true;
}

void HrRenderD3D11Demo::Release()
{

}

bool HrRenderD3D11Demo::LoadContent()
{
	ID3DBlob* vsBuffer = 0;

	bool compileResult = CompileD3DShader(L"SolidGreenColor.fx", "VS_Main", "vs_4_0", &vsBuffer);
	if (compileResult == false)
	{
		return false;
	}

	HRESULT d3dResult;

	d3dResult = m_pD3D11Device->CreateVertexShader(vsBuffer->GetBufferPointer(),
		vsBuffer->GetBufferSize(), 0, &m_pSolidColorVS);
	if (FAILED(d3dResult))
	{
		if (vsBuffer)
			vsBuffer->Release();

		return false;
	}

	D3D11_INPUT_ELEMENT_DESC solidColorLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	unsigned int totalLayoutElements = ARRAYSIZE(solidColorLayout);

	d3dResult = m_pD3D11Device->CreateInputLayout(solidColorLayout, totalLayoutElements,
		vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), &m_pInputLayout);

	vsBuffer->Release();

	if (FAILED(d3dResult))
	{
		return false;
	}

	ID3DBlob* psBuffer = 0;
	compileResult = CompileD3DShader(L"SolidGreenColor.fx", "PS_Main", "ps_4_0", &psBuffer);
	if (compileResult == false)
	{
		return false;
	}

	d3dResult = m_pD3D11Device->CreatePixelShader(psBuffer->GetBufferPointer(),
		psBuffer->GetBufferSize(), 0, &m_pSolidColorPS);

	psBuffer->Release();

	if (FAILED(d3dResult))
	{
		return false;
	}

	VertexPos vertices[] =
	{
		XMFLOAT3(0.5f, 0.5f, 0.5f),
		XMFLOAT3(0.5f, -0.5f, 0.5f),
		XMFLOAT3(-0.5f, -0.5f, 0.5f)
	};

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(VertexPos) * 3;

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory(&resourceData, sizeof(resourceData));
	resourceData.pSysMem = vertices;

	d3dResult = m_pD3D11Device->CreateBuffer(&vertexDesc, &resourceData, &m_pVertexBuffer);

	if (FAILED(d3dResult))
	{
		return false;
	}

	return true;
}

bool HrRenderD3D11Demo::CompileD3DShader(LPCWSTR pFilePath, char* pEntry, char* pTarget, ID3DBlob** pBuffer)
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	ID3DBlob* errorBuffer = 0;
	HRESULT result;

	result = D3DCompileFromFile(pFilePath, 0, 0, pEntry, pTarget,
		shaderFlags, 0, pBuffer, 0);

	if (FAILED(result))
	{
		if (errorBuffer != 0)
		{
			OutputDebugStringA((char*)errorBuffer->GetBufferPointer());
			errorBuffer->Release();
		}

		return false;
	}

	if (errorBuffer != 0)
		errorBuffer->Release();

	return true;
}
