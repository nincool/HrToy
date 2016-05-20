﻿#include "HrD3D11Render.h"
#include "HrD3D11Shader.h"
#include "HrD3D11RenderWindow.h"
#include "HrD3D11RenderLayout.h"
#include "HrD3D11Mapping.h"
#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrViewPort.h"
#include "HrRenderDemo/Include/HrRenderDemo.h"
#include "HrUtilTools/Include/HrUtil.h"
#include <boost/cast.hpp>

using namespace Hr;

HrD3D11Render::HrD3D11Render()
{
	m_pD3D11ImmediateContext = nullptr;

	//typedef HrRenderD3D11DemoPipleline DEMOCLASS;

	m_pRenderDemo = nullptr;
	//m_pRenderDemo = HR_NEW DEMOCLASS();
}

HrD3D11Render::~HrD3D11Render()
{
}

bool HrD3D11Render::Init()
{
	HrD3D11Device::GetInstance().CreateD3D11Device();
	
	m_pD3D11Device = HrD3D11Device::GetInstance().GetDevice();
	m_pD3D11ImmediateContext = HrD3D11Device::GetInstance().GetImmediateContext();

	return true;
}

void HrD3D11Render::SetRenderTarget(IRenderTargetPtr& renderTarget)
{
	m_pShareRenderWindow = std::dynamic_pointer_cast<HrD3D11RenderWindow>(renderTarget);
}

void HrD3D11Render::SetCurrentViewPort(HrViewPort* pViewPort)
{
	D3D11_VIEWPORT vp;
	// Setup the viewport to match the backbuffer
	ZeroMemory(&vp, sizeof(vp));
	vp.TopLeftX = pViewPort->GetLeft();
	vp.TopLeftY = pViewPort->GetTop();
	vp.Width = static_cast<FLOAT>(pViewPort->GetWidth());
	vp.Height = static_cast<FLOAT>(pViewPort->GetHeight());
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	HrD3D11Device::GetInstance().GetImmediateContext()->RSSetViewports(1, &vp);
}

void HrD3D11Render::ClearRenderTargetView()
{
	XMVECTORF32 Blue = { 0.69f, 0.77f, 0.87f, 1.0f };
	m_pD3D11ImmediateContext->ClearRenderTargetView(m_pShareRenderWindow->GetRenderTargetView(), reinterpret_cast<const float*>(&Blue));
}

void HrD3D11Render::ClearDepthStencilView()
{
	m_pD3D11ImmediateContext->ClearDepthStencilView(m_pShareRenderWindow->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void HrD3D11Render::Release()
{
	HrD3D11Device::GetInstance().Release();
	if (m_pRenderDemo)
		m_pRenderDemo->Release();
}

bool HrD3D11Render::StartRender()
{
	return true;
}

void HrD3D11Render::Render(IRenderTechnique* pRenderTechnique, IRenderLayout* pRenderLayout)
{
	//1.IASetVertexBuffers
	//2.Draw & DrawIndexed
	HrD3D11RenderLayout* pD3D11RenderLayout = boost::polymorphic_downcast<HrD3D11RenderLayout*>(pRenderLayout);
	unsigned int stride = pD3D11RenderLayout->GetVertexSize();
	unsigned int offset = 0;

	IShader* pShader = pRenderTechnique->GetRenderPass(0)->GetVertexShader();
	ID3D11InputLayout* pInputLayout = pD3D11RenderLayout->GetInputLayout(static_cast<HrD3D11Shader*>(pShader));
	m_pD3D11ImmediateContext->IASetInputLayout(pInputLayout);
	
	ID3D11Buffer* pVertexBuffer = pD3D11RenderLayout->GetVertexBuffer();
	m_pD3D11ImmediateContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	m_pD3D11ImmediateContext->IASetPrimitiveTopology(HrD3D11Mapping::GetTopologyType(pD3D11RenderLayout->GetTopologyType()));

	if (pD3D11RenderLayout->UseIndices())
	{
		ID3D11Buffer* pIndexBuffer = pD3D11RenderLayout->GetIndexBuffer();
		m_pD3D11ImmediateContext->IASetIndexBuffer(pIndexBuffer, HrD3D11Mapping::GetIndexBufferFormat(pD3D11RenderLayout->GetIndexBufferType()), 0);
	}

	if (pD3D11RenderLayout->UseIndices())
	{
		uint32 nNumIndices = pD3D11RenderLayout->GetIndicesNum();
		
		pRenderTechnique->GetRenderPass(0)->BindPass(this);
		m_pD3D11ImmediateContext->DrawIndexed(nNumIndices, 0, 0);
		pRenderTechnique->GetRenderPass(0)->UnBindPass(this);
	}
	else
	{
		pRenderTechnique->GetRenderPass(0)->BindPass(this);
		m_pD3D11ImmediateContext->Draw(3, 0);
		pRenderTechnique->GetRenderPass(0)->UnBindPass(this);
	}
}

void HrD3D11Render::SwapChain()
{
	m_pShareRenderWindow->GetSwapChain()->Present(0, 0);
}

