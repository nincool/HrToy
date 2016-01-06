#include "HrRenderD3D11DemoLight.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"
#include "DirectXTK/Inc/WICTextureLoader.h"
#include "DirectXTK/Inc/SpriteBatch.h"
#include "DirectXFX11/inc/d3dx11effect.h"
#include <fstream>

using namespace Hr;
using namespace std;
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

HrRenderD3D11DemoLight::HrRenderD3D11DemoLight()
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

}

void HrRenderD3D11DemoLight::SetD3DDevice(ID3D11Device* pDevice
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

bool HrRenderD3D11DemoLight::Init()
{
	return LoadContent();
}

bool HrRenderD3D11DemoLight::LoadContent()
{

	return true;
}

void HrRenderD3D11DemoLight::CalculatePerspectiveMatrix()
{

}

bool HrRenderD3D11DemoLight::Render()
{
	m_pD3D11ImmediateContext->ClearRenderTargetView(m_pRenderTargetView, reinterpret_cast<const float*>(&Colors::Silver));
	m_pD3D11ImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_pSwapChain->Present(0, 0);

	return true;
}

void HrRenderD3D11DemoLight::Release()
{
	SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

bool HrRenderD3D11DemoLight::BuildHLSL()
{


	return true;
}

bool HrRenderD3D11DemoLight::BuildInputLayout()
{


	return true;
}

bool HrRenderD3D11DemoLight::BuildBuffers()
{


	return true;
}

