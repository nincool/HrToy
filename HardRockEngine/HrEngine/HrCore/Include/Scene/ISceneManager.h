#ifndef _I_SCENEMANAGER_H_
#define _I_SCENEMANAGER_H_

#include "HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class ISceneManager : public SceneObjAllocatedObject
	{
	public:
		virtual ~ISceneManager(){}

		virtual const ISceneNodePtr& GetRootNode() = 0;

		virtual void RunScene(const IScenePtr& pScene) = 0;

	};
}

#endif





