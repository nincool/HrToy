#include "HrRenderD3D11DemoTexture.h"

using namespace Hr;
using namespace DirectX;

HrRenderD3D11DemoTexture::HrRenderD3D11DemoTexture()
{
	m_pD3D11Device = nullptr;
	m_pD3D11ImmediateContext = nullptr;
	m_pSwapChain = nullptr;

	m_pSolidColorVS = nullptr;
	m_pSolidColorPS = nullptr;

	m_pInputLayout = nullptr;
	m_pVertexBuffer = nullptr;

	m_pRenderTargetView = nullptr;
	m_pDepthStencilView = nullptr;
}

void HrRenderD3D11DemoTexture::SetD3DDevice(ID3D11Device* pDevice
	, ID3D11DeviceContext* pDeviceContex
	, ID3D11RenderTargetView* pRenderTargetView
	, ID3D11DepthStencilView* pDepthStencilView
	, IDXGISwapChain* pSwapChain)
{
	m_pD3D11Device = pDevice;
	m_pD3D11ImmediateContext = pDeviceContex;
	m_pRenderTargetView = pRenderTargetView;
	m_pDepthStencilView = pDepthStencilView;
	m_pSwapChain = pSwapChain;

}

bool HrRenderD3D11DemoTexture::Init()
{
	return LoadContent();
}

bool HrRenderD3D11DemoTexture::LoadContent()
{
	ID3DBlob* pVSBuffer = nullptr;

	bool bCompileResult = CompileD3DShader(L"HrShader\\TextureMap.fx", "VS_Main", "vs_5_0", &pVSBuffer);
	if (!bCompileResult)
	{
		HRERROR(_T("Compile VS Shader Error!"));
		return false;
	}

	HRESULT rt;
	rt = m_pD3D11Device->CreateVertexShader(pVSBuffer->GetBufferPointer(),
		pVSBuffer->GetBufferSize(), 0, &m_pSolidColorVS);
	if (FAILED(rt))
	{
		HRERROR(_T("Create VS Shader Error!"));
		if (pVSBuffer != nullptr)
		{
			SAFE_RELEASE(pVSBuffer);
		}
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC solidColorLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	uint32 nTotalLayoutElements = ARRAYSIZE(solidColorLayout);
	rt = m_pD3D11Device->CreateInputLayout(solidColorLayout, nTotalLayoutElements,
		pVSBuffer->GetBufferPointer(), pVSBuffer->GetBufferSize(), &m_pInputLayout);
	pVSBuffer->Release();
	if (FAILED(rt))
	{
		HRERROR(_T("Error creating the input layout!"));
		return false;
	}

	ID3DBlob* pPSBuffer = nullptr;
	bCompileResult = CompileD3DShader(L"HrShader\\TextureMap.fx", "PS_Main", "ps_4_0", &pPSBuffer);
	if (bCompileResult == false)
	{
		HRERROR(_T("Error compiling pixel shader!"));
		return false;
	}

	rt = m_pD3D11Device->CreatePixelShader(pPSBuffer->GetBufferPointer(), pPSBuffer->GetBufferSize(), 0, &m_pSolidColorPS);
	pPSBuffer->Release();
	if (FAILED(rt))
	{
		HRERROR(_T("Error creating pixel shader"));
		return false;
	}

	VertexPos vertices[] =
	{
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
	};
	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(VertexPos) * 6;

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory(&resourceData, sizeof(resourceData));
	resourceData.pSysMem = vertices;
	
	rt = m_pD3D11Device->CreateBuffer(&vertexDesc, &resourceData, &m_pVertexBuffer);
	if (FAILED(rt))
	{
		HRERROR(_T("FAILED to create vertex buffer!"));
		return false;
	}


	return true;
}

bool HrRenderD3D11DemoTexture::Render()
{
	XMVECTORF32 Blue = { 0.69f, 0.77f, 0.87f, 1.0f };
	m_pD3D11ImmediateContext->ClearRenderTargetView(m_pRenderTargetView, reinterpret_cast<const float*>(&Blue));
	m_pD3D11ImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	m_pSwapChain->Present(0, 0);

	return true;
}

void HrRenderD3D11DemoTexture::Release()
{

	SAFE_RELEASE(m_pSolidColorVS);
	SAFE_RELEASE(m_pSolidColorPS);
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pVertexBuffer);
}

