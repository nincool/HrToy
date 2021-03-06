#include "HrD3D11FrameBuffer.h"
#include "HrD3D11RenderTarget.h"
#include "HrD3D11DepthStencil.h"
#include "HrD3D11Render.h"
#include "HrD3D11Texture.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrCore/Include/Kernel/HrRenderModule.h"
#include "HrCore/Include/Kernel/HrWindowModule.h"
#include "HrCore/Include/Render/HrRenderSystem.h"
#include "HrCore/Include/Render/HrShadowMap.h"
#include <DirectXMath.h>

using namespace Hr;
using namespace DirectX;

HrD3D11FrameBuffer::HrD3D11FrameBuffer(uint32 nWidth, uint32 nHeight) : HrRenderFrame(nWidth, nHeight)
{}

HrD3D11FrameBuffer::~HrD3D11FrameBuffer()
{}

void HrD3D11FrameBuffer::AttachRenderTarget(EnumRenderTargetLayer attachLayer, HrRenderTargetPtr& pRenderTarget)
{
	HrRenderFrame::AttachRenderTarget(attachLayer, pRenderTarget);
}

void HrD3D11FrameBuffer::DetachRenderTarget(EnumRenderTargetLayer attachLayer)
{
	HrRenderFrame::DetachRenderTarget(attachLayer);
}

void HrD3D11FrameBuffer::OnBind(const HrRenderPtr& pRender)
{
	if (!m_pDepthStencil)
	{
		m_pDepthStencil = HrMakeSharedPtr<HrD3D11DepthStencil>(m_nWidth, m_nHeight, PF_D24S8, HrD3D11Texture::TUF_TEX_DEPTHSTENCILVIEW);
	}

	pRender->SetRenderTarget(m_arrRenderTargets, m_pDepthStencil);
}

void HrD3D11FrameBuffer::OnUnBind()
{
}

const ID3D11RenderTargetViewPtr& HrD3D11FrameBuffer::D3D11RenderTargetView(EnumRenderTargetLayer renderTargetLayer)
{
	if (m_arrRenderTargets[renderTargetLayer])
	{
		HrD3D11RenderTargetPtr pD3DRenderTarget = HrCheckPointerCast<HrD3D11RenderTarget>(m_arrRenderTargets[renderTargetLayer]);
		return pD3DRenderTarget->GetRenderTargetView();
	}

	return nullptr;
}

const ID3D11DepthStencilViewPtr& HrD3D11FrameBuffer::D3D11DepthStencilView()
{
	HrD3D11DepthStencilPtr pD3DDepthStencil = HrCheckPointerCast<HrD3D11DepthStencil>(m_pDepthStencil);
	return pD3DDepthStencil->GetDepthStencilView();
}

void HrD3D11FrameBuffer::ClearTarget()
{
	XMVECTORF32 Blue = { m_clearColor.r(), m_clearColor.g(), m_clearColor.b(), m_clearColor.a() };
	HrD3D11Device::Instance()->GetD3DDeviceContext()->ClearRenderTargetView(D3D11RenderTargetView(RTL_0).get(), reinterpret_cast<const float*>(&Blue));
}

void HrD3D11FrameBuffer::ClearDepthStencil()
{
	HrD3D11Device::Instance()->GetD3DDeviceContext()->ClearDepthStencilView(D3D11DepthStencilView().get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, m_clearDepth, m_clearStencil);
}

void HrD3D11FrameBuffer::Present()
{	
}










///////////////////////////////////////////////////////////////////////////
//HrD3D11ScreenFrameBuffer
///////////////////////////////////////////////////////////////////////////
HrD3D11ScreenFrameBuffer::HrD3D11ScreenFrameBuffer(uint32 nWidth, uint32 nHeight) : HrD3D11FrameBuffer(nWidth, nHeight)
{
	CreateSwapChain();
	CreateRenderTargetView();
	CreateDepthStencilView();
}

HrD3D11ScreenFrameBuffer::~HrD3D11ScreenFrameBuffer()
{
}

bool HrD3D11ScreenFrameBuffer::CreateSwapChain()
{
	if (HrD3D11Device::Instance()->GetDXGISubVersion() >= 2)
	{
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc1;
		ZeroMemory(&swapChainDesc1, sizeof(swapChainDesc1));
		swapChainDesc1.Width = m_nWidth;
		swapChainDesc1.Height = m_nHeight;
		swapChainDesc1.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		bool bStereo = HrD3D11Device::Instance()->GetDXGIFactory2()->IsWindowedStereoEnabled();
		swapChainDesc1.Stereo = bStereo;

		swapChainDesc1.SampleDesc.Count = 1;
		swapChainDesc1.SampleDesc.Quality = 0;

		swapChainDesc1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc1.BufferCount = 1;

		swapChainDesc1.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc1.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc1.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swapChainDesc1.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainFullScreenDesc;
		ZeroMemory(&swapChainFullScreenDesc, sizeof(swapChainFullScreenDesc));
		swapChainFullScreenDesc.RefreshRate.Numerator = 0;
		swapChainFullScreenDesc.RefreshRate.Denominator = 0;
		swapChainFullScreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainFullScreenDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainFullScreenDesc.Windowed = true;

		const HrWindowModulePtr& pWindowComponent = HrDirector::Instance()->GetWindowModule();
		IDXGISwapChain1* pSwapChain = nullptr;
		HRESULT hr = HrD3D11Device::Instance()->GetDXGIFactory2()->CreateSwapChainForHwnd(HrD3D11Device::Instance()->GetD3DDevice().get(), pWindowComponent->GetWindowHWnd()
			, &swapChainDesc1
			, &swapChainFullScreenDesc
			, nullptr
			, &pSwapChain);

		if (FAILED(hr))
		{
			TRE("HrD3D11ScreenFrameBuffer::CreateSwapChain Error!");
			return false;
		}
		m_pSwapChain1 = MakeComPtr(pSwapChain);

		return true;
	}
	else
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferDesc.Width = m_nWidth;
		swapChainDesc.BufferDesc.Height = m_nHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;

		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		swapChainDesc.BufferCount = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		const HrWindowModulePtr& pWindowComponent = HrDirector::Instance()->GetWindowModule();
		swapChainDesc.OutputWindow = pWindowComponent->GetWindowHWnd();
		swapChainDesc.Windowed = true;

		//todo
		IDXGISwapChain* pSwapChain = nullptr;
		HRESULT hr = HrD3D11Device::Instance()->GetDXGIFactory1()->CreateSwapChain(HrD3D11Device::Instance()->GetD3DDevice().get(), &swapChainDesc, &pSwapChain);
		if (FAILED(hr))
		{
			TRE("HrD3D11ScreenFrameBuffer::CreateSwapChain Error!");
			return false;
		}
		m_pSwapChain = MakeComPtr(pSwapChain);

		return true;
	}
}

void HrD3D11ScreenFrameBuffer::CreateRenderTargetView()
{
	if (!m_arrRenderTargets[RTL_0])
	{
		ID3D11Texture2D* pBackBuffer = nullptr;
		if (m_pSwapChain)
		{
			m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
		}
		else if (m_pSwapChain1)
		{
			m_pSwapChain1->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
		}
		ID3D11Texture2DPtr p2DBackBuffer = MakeComPtr(pBackBuffer);
		m_arrRenderTargets[RTL_0] = HrMakeSharedPtr<HrD3D11RenderTarget>(p2DBackBuffer);
	}
}

void HrD3D11ScreenFrameBuffer::CreateDepthStencilView()
{
	if (!m_pDepthStencil)
	{
		m_pDepthStencil = HrMakeSharedPtr<HrD3D11DepthStencil>(m_nWidth, m_nHeight, PF_D24S8, HrD3D11Texture::TUF_TEX_DEPTHSTENCILVIEW);
	}
}

void HrD3D11ScreenFrameBuffer::OnBind(const HrRenderPtr& pRender)
{
	if (m_arrRenderTargets[RTL_0])
	{
		pRender->SetRenderTarget(m_arrRenderTargets[RTL_0], m_pDepthStencil);
	}
}

void HrD3D11ScreenFrameBuffer::OnUnBind()
{

}

void HrD3D11ScreenFrameBuffer::ClearTarget()
{
	XMVECTORF32 clearColor = { m_clearColor.r(), m_clearColor.g(), m_clearColor.b(), m_clearColor.a() };
	HrD3D11Device::Instance()->GetD3DDeviceContext()->ClearRenderTargetView(D3D11RenderTargetView(RTL_0).get(), reinterpret_cast<const float*>(&clearColor));
}

void HrD3D11ScreenFrameBuffer::ClearDepthStencil()
{
	HrD3D11Device::Instance()->GetD3DDeviceContext()->ClearDepthStencilView(D3D11DepthStencilView().get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, m_clearDepth, m_clearStencil);
}

void HrD3D11ScreenFrameBuffer::Present()
{
	if (m_pSwapChain1)
	{
		m_pSwapChain1->Present(0, 0);
	}
	else if (m_pSwapChain)
	{
		m_pSwapChain->Present(0, 0);
	}
}

///////////////////////////////////////////////////////////////////////////
//HrD3D11DepthStencilFrameBuffer
///////////////////////////////////////////////////////////////////////////
HrD3D11DepthStencilFrameBuffer::HrD3D11DepthStencilFrameBuffer(uint32 nWidth, uint32 nHeight) : HrD3D11FrameBuffer(nWidth, nHeight)
{
	//1.创建DepthTexture
	//2.创建DepthStencil
	//3.创建关联DepthStencil的ShaderResourceView
	//4.忽略RenderTarget
	CreateDepthStencilView();
}

HrD3D11DepthStencilFrameBuffer::~HrD3D11DepthStencilFrameBuffer()
{

}

void HrD3D11DepthStencilFrameBuffer::CreateDepthStencilView()
{
	if (!m_pDepthStencil)
	{
		m_pDepthStencil = HrMakeSharedPtr<HrD3D11DepthStencil>(m_nWidth, m_nHeight, PF_D24S8, HrD3D11Texture::TUF_TEX_DEPTHSTENCILVIEW | HrD3D11Texture::TUF_TEX_SHADERRESOURCEVIEW);
		HrCheckPointerCast<HrD3D11DepthStencil>(m_pDepthStencil)->GetDepthStencilShaderResouceView();
	}
}

void HrD3D11DepthStencilFrameBuffer::ClearTarget()
{
}

void HrD3D11DepthStencilFrameBuffer::ClearDepthStencil()
{
	HrD3D11Device::Instance()->GetD3DDeviceContext()->ClearDepthStencilView(D3D11DepthStencilView().get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, m_clearDepth, m_clearStencil);
}

void HrD3D11DepthStencilFrameBuffer::OnBind(const HrRenderPtr& pRender)
{
	pRender->SetRenderTarget(nullptr, m_pDepthStencil);
}

void HrD3D11DepthStencilFrameBuffer::OnUnBind()
{

}

///////////////////////////////////////////////////////////////////////////
//HrD3D11DepthStencilFrameBuffer
///////////////////////////////////////////////////////////////////////////
HrD3D11DeferredFrameBuffer::HrD3D11DeferredFrameBuffer(uint32 nWidth, uint32 nHeight, const HrDeferredGBufferDataPtr& pDeferredGBufferData) : HrD3D11FrameBuffer(nWidth, nHeight)
{
	m_pGBufferData = pDeferredGBufferData;

	CreateGBuffers();
	CreateDepthStencilView();

	m_clearColor = HrColor(0.0f, 0.0f, 0.0f, 1.0f);
}

HrD3D11DeferredFrameBuffer::~HrD3D11DeferredFrameBuffer()
{
}

void HrD3D11DeferredFrameBuffer::OnBind(const HrRenderPtr& pRender)
{
	pRender->SetRenderTarget(m_arrRenderTargets, m_pDepthStencil);
}

void HrD3D11DeferredFrameBuffer::OnUnBind()
{

}

void HrD3D11DeferredFrameBuffer::ClearTarget()
{
	XMVECTORF32 clearColor = { m_clearColor.r(), m_clearColor.g(), m_clearColor.b(), m_clearColor.a() };
	HrD3D11Device::Instance()->GetD3DDeviceContext()->ClearRenderTargetView(D3D11RenderTargetView(RTL_0).get(), reinterpret_cast<const float*>(&clearColor));
	for (int i = 0; i < RTL_MAX; ++i)
	{
		if (m_arrRenderTargets[i])
			HrD3D11Device::Instance()->GetD3DDeviceContext()->ClearRenderTargetView(D3D11RenderTargetView((EnumRenderTargetLayer)i).get(), reinterpret_cast<const float*>(&clearColor));
	}
}

void HrD3D11DeferredFrameBuffer::ClearDepthStencil()
{
	HrD3D11Device::Instance()->GetD3DDeviceContext()->ClearDepthStencilView(D3D11DepthStencilView().get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, m_clearDepth, m_clearStencil);
}


void HrD3D11DeferredFrameBuffer::CreateGBuffers()
{
	//m_pPositionSRV = HrMakeSharedPtr<HrD3D11Texture2D>(m_nWidth
	//	, m_nHeight
	//	, 1, 1, 0
	//	, HrTexture::EAH_GPU_READ | HrTexture::EAH_GPU_WRITE
	//	, EnumPixelFormat::PF_R32G32B32A32_FLOAT
	//	, HrD3D11Texture::TUF_TEX_RENDERTARGETVIEW | HrD3D11Texture::TUF_TEX_SHADERRESOURCEVIEW);
	//m_pPositionSRV->CreateRenderTargetView();
	//m_arrRenderTargets[RTL_0] = HrMakeSharedPtr<HrD3D11RenderTarget>(m_pPositionSRV->GetD3D11Texture());
	//m_pPositionSRV->CreateShaderResourceView();

	//m_pNormalSRV = HrMakeSharedPtr<HrD3D11Texture2D>(m_nWidth
	//	, m_nHeight
	//	, 1, 1, 0
	//	, HrTexture::EAH_GPU_READ | HrTexture::EAH_GPU_WRITE
	//	, EnumPixelFormat::PF_R32G32B32A32_FLOAT
	//	, HrD3D11Texture::TUF_TEX_RENDERTARGETVIEW | HrD3D11Texture::TUF_TEX_SHADERRESOURCEVIEW);
	//m_pNormalSRV->CreateRenderTargetView();
	//m_arrRenderTargets[RTL_1] = HrMakeSharedPtr<HrD3D11RenderTarget>(m_pNormalSRV->GetD3D11Texture()); //m_pPositionSRV->GetD3DRenderTargetView();
	//m_pNormalSRV->CreateShaderResourceView();

	//m_pAlbedoSRV = HrMakeSharedPtr<HrD3D11Texture2D>(m_nWidth
	//	, m_nHeight
	//	, 1, 1, 0
	//	, HrTexture::EAH_GPU_READ | HrTexture::EAH_GPU_WRITE
	//	, EnumPixelFormat::PF_R32G32B32A32_FLOAT
	//	, HrD3D11Texture::TUF_TEX_RENDERTARGETVIEW | HrD3D11Texture::TUF_TEX_SHADERRESOURCEVIEW);
	//m_pAlbedoSRV->CreateRenderTargetView();
	//m_arrRenderTargets[RTL_2] = HrMakeSharedPtr<HrD3D11RenderTarget>(m_pAlbedoSRV->GetD3D11Texture()); //m_pAlbedoSRV->GetD3DRenderTargetView();
	//m_pAlbedoSRV->CreateShaderResourceView();

	//m_pGBufferData->m_pGBufferPosition = m_pPositionSRV;
	//m_pGBufferData->m_pGBufferNormal = m_pNormalSRV;
	//m_pGBufferData->m_pGBufferAlbedo = m_pAlbedoSRV;
}

void HrD3D11DeferredFrameBuffer::CreateDepthStencilView()
{
	if (!m_pDepthStencil)
	{
		m_pDepthStencil = HrMakeSharedPtr<HrD3D11DepthStencil>(m_nWidth, m_nHeight, PF_D24S8, HrD3D11Texture::TUF_TEX_DEPTHSTENCILVIEW);
	}
}

