#include "HrExport.h"
#include "HrD3D11Render.h"


extern "C" HR_EXPORT Hr::IRender* HrModuleInitialize() throw()
{
	Hr::IRender* m_s_pRender = Hr::HrD3D11Render::GetInstance();
	
	return m_s_pRender;
}

extern "C"  HR_EXPORT void HrModuleUnload(void)
{
	Hr::HrD3D11Render::GetInstance()->Release();
	Hr::HrD3D11Render::ReleaseInstance();
}

