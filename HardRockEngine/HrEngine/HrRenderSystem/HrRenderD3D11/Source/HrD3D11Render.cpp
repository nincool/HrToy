#include "HrD3D11Render.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrD3D11RenderWindow.h"

using namespace Hr;

HrD3D11Render::HrD3D11Render()
{
	//typedef HrRenderD3D11DemoTriangle DEMOCLASS;

	//m_pRenderDemo = HR_NEW DEMOCLASS();

}

HrD3D11Render::~HrD3D11Render()
{
	//HrD3D11Device::ReleaseInstance();
	//HrD3D11Utility::ReleaseInstance();

}

bool HrD3D11Render::Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc)
{
	m_pShareRenderWindow = MakeSharedPtr<HrD3D11RenderWindow>();
	m_pShareRenderWindow->CreateRenderWindow(nWidth, nHeight, lpfnProc);
	//HrD3D11Utility::GetInstance()->Init(nWidth, nHeight, lpfnProc);

	//m_pRenderDemo->SetD3DDevice(HrD3D11Device::GetInstance()->GetDevice()
	//	, HrD3D11Device::GetInstance()->GetImmediateContext()
	//	, HrD3D11Device::GetInstance()->GetRenderTargetView()
	//	, HrD3D11Device::GetInstance()->GetDepthStencilView()
	//	, HrD3D11Device::GetInstance()->GetSwapChain());
	//if (!m_pRenderDemo->Init())
	//{
	//	return false;
	//}

	return true;
}

void HrD3D11Render::CreateRenderWindow(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc)
{

}

void HrD3D11Render::Release()
{
	//m_pRenderDemo->Release();
}

bool HrD3D11Render::StartRender()
{
	//m_pRenderDemo->Render();

	return true;
}

//void HrD3D11Render::Render(const HrRenderTechnique* pRenderTechnique, const HrRenderLayout* pRenderLayout)
//{
//	//1.IASetVertexBuffers
//	//2.Draw & DrawIndexed
//
//	unsigned int stride = 0;//sizeof(VertexPos);
//	unsigned int offset = 0;
//
//	//ID3D11Buffer* pVertexBuffer;
//	//GetImmediateContext()->IASetInputLayout();
//	//GetImmediateContext()->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
//	//GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//	//
//	//GetImmediateContext()->VSSetShader()
//}

//m_pD3D11ImmediateContext->IASetInputLayout(m_pInputLayout);
//m_pD3D11ImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
//m_pD3D11ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//m_pD3D11ImmediateContext->VSSetShader(m_pSolidColorVS, 0, 0);
//m_pD3D11ImmediateContext->PSSetShader(m_pSolidColorPS, 0, 0);
//m_pD3D11ImmediateContext->Draw(3, 0);