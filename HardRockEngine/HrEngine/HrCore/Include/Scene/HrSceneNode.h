#ifndef _HR_SCENENODE_H_
#define _HR_SCENENODE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Kernel/HrIDObject.h"
#include "HrCore/Include/Scene/HrTransform.h"

namespace Hr
{
	class HR_CORE_API HrSceneNode : public HrIDObject, public std::enable_shared_from_this<HrSceneNode>
	{
	public:
		HrSceneNode();
		HrSceneNode(const std::string& strName);
		
		virtual ~HrSceneNode();

		void SetName(const std::string& strName);
		const std::string& GetName() const;

		const HrSceneObjectPtr& GetSceneObject();

		const HrSceneNode* GetParent() const;

		size_t GetChildrenCount();
		/**
		 @Comment: ��ȡ�ӽڵ� [10/29/2018 By Hr]
		 @Param: int �ڵ�����
		 @Return: �ӽڵ�����ָ�� ���û���ҵ�����nullptr
		*/
		const HrSceneNodePtr& GetChildByIndex(int nNodeIndex);
		/**
		 @Comment: ��ȡ�ӽڵ� [10/29/2018 By Hr]
		 @Param: string �ڵ�����
		 @Return: �ӽڵ�����ָ�� ���û���ҵ�����nullptr
		*/
		const HrSceneNodePtr& GetChildByName(const std::string& strName) const;
		/**
		 @Comment: �����Դ˽ڵ�Ϊ���ڵ�������νṹ ��ȡ�ӽڵ� [10/29/2018 By Hr]
		 @Param: string �ڵ�����
		 @Return: �ӽڵ�����ָ�� ���û���ҵ�����nullptr
		*/
		const HrSceneNodePtr& GetNodeByNameFromHierarchy(const std::string& strName);
		
		const HrTransformPtr& GetTransform() const;

		void AddChild(const HrSceneNodePtr& pSceneNode);
		bool RemoveChild(const HrSceneNodePtr& pChild);
		void RemoveChildren();
		bool RemoveFromParent();

		bool IsRunning() const;

		virtual void OnEnter();
		virtual void OnExist();
		virtual void UpdateNode(float fDt = 0.0f);

		void FindVisibleRenderable(HrRenderQueuePtr& pRenderQueue);
		void FindVisibleRenderables(const HrRenderQueueManagerPtr& pRenderQueueManager);

		/**
		 @Comment: ��ȡ�ڵ�����ӽڵ��Renderables [10/26/2018 By Hr]
		 @Param:   in|out vector 
		*/
		void FindAllRenderables(std::vector<HrSceneNodePtr>& vecRenderables);

		void OnBeginRenderScene(const HrEventPtr& pEvent);
		void OnEndRenderScene(const HrEventPtr& pEvent);

		void DirtyTransfrom(bool bDirtyPos, bool bDirtyScale, bool bDirtyOrientation);

		HrMath::EnumVisibility GetFrustumVisible();
		void SetFrustumVisible(HrMath::EnumVisibility visible);
	protected:
		void SetParent(HrSceneNode* pParentNode);
		
	private:
		void AddEventListeners();
		void RemoveEventListeners();

	protected:
		std::string m_strName;
		bool m_bRunning;
		HrMath::EnumVisibility m_nFrustumVisibleMark;

		HrSceneObjectPtr m_pSceneObject;

		//parent
		HrSceneNode* m_pParentNode;

		//children
		std::vector<HrSceneNodePtr> m_vecChildrenNode;

		HrTransformPtr m_pTransform;
	};
}

#endif

