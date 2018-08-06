#include "HrMeshConvertCoreWrapper.h"
#include "HrTools/HrMeshConvertCore/HrMeshConvertCore.h"
#include <iostream>

using namespace Hr;

HrMeshConvertWrapper::HrMeshConvertWrapper(System::IntPtr native_wnd)
{
	core_ = new HrMeshConvertCore(native_wnd.ToPointer());
	core_->Run();
}

HrMeshConvertWrapper::~HrMeshConvertWrapper()
{
	delete core_;
}
