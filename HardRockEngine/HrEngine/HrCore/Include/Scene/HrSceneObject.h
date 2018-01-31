#ifndef _HR_SCENEOBJECT_H_
#define _HR_SCENEOBJECT_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrSceneObject
	{
	public:
		enum EnumSceneComponentType
		{
			SCT_NORMAL,
			SCT_CAMERA,
		};
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

		void AddComponent(EnumSceneComponentType comType, const HrSceneObjectComponentPtr& pSceneObjComponent);
	private:
		void AddCameraToScene(const HrCameraPtr& pCamera);
	protected:
		std::weak_ptr<HrSceneNode> m_pContainerNode;

		HrRenderablePtr m_pRenderable;

		std::list<HrCameraPtr> m_lisCameras;
		std::list<HrSceneObjectComponentPtr> m_lisComponents;
	};


}

#endif


