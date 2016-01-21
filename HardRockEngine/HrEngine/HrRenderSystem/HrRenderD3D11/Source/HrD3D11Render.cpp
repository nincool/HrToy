#include "HrD3D11Render.h"
#include "HrD3D11Device.h"
#include "HrD3D11Utility.h"

#include "HrRenderDemo/Include/HrRenderDemo.h"

using namespace Hr;
using namespace DirectX;

HrD3D11Render* HrD3D11Render::m_s_pInstance = nullptr;

HrD3D11Render::HrD3D11Render()
{
	typedef HrRenderD3D11DemoTriangle DEMOCLASS;

	m_pRenderDemo = HR_NEW DEMOCLASS();

	m_pImmediateContext = nullptr;
}

HrD3D11Render::~HrD3D11Render()
{
	SAFE_DELETE(m_pRenderDemo);

	HrD3D11Device::ReleaseInstance();
	HrD3D11Utility::ReleaseInstance();

}

#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
bool HrD3D11Render::Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc)
{
	HrD3D11Utility::GetInstance()->Init(nWidth, nHeight, lpfnProc);

	m_pRenderDemo->SetD3DDevice(HrD3D11Device::GetInstance()->GetDevice()
		, HrD3D11Device::GetInstance()->GetImmediateContext()
		, HrD3D11Device::GetInstance()->GetRenderTargetView()
		, HrD3D11Device::GetInstance()->GetDepthStencilView()
		, HrD3D11Device::GetInstance()->GetSwapChain());
	if (!m_pRenderDemo->Init())
	{
		return false;
	}

	return true;
}
#else
bool HrD3D11Render::Init(unsigned int nWidth, unsigned int nHeight)
{
}
#endif

void HrD3D11Render::Release()
{
	m_pRenderDemo->Release();
}

bool HrD3D11Render::StartRender()
{
	m_pRenderDemo->Render();

	return true;
}

void HrD3D11Render::Render(const HrRenderTechnique* pRenderTechnique, const HrRenderLayout* pRenderLayout)
{
	//1.IASetVertexBuffers
	//2.Draw & DrawIndexed

	unsigned int stride = 0;//sizeof(VertexPos);
	unsigned int offset = 0;

	//ID3D11Buffer* pVertexBuffer;
	//GetImmediateContext()->IASetInputLayout();
	//GetImmediateContext()->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	//GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//
	//GetImmediateContext()->VSSetShader()
}

//m_pD3D11ImmediateContext->IASetInputLayout(m_pInputLayout);
//m_pD3D11ImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
//m_pD3D11ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//m_pD3D11ImmediateContext->VSSetShader(m_pSolidColorVS, 0, 0);
//m_pD3D11ImmediateContext->PSSetShader(m_pSolidColorPS, 0, 0);
//m_pD3D11ImmediateContext->Draw(3, 0);