#ifndef _HR_SAMPLECOMMON_H_
#define _HR_SAMPLECOMMON_H_

#include <memory>

#include "HrCore/Include/AppWin32/HrApplication_Win32.h"
#include "HrEngine.h"

namespace Hr
{
	class HrGeometryApp;
	typedef std::unique_ptr<HrGeometryApp> HrGeometryAppPtr;
}


#endif



