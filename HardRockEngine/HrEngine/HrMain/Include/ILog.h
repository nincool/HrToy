/************************************************************************
*
* @Comment£º
*
* @Author: Hr
* @Date: [11/13/2015 By Hr]
*
************************************************************************/  
#ifndef _I_LOG_H_
#define _I_LOG_H_

#include "HrMainPrerequisiters.h"
#include "MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HR_MAIN_API ILog : public GeneralAllocatedObject
	{
	public:
		ILog(){}
		virtual ~ILog(){}

		enum EnumLogType
		{
			_HALL = 0,
			_HDEBUG,
			_HNOTE,
			_HWARNING,
			_HERROR,
		};
	};
}

#endif // !_I_LOG_H_
