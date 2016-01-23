#include "HrExport.h"
#include "HrRenderD3D11/Include/HrD3D11Render.h"

extern "C" HR_EXPORT void HrModuleInitialize(Hr::IRenderPtr& ptr)
{
	ptr = std::dynamic_pointer_cast<Hr::IRender>(Hr::MakeSharedPtr<Hr::HrD3D11Render>());
}

extern "C"  HR_EXPORT void HrModuleUnload(void)
{

}

