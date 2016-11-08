#ifndef _HR_SCENENODE_H_
#define _HR_SCENENODE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Kernel/HrIDObject.h"

namespace Hr
{
	class HR_CORE_API HrSceneNode : public HrIDObject
	{
	public:
		enum EnumNodeType
		{
			NT_NORMAL,
			NT_CAMERA,
		};

	public:
		HrSceneNode();
		HrSceneNode(HrRenderable* pRenderable);
		virtual ~HrSceneNode();

		EnumNodeType GetNodeType() { return m_nodeType; }
		
		HrSceneNode* GetParent() { return m_pParent; }

		HrRenderable* GetRenderable() { return m_pRenderable; }

		HrTransform* GetTransfrom() { return m_pTransform; }

		void AddChild(HrSceneNode* pSceneNode);
		
		void FindVisibleRenderable(HrRenderQueuePtr& pRenderQueue);
		
		void RemoveChildren();

		virtual void UpdateNode();
		
		void UpdateRenderParamData(HrRenderFrameParameters& renderFrameParameters);

		void DirtyTransform();
	protected:
		EnumNodeType m_nodeType;
		HrRenderable* m_pRenderable;

		HrSceneNode* m_pParent;
		std::vector<HrSceneNode*> m_vecChildNode;

		HrTransform* m_pTransform;

		bool m_bDirtyView;
	};
}

#endif

