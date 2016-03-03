#ifndef _I_SCENENODE_H_
#define _I_SCENENODE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class IRenderable;

	class ISceneNode : public SceneObjAllocatedObject
	{
	public:
		virtual ~ISceneNode(){}

		virtual ISceneNode* GetParent() = 0;
		virtual IRenderable* GetRenderable() = 0;

		virtual void AddChild(ISceneNode* pSceneNode) = 0;
		virtual void FindVisibleRenderable(IRenderQueuePtr& pRenderQueue) = 0;
		virtual void RemoveChildren() = 0;
	protected:

	};
}

#endif
