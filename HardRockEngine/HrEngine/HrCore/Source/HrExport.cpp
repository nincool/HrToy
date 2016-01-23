#include "HrExport.h"
#include "AppWin32/HrApplication_Win32.h"

using namespace Hr;

extern "C" HR_EXPORT void HrModuleInitialize()
{
	HrApplication::GetInstance()->Run();
}

extern "C"  HR_EXPORT void HrModuleUnload(void)
{
	HrApplication::ReleaseInstance();
}

