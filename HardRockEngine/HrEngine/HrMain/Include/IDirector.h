/************************************************************************
*
* @Comment：
*
* @Author: Hr
* @Date: [10/29/2015 By Hr]
*
************************************************************************/  

#ifndef _I_DIRECTOR_H_
#define _I_DIRECTOR_H_

#include "HrMainPrerequisiters.h"

namespace Hr
{
	class HrSystemSupporter;

	class HR_MAIN_API IDirector
	{
	public:
		IDirector(){}
		virtual ~IDirector(){}

		virtual bool Init() = 0;
		virtual void StartMainLoop() = 0;
		virtual void PurgeDirector() = 0;

	};
}

#endif

