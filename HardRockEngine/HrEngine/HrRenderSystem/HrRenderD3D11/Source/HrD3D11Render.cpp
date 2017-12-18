#include "HrD3D11Render.h"
#include "HrD3D11Shader.h"
#include "HrD3D11RenderWindow.h"
#include "HrD3D11RenderLayout.h"
#include "HrD3D11Mapping.h"
#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrViewPort.h"
#include "HrUtilTools/Include/HrUtil.h"
#include <boost/cast.hpp>

using namespace Hr;

HrD3D11Render::HrD3D11Render()
{
}

HrD3D11Render::~HrD3D11Render()
{
}

bool HrD3D11Render::Init()
{
	HrD3D11Device::Instance()->CreateD3D11Device();

	return true;
}

void HrD3D11Render::SetRenderTarget(HrRenderTargetPtr& renderTarget)
{
	m_pRenderWindow = std::dynamic_pointer_cast<HrD3D11RenderWindow>(renderTarget);
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

	GetD3D11DeviceContext()->RSSetViewports(1, &vp);
}

void HrD3D11Render::ClearRenderTargetView()
{
	XMVECTORF32 Blue = { 0.69f, 0.77f, 0.87f, 1.0f };
	GetD3D11DeviceContext()->ClearRenderTargetView(m_pRenderWindow->GetRenderTargetView(), reinterpret_cast<const float*>(&Blue));
}

void HrD3D11Render::ClearDepthStencilView()
{
	GetD3D11DeviceContext()->ClearDepthStencilView(m_pRenderWindow->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void HrD3D11Render::ReleaseRenderEngine()
{
	HrD3D11Device::Instance()->Release();
}

bool HrD3D11Render::StartRender()
{
	return true;
}

void HrD3D11Render::Render(HrRenderTechnique* pRenderTechnique, HrRenderLayout* pRenderLayout)
{
	//1.IASetVertexBuffers
	//2.Draw & DrawIndexed
	HrD3D11RenderLayout* pD3D11RenderLayout = boost::polymorphic_downcast<HrD3D11RenderLayout*>(pRenderLayout);
	unsigned int stride = pD3D11RenderLayout->GetVertexSize();
	unsigned int offset = 0;

	HrShader* pVertexShader = pRenderTechnique->GetRenderPass(0)->GetShader(HrShader::ST_VERTEX_SHADER);
	ID3D11InputLayout* pInputLayout = pD3D11RenderLayout->GetInputLayout(static_cast<HrD3D11Shader*>(pVertexShader));
	GetD3D11DeviceContext()->IASetInputLayout(pInputLayout);
	
	ID3D11Buffer* pVertexBuffer = pD3D11RenderLayout->GetVertexBuffer();
	GetD3D11DeviceContext()->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	GetD3D11DeviceContext()->IASetPrimitiveTopology(HrD3D11Mapping::GetTopologyType(pD3D11RenderLayout->GetTopologyType()));

	if (pD3D11RenderLayout->UseIndices())
	{
		ID3D11Buffer* pIndexBuffer = pD3D11RenderLayout->GetIndexBuffer();
		GetD3D11DeviceContext()->IASetIndexBuffer(pIndexBuffer, HrD3D11Mapping::GetIndexBufferFormat(pD3D11RenderLayout->GetIndexBufferType()), 0);
	}

	const uint32 nPassNum = pRenderTechnique->GetRenderPassNum();
	if (pD3D11RenderLayout->UseIndices())
	{
		uint32 nNumIndices = pD3D11RenderLayout->GetIndicesNum();
		for (uint32 i = 0; i < nPassNum; ++i)
		{
			pRenderTechnique->GetRenderPass(i)->BindPass(this);
			GetD3D11DeviceContext()->DrawIndexed(nNumIndices, 0, 0);
			pRenderTechnique->GetRenderPass(i)->UnBindPass(this);
		}
	}
	else
	{
		uint32 nNumVertices = pD3D11RenderLayout->GetVerticesNum();
		for (uint32 i = 0; i < nPassNum; ++i)
		{
			pRenderTechnique->GetRenderPass(i)->BindPass(this);
			GetD3D11DeviceContext()->Draw(nNumVertices, 0);
			pRenderTechnique->GetRenderPass(i)->UnBindPass(this);
		}
	}
}

void HrD3D11Render::SwapChain()
{
	m_pRenderWindow->PresentSwapChain();
}

const ID3D11DevicePtr& HrD3D11Render::GetD3D11Device()
{
	return HrD3D11Device::Instance()->GetD3DDevice();
}

const ID3D11DeviceContextPtr& HrD3D11Render::GetD3D11DeviceContext()
{
	return HrD3D11Device::Instance()->GetD3DDeviceContext();
}

