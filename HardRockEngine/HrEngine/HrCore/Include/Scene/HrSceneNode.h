#ifndef _HR_SCENENODE_H_
#define _HR_SCENENODE_H_

#include "ISceneNode.h"

namespace Hr
{
	class HrSceneNode : public ISceneNode
	{
	public:
		HrSceneNode();
		HrSceneNode(IRenderable* pRenderable);
		~HrSceneNode();

		virtual ISceneNode* GetParent() override;
		virtual IRenderable* GetRenderable() override;

		virtual void AddChild(ISceneNode* pSceneNode) override;
		virtual void FindVisibleRenderable(IRenderQueuePtr& pRenderQueue) override;
		virtual void RemoveChildren() override;

		virtual void UpdateNode(HrRenderFrameParameters& renderFrameParameters) override;
	protected:
		IRenderable* m_pRenderable;

		ISceneNode* m_pParent;
		std::vector<ISceneNode*> m_vecChildNode;
	};
}

#endif

