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

		virtual void RunScene(const IScenePtr& pScene) = 0;
		virtual void StopScene() = 0;

		virtual void UpdateScene() = 0;
		virtual void RenderScene(IRenderTargetPtr& renderTarget) = 0;
		virtual void Destroy() = 0;
	};
}

#endif





