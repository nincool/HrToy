#ifndef _HR_SCENEOBJECT_H_
#define _HR_SCENEOBJECT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Scene/HrSceneObjectComponent.h"

namespace Hr
{
	class HR_CORE_API HrSceneObject : public std::enable_shared_from_this<HrSceneObject>
	{

	public:
		HrSceneObject();
		~HrSceneObject();

		void AttachSceneNode(const HrSceneNodePtr& pSceneNode);

		void OnEnter();
		void OnExist();
		void Update(float fDelta, const HrTransformPtr& pTrans);

		void AddComponent(const HrSceneObjectComponentPtr& pSceneObjComponent);
		HrSceneObjectComponentPtr AddComponent(HrSceneObjectComponent::EnumSceneComponentType comType);
		HrSceneObjectComponentPtr GetComponent(HrSceneObjectComponent::EnumSceneComponentType comType);

		template <typename T>
		std::shared_ptr<T> AddComponent();
		template <typename T>
		std::shared_ptr<T> GetComponent();

		HrSceneNodePtr GetSceneNode();
	private:
		void AddCameraToScene(const HrCameraPtr& pCamera);
		void AddLightToScene(const HrLightPtr& pLight);
	protected:
		std::weak_ptr<HrSceneNode> m_pContainerNode;

		std::unordered_map<HrSceneObjectComponent::EnumSceneComponentType, HrSceneObjectComponentPtr> m_mapComponents;
		HrSceneObjectComponentPtr m_pSceneObjMutexCom;

		HrCameraComponentPtr m_pCachedCamera;
		HrLightComponentPtr m_pCachedLight;

	};

	template <typename T>
	std::shared_ptr<T> HrSceneObject::AddComponent()
	{
		if (typeid(T) == typeid(HrInstanceBatchComponent))
		{
			return HrCheckPointerCast<T>(AddComponent(HrSceneObjectComponent::SCT_INSTANCEBATCH));
		}
		else if (typeid(T) == typeid(HrInstanceObjectComponent))
		{
			return HrCheckPointerCast<T>(AddComponent(HrSceneObjectComponent::SCT_INSTANCEOBJ));
		}
		else if (typeid(T) == typeid(HrRenderableComponent))
		{
			return HrCheckPointerCast<T>(AddComponent(HrSceneObjectComponent::SCT_RENDERABLE));
		}
		else
		{
			TRE("invalid component!");
		}
	}

	template <typename T>
	std::shared_ptr<T> HrSceneObject::GetComponent()
	{
		HrSceneObjectComponentPtr pSceneObjCom;
		if (typeid(T) == typeid(HrInstanceBatchComponent))
		{
			return HrCheckPointerCast<T>(GetComponent(HrSceneObjectComponent::SCT_INSTANCEBATCH));
		}
		else if (typeid(T) == typeid(HrRenderableComponent))
		{
			pSceneObjCom = GetComponent(HrSceneObjectComponent::SCT_RENDERABLE);
		}
		else if (typeid(T) == typeid(HrCameraComponet))
		{
			pSceneObjCom = GetComponent(HrSceneObjectComponent::SCT_CAMERA);
		}
		else if (typeid(T) == typeid(HrLightComponent))
		{
			pSceneObjCom = GetComponent(HrSceneObjectComponent::SCT_LIGHT);
		}
		else
		{
			TRE("invalid component!");
		}

		if (pSceneObjCom)
			return HrCheckPointerCast<T>(pSceneObjCom);
		else
			return nullptr;
	}

	}

#endif


