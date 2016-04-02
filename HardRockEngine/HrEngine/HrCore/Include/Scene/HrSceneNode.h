#ifndef _HR_SCENENODE_H_
#define _HR_SCENENODE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"

namespace Hr
{
	class HrSceneNode : public SceneObjAllocatedObject
	{
	public:
		enum EnumNodeType
		{
			NT_NORMAL,
			NT_CAMERA,
		};

		HrSceneNode();
		HrSceneNode(IRenderable* pRenderable);
		virtual ~HrSceneNode();

		EnumNodeType GetNodeType();
		HrSceneNode* GetParent();
		IRenderable* GetRenderable();

		void AddChild(HrSceneNode* pSceneNode);
		void FindVisibleRenderable(HrRenderQueuePtr& pRenderQueue);
		void RemoveChildren();

		void UpdateNode(HrRenderFrameParameters& renderFrameParameters);

		void SetPosition(const Vector3& v3Pos);
		void SetPosition(REAL x, REAL y, REAL z);
		const Vector3& GetPosition();
		virtual void Translate(const Vector3& v3);
	protected:
		EnumNodeType m_nodeType;
		IRenderable* m_pRenderable;

		HrSceneNode* m_pParent;
		std::vector<HrSceneNode*> m_vecChildNode;

		//相对父节点的位置
		Vector3 m_v3LocalPosition;


	};
}

#endif

