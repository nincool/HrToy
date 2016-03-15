#include "HrD3D11Render.h"
#include "HrD3D11Shader.h"
#include "HrD3D11RenderWindow.h"
#include "HrD3D11RenderLayout.h"
#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrRenderDemo/Include/HrRenderDemo.h"
#include "HrUtilTools/Include/HrUtil.h"
#include <boost/cast.hpp>

using namespace Hr;

HrD3D11Render::HrD3D11Render()
{
	m_pD3D11ImmediateContext = nullptr;

	typedef HrRenderD3D11DemoPipleline DEMOCLASS;

	m_pRenderDemo = nullptr;
	//m_pRenderDemo = HR_NEW DEMOCLASS();

}

HrD3D11Render::~HrD3D11Render()
{
}

bool HrD3D11Render::Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc)
{
	HrD3D11Device::GetInstance().CreateD3D11Device();
	
	m_pD3D11ImmediateContext = HrD3D11Device::GetInstance().GetImmediateContext();

	m_pShareRenderWindow = MakeSharedPtr<HrD3D11RenderWindow>();
	m_pShareRenderWindow->CreateRenderWindow(nWidth, nHeight, lpfnProc);

	if (m_pRenderDemo)
	{
		m_pRenderDemo->SetD3DDevice(HrD3D11Device::GetInstance().GetDevice()
			, HrD3D11Device::GetInstance().GetImmediateContext()
			, m_pShareRenderWindow->GetRenderTargetView()
			, m_pShareRenderWindow->GetDepthStencilView()
			, m_pShareRenderWindow->GetSwapChain());
		if (!m_pRenderDemo->Init())
		{
			return false;
		}
	}


	return true;
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
	if (m_pRenderDemo)
	{
		m_pRenderDemo->Render();
		return;
	}
	//1.IASetVertexBuffers
	//2.Draw & DrawIndexed
	XMVECTORF32 Blue = { 0.69f, 0.77f, 0.87f, 1.0f };
	m_pD3D11ImmediateContext->ClearRenderTargetView(m_pShareRenderWindow->GetRenderTargetView(), reinterpret_cast<const float*>(&Blue));
	m_pD3D11ImmediateContext->ClearDepthStencilView(m_pShareRenderWindow->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	HrD3D11RenderLayout* pD3D11RenderLayout = boost::polymorphic_downcast<HrD3D11RenderLayout*>(pRenderLayout);
	unsigned int stride = pD3D11RenderLayout->GetVertexSize();
	unsigned int offset = 0;

	IShader* pShader = pRenderTechnique->GetRenderPass(0)->GetVertexShader();
	ID3D11InputLayout* pInputLayout = pD3D11RenderLayout->GetInputLayout(static_cast<HrD3D11Shader*>(pShader));
	m_pD3D11ImmediateContext->IASetInputLayout(pInputLayout);
	
	ID3D11Buffer* pVertexBuffer = pD3D11RenderLayout->GetVertexBuffer();
	m_pD3D11ImmediateContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	m_pD3D11ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (pD3D11RenderLayout->UseIndices())
	{
		ID3D11Buffer* pIndexBuffer = pD3D11RenderLayout->GetIndexBuffer();
		m_pD3D11ImmediateContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	}

	if (pD3D11RenderLayout->UseIndices())
	{
		pRenderTechnique->GetRenderPass(0)->BindPass(this);
		m_pD3D11ImmediateContext->Draw(3, 0);
		pRenderTechnique->GetRenderPass(0)->UnBindPass(this);
	}
	else
	{
		pRenderTechnique->GetRenderPass(0)->BindPass(this);
		m_pD3D11ImmediateContext->DrawIndexed(36, 0, 0);
		pRenderTechnique->GetRenderPass(0)->UnBindPass(this);
	}

	m_pShareRenderWindow->GetSwapChain()->Present(0, 0);
}

