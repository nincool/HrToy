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
			NT_LIGHT,
		};

	public:
		HrSceneNode();
		HrSceneNode(HrRenderable* pRenderable);
		HrSceneNode(const std::string& strName, HrRenderable* pRenderable);
		virtual ~HrSceneNode();

		EnumNodeType GetNodeType() { return m_nodeType; }

		void AttachRenderable(HrRenderable* pRenderable);

		void SetName(const std::string& strName);
		const std::string& GetName() const;

		void SetEnable(bool bEnable);
		bool GetEnable() const;
		
		void SetParent(HrSceneNode* pParent);
		HrSceneNode* GetParent() const;
		HrSceneNode* GetNodeByNameFromHierarchy(const std::string& strName);

		HrRenderable* GetRenderable() const;
		
		HrTransform* GetTransform() const;

		void AddChild(HrSceneNode* pSceneNode);
		void RemoveChildren();

		bool IsRunning() const;

		virtual void OnEnter();
		virtual void OnEnterDidFinish();
		virtual void OnExist();

		//查找可渲染物件并且加入到渲染队列
		void FindVisibleRenderable(HrRenderQueuePtr& pRenderQueue);
		
		virtual void UpdateNode();
		void UpdateRenderParamData(HrRenderFrameParameters& renderFrameParameters);

		void DirtyTransform();
	protected:
		EnumNodeType m_nodeType;
		
		HrRenderable* m_pRenderable;
		
		std::string m_strName;
		bool m_bEnable;

		bool m_bRunning;

		HrSceneNode* m_pParent;
		std::vector<HrSceneNode*> m_vecChildNode;

		HrTransform* m_pTransform;

		bool m_bDirtyTransform;
	};
}

#endif

