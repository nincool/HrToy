#ifndef _I_SCENENODE_H_
#define _I_SCENENODE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class ISceneNode : public SceneObjAllocatedObject
	{
	public:
		virtual ~ISceneNode(){}
	};
}

#endif
