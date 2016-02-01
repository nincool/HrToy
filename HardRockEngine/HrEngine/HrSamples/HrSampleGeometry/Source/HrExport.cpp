#include "HrExport.h"
#include "HrGeometryApp.h"


extern "C" HR_EXPORT void HrModuleInitialize()
{
	Hr::HrGeometryApp::GetInstance().Run();
}

extern "C"  HR_EXPORT void HrModuleUnload(void)
{
	Hr::HrGeometryApp::GetInstance().ReleaseInstance();
}

