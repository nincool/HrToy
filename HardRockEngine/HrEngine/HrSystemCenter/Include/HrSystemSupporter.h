/************************************************************************
*
* @Comment£º
*
* @Author: Hr
* @Date: [11/6/2015 By Hr]
*
************************************************************************/  
#ifndef _HR_SYSTEMSUPPORTER_H_
#define _HR_SYSTEMSUPPORTER_H_

#include "HrSystemCenterPrerequisites.h"

namespace Hr
{
	class ILog;

	class HrSystemSupporter
	{
	public:
		HrSystemSupporter();
		~HrSystemSupporter();

		//Log
		HR_SYNTHESIZE_READONLY(ILog*, m_pLog, Log);
	};
}

#endif

