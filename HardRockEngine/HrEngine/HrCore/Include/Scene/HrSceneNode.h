#ifndef _HR_SCENENODE_H_
#define _HR_SCENENODE_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Kernel/HrIDObject.h"

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

		void SetSceneObject(const HrSceneObjectPtr& pSceneObj);
		const HrSceneObjectPtr& GetSceneObject();

		void SetEnable(bool bEnable);
		bool GetEnable() const;

		void SetParent(const HrSceneNodePtr& pParent);
		HrSceneNodePtr GetParent() const;
		const HrSceneNodePtr& GetChildByName(const std::string& strName) const;
		const HrSceneNodePtr& GetNodeByNameFromHierarchy(const std::string& strName);
		
		const HrTransformPtr& GetTransform() const;

		void AddChild(const HrSceneNodePtr& pSceneNode);
		void RemoveChildren();

		bool IsRunning() const;

		virtual void OnEnter();
		virtual void OnExist();
		virtual void UpdateNode(float fDt = 0.0f);

		void FindVisibleRenderable(HrRenderQueuePtr& pRenderQueue);

		void OnBeginRenderScene(const HrEventPtr& pEvent);
		void OnEndRenderScene(const HrEventPtr& pEvent);

		void DirtyPosition();

	private:
		void AddEventListeners();
		void RemoveEventListeners();

	protected:
		HrSceneObjectPtr m_pSceneObject;

		std::string m_strName;
		bool m_bEnable;
		bool m_bRunning;

		//parent
		std::weak_ptr<HrSceneNode> m_pParent;
		//children
		std::vector<HrSceneNodePtr> m_vecChildrenNode;

		HrTransformPtr m_pTransform;
	};
}

#endif

