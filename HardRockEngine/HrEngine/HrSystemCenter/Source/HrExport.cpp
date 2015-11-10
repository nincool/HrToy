#include "HrExport.h"
#include "HrDirector.h"

extern "C" HR_EXPORT  Hr::IDirector* HrModuleInitialize() throw()
{
	Hr::HrDirector* pDirector = Hr::HrDirector::GetInstance();

	return pDirector;
}

extern "C"  HR_EXPORT void HrModuleUnload(void)
{
	Hr::HrDirector::ReleaseInstance();
}

