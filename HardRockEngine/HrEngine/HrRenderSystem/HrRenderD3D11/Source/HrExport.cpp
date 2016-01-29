#include "HrExport.h"
#include "HrRenderD3D11/Include/HrD3D11RenderFactory.h"

extern "C" HR_EXPORT void HrModuleInitialize(Hr::IRenderFactoryPtr& ptr)
{
	ptr = std::dynamic_pointer_cast<Hr::IRenderFactory>(Hr::MakeSharedPtr<Hr::HrD3D11RenderFactory>());
}

extern "C"  HR_EXPORT void HrModuleUnload(void)
{

}

