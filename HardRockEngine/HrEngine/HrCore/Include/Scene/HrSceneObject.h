#ifndef _HR_SCENEOBJECT_H_
#define _HR_SCENEOBJECT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Scene/HrSceneObjectComponent.h"

namespace Hr
{
	class HR_CORE_API HrSceneObject
	{

	public:
		HrSceneObject();
		HrSceneObject(const HrRenderablePtr& pRenderable);
		~HrSceneObject();

		void AttachSceneNode(const HrSceneNodePtr& pSceneNode);

		void OnEnter();
		void OnExist();
		void Update(float fDelta, const HrTransformPtr& pTrans);

		void SetRenderable(const HrRenderablePtr& pRenderable);
		const HrRenderablePtr& GetRenderable();

		void AddComponent(const HrSceneObjectComponentPtr& pSceneObjComponent);
		const HrSceneObjectComponentPtr& AddComponent(HrSceneObjectComponent::EnumSceneComponentType comType);
		const HrSceneObjectComponentPtr& GetComponent(HrSceneObjectComponent::EnumSceneComponentType comType);

		template <typename T>
		std::shared_ptr<T> AddComponent();
		template <typename T>
		std::shared_ptr<T> GetComponent();
	private:
		void AddCameraToScene(const HrCameraPtr& pCamera);
		void AddLightToScene(const HrLightPtr& pLight);
	protected:
		std::weak_ptr<HrSceneNode> m_pContainerNode;

		HrRenderablePtr m_pRenderable;

		std::unordered_map<HrSceneObjectComponent::EnumSceneComponentType, HrSceneObjectComponentPtr> m_mapComponents;
		HrCameraComponentPtr m_pCachedCamera;
		HrLightComponentPtr m_pCachedLight;

	};

	template <typename T>
	std::shared_ptr<T> HrSceneObject::AddComponent()
	{
		if (typeid(T) == typeid(HrInstanceBatchComponent))
		{
			return HrCheckPointerCast<HrInstanceBatchComponent>(AddComponent(HrSceneObjectComponent::SCT_INSTANCEBATCH));
		}
	}

	template <typename T>
	std::shared_ptr<T> HrSceneObject::GetComponent()
	{
		if (typeid(T) == typeid(HrInstanceBatchComponent))
		{
			return HrCheckPointerCast<HrInstanceBatchComponent>(GetComponent(HrSceneObjectComponent::SCT_INSTANCEBATCH));
		}
	}

	}

#endif


