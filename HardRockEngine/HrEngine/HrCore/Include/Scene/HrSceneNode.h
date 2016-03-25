#ifndef _HR_SCENENODE_H_
#define _HR_SCENENODE_H_


#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HrSceneNode : public SceneObjAllocatedObject
	{
	public:
		HrSceneNode();
		HrSceneNode(IRenderable* pRenderable);
		~HrSceneNode();

		HrSceneNode* GetParent();
		IRenderable* GetRenderable();

		void AddChild(HrSceneNode* pSceneNode);
		void FindVisibleRenderable(HrRenderQueuePtr& pRenderQueue);
		void RemoveChildren();

		void UpdateNode(HrRenderFrameParameters& renderFrameParameters);
	protected:
		IRenderable* m_pRenderable;

		HrSceneNode* m_pParent;
		std::vector<HrSceneNode*> m_vecChildNode;
	};
}

#endif

