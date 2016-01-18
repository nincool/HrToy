#include "HrD3D11Render.h"
#include "HrD3D11Device.h"
#include "HrD3D11Utility.h"

#include "HrRenderDemo/Include/HrRenderDemo.h"

using namespace Hr;
using namespace DirectX;

HrD3D11Render* HrD3D11Render::m_s_pInstance = nullptr;

HrD3D11Render::HrD3D11Render()
{
	typedef HrRenderD3D11DemoHrMath DEMOCLASS;

	m_pRenderDemo = HR_NEW DEMOCLASS();
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
	HrD3D11Render::GetInstance()->Release();
	m_pRenderDemo->Release();
}

bool HrD3D11Render::StartRender()
{
	m_pRenderDemo->Render();

	return true;
}

