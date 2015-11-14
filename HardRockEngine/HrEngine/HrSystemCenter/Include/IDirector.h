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

#include "HrSystemCenterPrerequisites.h"

namespace Hr
{
	class HrSystemSupporter;

	class IDirector
	{
	public:
		IDirector(){}
		virtual ~IDirector(){}

		virtual bool Init() = 0;
		virtual void Go() = 0;

	};
}

#endif

