/************************************************************************
*
* @Comment£º
*
* @Author: Hr
* @Date: [12/5/2015 By Hr]
*
************************************************************************/  
#ifndef _I_TIMER_H_
#define _I_TIMER_H_

#include "HrMainPrerequisiters.h"

namespace Hr
{
	class HR_MAIN_API ITimer
	{
	public:
		virtual ~ITimer(){};

		virtual void ResetTimer() = 0;

		//The function Tick is called in the application message loop
		virtual void Tick() = 0;

		virtual float DeltaTime() = 0;

		virtual void PauseTimer() = 0;
		virtual void ContinueTimer() = 0;
	};
}

#endif