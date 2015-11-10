#include "HrExport.h"


extern "C" HR_ENGINE_API  int HrModuleInitialize() throw()
{
	int a = 1 + 2;
	int b = 3 + 2;
	int c = a + b;
	 
	return c;
}

extern "C"  HR_ENGINE_API void HrModuleUnload(void)
{

}

