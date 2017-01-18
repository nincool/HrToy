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

		void AttachRenderable(HrRenderable* pRenderable);
		
		void SetParent(HrSceneNode* pParent) { m_pParent = pParent; }
		HrSceneNode* GetParent() { return m_pParent; }
		HrRenderable* GetRenderable() { return m_pRenderable; }
		HrTransform* GetTransform() { return m_pTransform; }

		void AddChild(HrSceneNode* pSceneNode);
		void RemoveChildren();

		//查找可渲染物件并且加入到渲染队列
		void FindVisibleRenderable(HrRenderQueuePtr& pRenderQueue);
		
		virtual void UpdateNode();
		void UpdateRenderParamData(HrRenderFrameParameters& renderFrameParameters);

		void DirtyTransform();
	protected:
		EnumNodeType m_nodeType;
		HrRenderable* m_pRenderable;

		HrSceneNode* m_pParent;
		std::vector<HrSceneNode*> m_vecChildNode;

		HrTransform* m_pTransform;

		bool m_bDirtyTransform;
	};
}

#endif

