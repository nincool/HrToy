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

#include "HrMainPrerequisiters.h"
#include "ISupporter.h"

namespace Hr
{
	class ILog;

	class HR_MAIN_API HrSystemSupporter : public ISupporter
	{
	public:
		HrSystemSupporter();
		~HrSystemSupporter();

	public:
		virtual bool Init() override;
		
	};
}

#endif

