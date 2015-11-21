#include "HrD3D11Render.h"
#include "HrD3D11Device.h"
#include "HrD3D11Utility.h"

using namespace Hr;

HrD3D11Render* HrD3D11Render::m_s_pInstance = nullptr;

HrD3D11Render::HrD3D11Render()
{
	m_pD3D11Device = HNEW(HrD3D11Device);
}

HrD3D11Render::~HrD3D11Render()
{
	SAFE_DELETE(m_pD3D11Device);
}

#if (HR_TARGET_PLATFORM == HR_PLATFORM_WIN32)
bool HrD3D11Render::Init(unsigned int nWidth, unsigned int nHeight, WNDPROC lpfnProc)
{
	HrD3D11Utility::GetInstance()->Init(nWidth, nHeight, lpfnProc);
	

	return true;
}
#else
bool HrD3D11Render::Init(unsigned int nWidth, unsigned int nHeight)
{
}
#endif

void HrD3D11Render::Destroy()
{

}

bool HrD3D11Render::CreateD3D11Device()
{
	return true;
}
