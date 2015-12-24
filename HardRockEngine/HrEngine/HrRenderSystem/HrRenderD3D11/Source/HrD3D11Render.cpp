#include "HrD3D11Render.h"
#include "HrD3D11Device.h"
#include "HrD3D11Utility.h"

#include "HrRenderDemo/Include/HrRenderD3D11Demo.h"

using namespace Hr;
using namespace DirectX;

HrD3D11Render* HrD3D11Render::m_s_pInstance = nullptr;

HrD3D11Render::HrD3D11Render()
{
	m_pRenderDemo = HR_NEW HrRenderD3D11Demo();
}

HrD3D11Render::~HrD3D11Render()
{
	HrD3D11Device::ReleaseInstance();
	HrD3D11Utility::ReleaseInstance();
}

#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
bool HrD3D11Render::Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc)
{
	HrD3D11Utility::GetInstance()->Init(nWidth, nHeight, lpfnProc);

	m_pRenderDemo->SetD3DDevice(HrD3D11Device::GetInstance()->GetDevice(), HrD3D11Device::GetInstance()->GetImmediateContext());

	return true;
}
#else
bool HrD3D11Render::Init(unsigned int nWidth, unsigned int nHeight)
{
}
#endif

void HrD3D11Render::Release()
{
	HrD3D11Device::GetInstance()->Release();
	m_pRenderDemo->Release();
}

bool HrD3D11Render::StartRender()
{
	XMVECTORF32 Blue = { 0.69f, 0.77f, 0.87f, 1.0f };
	HrD3D11Device::GetInstance()->GetImmediateContext()->ClearRenderTargetView(HrD3D11Device::GetInstance()->GetRenderTargetView(), reinterpret_cast<const float*>(&Blue));
	HrD3D11Device::GetInstance()->GetImmediateContext()->ClearDepthStencilView(HrD3D11Device::GetInstance()->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_pRenderDemo->Render();

	HrD3D11Device::GetInstance()->GetSwapChain()->Present(0, 0);
	return true;
}

