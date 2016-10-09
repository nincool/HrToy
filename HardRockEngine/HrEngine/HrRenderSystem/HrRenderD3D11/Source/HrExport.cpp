#include "HrExport.h"
#include "HrRenderD3D11/Include/HrD3D11RenderFactory.h"

extern "C" HR_EXPORT void HrModuleInitialize(Hr::HrRenderFactoryPtr& ptr)
{
	ptr = std::static_pointer_cast<Hr::HrRenderFactory>(Hr::MakeSharedPtr<Hr::HrD3D11RenderFactory>());
}

extern "C"  HR_EXPORT void HrModuleUnload(void)
{

}

