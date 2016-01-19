#include "HrExport.h"
#include "HrD3D11Render.h"

extern "C" HR_EXPORT void HrModuleInitialize(Hr::IRenderPtr& ptr)
{
	ptr = std::dynamic_pointer_cast<Hr::IRender>(std::make_shared<Hr::HrD3D11Render>());
}

extern "C"  HR_EXPORT void HrModuleUnload(void)
{

}

