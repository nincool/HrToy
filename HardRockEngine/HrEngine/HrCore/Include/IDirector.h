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

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HR_CORE_API IDirector : public GeneralAllocatedObject
	{
	public:
		IDirector(){}
		virtual ~IDirector(){}

		virtual bool Init() = 0;
		virtual void StartMainLoop() = 0;
		virtual void End() = 0;
		virtual void Release() = 0;

		virtual bool Render() = 0;

		//virtual void RunScene() = 0;
	};
}

#endif

