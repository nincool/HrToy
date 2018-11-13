#ifndef _HR_SCENEOBJECT_H_
#define _HR_SCENEOBJECT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/Scene/HrSceneObjectComponent.h"

namespace Hr
{
	class HR_CORE_API HrSceneObject : public std::enable_shared_from_this<HrSceneObject>
	{

	public:
		/**
		 @Comment: 因为和Node是相辅相成的，所以作为Node的一个组成部分吧 [10/29/2018 By Hr]
		*/
		HrSceneObject(HrSceneNode* pSceneNode);
		~HrSceneObject();

		void OnEnter();
		void OnExist();
		void Update(float fDelta);
		void OnNodeTransformDirty(const HrTransformPtr& pTrans);

		void AddComponent(const HrSceneObjectComponentPtr& pSceneObjComponent);
		HrSceneObjectComponentPtr AddComponent(HrSceneObjectComponent::EnumSceneComponentType comType);
		HrSceneObjectComponentPtr GetComponent(HrSceneObjectComponent::EnumSceneComponentType comType);
		const HrRenderableComponentPtr& GetRenderableComponent();

		template <typename T>
		std::shared_ptr<T> AddComponent();
		template <typename T>
		std::shared_ptr<T> GetComponent();

		const HrSceneNode* GetSceneNode() const;
	private:
		void AddCameraToScene();
		void AddLightToScene(const HrLightPtr& pLight);
	protected:
		HrSceneNode* m_pContainerNode;

		std::unordered_map<HrSceneObjectComponent::EnumSceneComponentType, HrSceneObjectComponentPtr> m_mapComponents;
		HrSceneObjectComponentPtr m_pSceneObjMutexCom;

		HrRenderableComponentPtr m_pCachedRenderable;
		HrCameraComponentPtr m_pCachedCamera;
		HrLightComponentPtr m_pCachedLight;

	};

	template <typename T>
	std::shared_ptr<T> HrSceneObject::AddComponent()
	{
		const std::type_info &typeInfo = typeid(T);
		if (typeInfo == typeid(HrInstanceBatchComponent))
		{
			return HrCheckPointerCast<T>(AddComponent(HrSceneObjectComponent::SCT_INSTANCEBATCH));
		}
		else if (typeInfo == typeid(HrInstanceObjectComponent))
		{
			return HrCheckPointerCast<T>(AddComponent(HrSceneObjectComponent::SCT_INSTANCEOBJ));
		}
		else if (typeInfo == typeid(HrRenderableComponent))
		{
			return HrCheckPointerCast<T>(AddComponent(HrSceneObjectComponent::SCT_RENDERABLE));
		}
		else if (typeInfo == typeid(HrCameraComponet))
		{
			return HrCheckPointerCast<T>(AddComponent(HrSceneObjectComponent::SCT_CAMERA));
		}
		else if (typeInfo == typeid(HrTrackBallCameraController))
		{
			return HrCheckPointerCast<T>(AddComponent(HrSceneObjectComponent::SCT_TRACKBALLCAMERA));
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


