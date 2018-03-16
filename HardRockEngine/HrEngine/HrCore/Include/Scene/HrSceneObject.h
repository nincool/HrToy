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
	private:
		void AddCameraToScene(const HrCameraPtr& pCamera);
		void AddLightToScene(const HrLightPtr& pLight);
	protected:
		std::weak_ptr<HrSceneNode> m_pContainerNode;
		//渲染对象
		HrRenderablePtr m_pRenderable;
		//组件
		std::unordered_map<HrSceneObjectComponent::EnumSceneComponentType, HrSceneObjectComponentPtr> m_mapComponents;
		HrCameraComponentPtr m_pCachedCamera;
		HrLightComponentPtr m_pCachedLight;


		std::list<HrCameraPtr> m_lisCameras;
		HrLightComponentPtr m_pLightComponent;
		std::list<HrSceneObjectComponentPtr> m_lisComponents;
	};


}

#endif


