#include "HrExport.h"
#include "HrGeometryApp.h"


extern "C" HR_EXPORT void HrModuleInitialize()
{
	Hr::HrGeometryApp::Instance()->Run();
}

extern "C"  HR_EXPORT void HrModuleUnload(void)
{
	Hr::HrGeometryApp::Instance()->Destroy();
}

