#include "HrRenderD3D11DemoPipleline.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"
#include "DirectXTK/Inc/WICTextureLoader.h"
#include "DirectXTK/Inc/SpriteBatch.h"
#include "DirectXFX11/inc/d3dx11effect.h"
#include "HrCore/Include/Render/HrCamera.h"
#include "HrMath/Include/HrMath.h"

using namespace Hr;
using namespace DirectX;

const XMFLOAT4 White = { 1.0f, 1.0f, 1.0f, 1.0f };
const XMFLOAT4 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
const XMFLOAT4 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
const XMFLOAT4 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
const XMFLOAT4 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
const XMFLOAT4 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
const XMFLOAT4 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
const XMFLOAT4 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
const XMFLOAT4 Silver = { 0.75f, 0.75f, 0.75f, 1.0f };

HrRenderD3D11DemoPipleline::HrRenderD3D11DemoPipleline()
{
	m_pD3D11Device = nullptr;
	m_pD3D11ImmediateContext = nullptr;
	m_pSwapChain = nullptr;

	m_pRenderTargetView = nullptr;
	m_pDepthStencilView = nullptr;

	m_pEffect = nullptr;
	m_pInputLayout = nullptr;
	m_pVertexBuffer = nullptr;
	m_pIndexBuffer = nullptr;

	m_pFxWorldViewProj = nullptr;
}

void HrRenderD3D11DemoPipleline::SetD3DDevice(ID3D11Device* pDevice
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

bool HrRenderD3D11DemoPipleline::Init()
{
	m_pShareCamera = std::make_shared<HrCamera>();

	return LoadContent();
}

bool HrRenderD3D11DemoPipleline::LoadContent()
{
	ID3DBlob* pShaderBuffer(nullptr);
	bool bCompile = CompileD3DShader(L"HrShader\\BasicDraw.fx", nullptr, "fx_5_0", &pShaderBuffer);
	//从编译好的effect中创建effect
	HRESULT rt = D3DX11CreateEffectFromMemory(pShaderBuffer->GetBufferPointer(), pShaderBuffer->GetBufferSize(), 0, m_pD3D11Device, &m_pEffect);
	if (FAILED(rt))
	{
		HRERROR(_T("CreateEffectFromMemory Error!"));
		return false;
	}
	SAFE_RELEASE(pShaderBuffer);

	//开始创建输入布局
	D3D11_INPUT_ELEMENT_DESC inputDesc[2] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	D3DX11_PASS_DESC passDesc = { 0 };
	m_pEffect->GetTechniqueByName("BasicDraw")->GetPassByIndex(0)->GetDesc(&passDesc);
	rt = m_pD3D11Device->CreateInputLayout(inputDesc, 2, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_pInputLayout);
	if (FAILED(rt))
	{
		HRERROR(_T("CreateInputLayout Error"));
		return false;
	}

	//创建顶点缓存
	D3D11_BUFFER_DESC vbDesc = { 0 };
	vbDesc.ByteWidth = 8 * sizeof(Vertex);
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;
	//然后给出数据：立方体的8个顶点
	Vertex vertices[8] =
	{
		{ XMFLOAT3(-1.f, -1.f, -1.f), Blue },
		{ XMFLOAT3(-1.f, 1.f, -1.f), Cyan },
		{ XMFLOAT3(1.f, 1.f, -1.f), Red },
		{ XMFLOAT3(1.f, -1.f, -1.f), Yellow },
		{ XMFLOAT3(-1.f, -1.f, 1.f), Green },
		{ XMFLOAT3(-1.f, 1.f, 1.f), Silver },
		{ XMFLOAT3(1.f, 1.f, 1.f), Black },
		{ XMFLOAT3(1.f, -1.f, 1.f), Magenta }
	};
	D3D11_SUBRESOURCE_DATA vbData = { 0 };
	vbData.pSysMem = vertices;
	rt = m_pD3D11Device->CreateBuffer(&vbDesc, &vbData, &m_pVertexBuffer);
	if (FAILED(rt))
	{
		HRERROR(_T("CreateVertexBuffer Error!"));
		return false;
	}

	//创建索引缓存
	D3D11_BUFFER_DESC ibDesc = { 0 };
	ibDesc.ByteWidth = 36 * sizeof(UINT);
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.Usage = D3D11_USAGE_IMMUTABLE;
	UINT indices[36] =
	{
		0, 1, 2, 0, 2, 3,
		4, 5, 1, 4, 1, 0,
		7, 6, 5, 7, 5, 4,
		3, 2, 6, 3, 6, 7,
		1, 5, 6, 1, 6, 2,
		4, 0, 3, 4, 3, 7
	};
	D3D11_SUBRESOURCE_DATA ibData = { 0 };
	ibData.pSysMem = indices;
	rt = m_pD3D11Device->CreateBuffer(&ibDesc, &ibData, &m_pIndexBuffer);
	if (FAILED(rt))
	{

		HRERROR(_T("CreateIndexBuffer Error!"));
		return false;
	}

	//连接Shader变量与C++
	m_pFxWorldViewProj = m_pEffect->GetVariableByName("g_worldViewProj")->AsMatrix();

	return true;
}

bool HrRenderD3D11DemoPipleline::Render()
{
	//
	static float phy(0.0f), theta(0.0f);
	XMMATRIX rotation1 = XMMatrixRotationY(phy);
	XMMATRIX rotation2 = XMMatrixRotationX(theta);
	phy += XM_PI * 0.5f * 0.001f;
	theta += XM_PI * 0.5f * 0.001f;

	XMMATRIX world = XMMatrixIdentity();
	world = rotation1 * rotation2;

	//视变换 把摄像机变换到世界坐标系原点 所有物体都随摄像机变换 
	XMVECTOR eyePos = XMVectorSet(0.0f, 2.0f, -5.0f, 1.0f);
	XMVECTOR lookAt = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	XMMATRIX view = XMMatrixLookAtLH(eyePos, lookAt, up);

	//投影变换
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PI * 0.25f, 600.0f / 480.0f, 1.0f, 1000.0f);
	m_pShareCamera->ProjectParams(Hr::PI * 0.25f, 600.0f / 480.0f, 1.0f, 1000.0f);
	Matrix4 projMatrix = m_pShareCamera->GetProjectMatrix();

	XMMATRIX worldViewProj = world * view * proj;

	//更新Shader相应的变量
	m_pFxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	XMVECTORF32 Blue = { 0.0f, 0.0f, 0.25f, 1.0f };
	m_pD3D11ImmediateContext->ClearRenderTargetView(m_pRenderTargetView, reinterpret_cast<const float*>(&Blue));
	m_pD3D11ImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	 //指定输入布局
	m_pD3D11ImmediateContext->IASetInputLayout(m_pInputLayout);

	uint32 nStride = sizeof(Vertex);
	uint32 nOffset = 0;
	m_pD3D11ImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &nStride, &nOffset);
	//指定索引缓存
	m_pD3D11ImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//指定图元拓扑类型
	m_pD3D11ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//从Technique获取全部pass并逐个渲染
	ID3DX11EffectTechnique* pTech = m_pEffect->GetTechniqueByName("BasicDraw");
	D3DX11_TECHNIQUE_DESC techDesc = { 0 };
	pTech->GetDesc(&techDesc);
	for (UINT i = 0; i < techDesc.Passes; ++i)
	{
		pTech->GetPassByIndex(i)->Apply(0, m_pD3D11ImmediateContext);
		m_pD3D11ImmediateContext->DrawIndexed(36, 0, 0);
	}

	m_pSwapChain->Present(0, 0);

	return true;
}

void HrRenderD3D11DemoPipleline::Release()
{
	SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

