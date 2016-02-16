#ifndef _I_SCENE_H_
#define _I_SCENE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HR_CORE_API IScene : public SceneObjAllocatedObject
	{
	public:
		virtual ~IScene(){};

		virtual void OnEnter() = 0;
		virtual void OnEnterDidFinish() = 0;

		virtual void AddChild(ISceneNode* pSceneNode) = 0;

		virtual void Update() = 0;
		virtual void FillRenderQueue(IRenderQueuePtr& pRenderQueue) = 0;
	};
}

#endif



