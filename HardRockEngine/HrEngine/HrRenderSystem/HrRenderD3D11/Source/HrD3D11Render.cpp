#include "HrD3D11Render.h"
#include <boost/cast.hpp>
#include "HrUtilTools/Include/HrUtil.h"
#include "HrD3D11RenderWindow.h"
#include "HrD3D11RenderLayout.h"
#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrRenderDemo/Include/HrRenderDemo.h"


using namespace Hr;

HrD3D11Render::HrD3D11Render()
{
	m_pD3D11ImmediateContext = nullptr;

	typedef HrRenderD3D11DemoPipleline DEMOCLASS;

	m_pRenderDemo = HR_NEW DEMOCLASS();

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


	m_pRenderDemo->SetD3DDevice(HrD3D11Device::GetInstance().GetDevice()
		, HrD3D11Device::GetInstance().GetImmediateContext()
		, m_pShareRenderWindow->GetRenderTargetView()
		, m_pShareRenderWindow->GetDepthStencilView()
		, m_pShareRenderWindow->GetSwapChain());
	if (!m_pRenderDemo->Init())
	{
		return false;
	}

	return true;
}

void HrD3D11Render::Release()
{
	HrD3D11Device::GetInstance().Release();
	m_pRenderDemo->Release();
}

bool HrD3D11Render::StartRender()
{
	m_pRenderDemo->Render();
	

	return true;
}

void HrD3D11Render::Render(HrRenderTechnique* pRenderTechnique, IRenderLayout* pRenderLayout)
{
	//1.IASetVertexBuffers
	//2.Draw & DrawIndexed
	
	HrD3D11RenderLayout* pD3D11RenderLayout = boost::polymorphic_downcast<HrD3D11RenderLayout*>(pRenderLayout);
	ID3D11InputLayout* pInputLayout = pD3D11RenderLayout->GetInputLayout();
	m_pD3D11ImmediateContext->IASetInputLayout(pInputLayout);
	ID3D11Buffer* pVertexBuffer = pD3D11RenderLayout->GetVertexBuffer();
	unsigned int nStride = 0;//sizeof(VertexPos);
	unsigned int nOffset = 0;
	m_pD3D11ImmediateContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &nStride, &nOffset);
	m_pD3D11ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pRenderTechnique->GetRenderPass()->BindPass(this);
	m_pD3D11ImmediateContext->Draw(3, 0);
	pRenderTechnique->GetRenderPass()->UnBindPass(this);

	m_pShareRenderWindow->GetSwapChain()->Present(0, 0);
}

