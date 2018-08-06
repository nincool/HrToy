#pragma once

#include "HrCommon/Include/HrPrerequisite.h"
#include "HrCore/Include/Platform/AppWin/HrAppWindows.h"

#ifdef HR_MESHCONVERTCORE_EXPORT
#define HR_MESHCONVERTCORE_API HR_EXPORT
#else
#define HR_MESHCONVERTCORE_API HR_IMPORT
#endif

namespace Hr
{
	class HR_MESHCONVERTCORE_API HrMeshConvertCore : public HrAppWindows
	{
	public:
		HrMeshConvertCore(void* pWnd);
		~HrMeshConvertCore();

		virtual void Run() override;

	private:
		void* m_pWnd;
	};
}

