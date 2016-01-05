#include "HrRenderD3D11DemoSprite.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"
#include "DirectXTK/Inc/WICTextureLoader.h"
#include "DirectXTK/Inc/SpriteBatch.h"

using namespace Hr;
using namespace DirectX;

HrRenderD3D11DemoSprite::HrRenderD3D11DemoSprite()
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

	m_pColorMap = nullptr;
	m_pColorMapSampler = nullptr;
	m_pTexture = nullptr;

	m_pAlphaBlendState = nullptr;

	m_pConstBuffer = nullptr;

	m_pSprite1 = nullptr;
}

void HrRenderD3D11DemoSprite::SetD3DDevice(ID3D11Device* pDevice
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

bool HrRenderD3D11DemoSprite::Init()
{
	return LoadContent();
}

bool HrRenderD3D11DemoSprite::LoadContent()
{
	HRESULT rt = CreateDDSTextureFromFile(m_pD3D11Device, L"HrAssets\\windowslogo.dds", &m_pTexture, &m_pColorMap);
	if (FAILED(rt))
	{
		HRERROR(_T("ERROR to create texture from file"));
		return false;
	}
	m_pSprite1 = new SpriteBatch(m_pD3D11ImmediateContext);

	return true;
}

bool HrRenderD3D11DemoSprite::Render()
{
	XMVECTORF32 Blue = { 0.0f, 0.0f, 0.25f, 1.0f };
	m_pD3D11ImmediateContext->ClearRenderTargetView(m_pRenderTargetView, reinterpret_cast<const float*>(&Blue));
	m_pD3D11ImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_pSprite1->Begin(SpriteSortMode_Deferred);
	m_pSprite1->Draw(m_pColorMap, XMFLOAT2(10, 75), nullptr, Colors::White);
	m_pSprite1->End();

	m_pSwapChain->Present(0, 0);

	return true;
}

void HrRenderD3D11DemoSprite::Release()
{
	SAFE_RELEASE(m_pSolidColorVS);
	SAFE_RELEASE(m_pSolidColorPS);
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pVertexBuffer);

	SAFE_RELEASE(m_pColorMap);
	SAFE_RELEASE(m_pColorMapSampler);
	SAFE_RELEASE(m_pTexture);
	
	SAFE_DELETE(m_pSprite1);
}

