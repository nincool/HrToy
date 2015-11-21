#include "HrExport.h"
#include "Win32/HrApplication_Win32.h"
#include "HrMain/Include/HrLog.h"

using namespace Hr;

extern "C" HR_EXPORT  void HrModuleInitialize() throw()
{
	auto pApp = HrApplication::GetInstance();
	HrLog::GetInstance()->Log(ILog::_HALL, "Test %d", 10);
	pApp->Run();
}

extern "C"  HR_EXPORT void HrModuleUnload(void)
{
	auto pApp = HrApplication::GetInstance();
	pApp->ReleaseInstance();
}

