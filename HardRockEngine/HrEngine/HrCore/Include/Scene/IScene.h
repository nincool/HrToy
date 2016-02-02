#ifndef _I_SCENE_H_
#define _I_SCENE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IScene : public SceneObjAllocatedObject
	{
	public:
		virtual ~IScene(){};

		virtual void OnEnter() = 0;
		virtual void OnEnterDidFinish() = 0;
	};
}

#endif



