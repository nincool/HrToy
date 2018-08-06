#pragma once

namespace Hr
{
	class HrMeshConvertCore;
	public ref class HrMeshConvertWrapper
	{
	public:
		explicit HrMeshConvertWrapper(System::IntPtr native_wnd);
		~HrMeshConvertWrapper();

	private:
		HrMeshConvertCore* core_;

	};
}


