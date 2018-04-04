#ifndef _HR_SCENEOBJECTCOMPONENT_H_
#define _HR_SCENEOBJECTCOMPONENT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/Include/HrComponent.h"
#include "HrCore/Include/Render/HrLight.h"

namespace Hr
{
	class HR_CORE_API HrSceneObjectComponent : public HrComponent
	{
	public:
		enum EnumSceneComponentType
		{
			SCT_NORMAL,
			SCT_CAMERA,
			SCT_LIGHT,
			SCT_RENDERABLE,
			SCT_INSTANCEBATCH,
			SCT_INSTANCEOBJ,

			SCT_COM_COUNT,
		};
	public:
		HrSceneObjectComponent(const std::string& strName, const HrSceneObjectPtr& pSceneObj);
		~HrSceneObjectComponent();

		virtual bool InitComponent() override;
		virtual bool Update(float fDelta) override;

		virtual bool IsMutex() = 0;

		const std::string& GetName();
		EnumSceneComponentType GetComType();

		HrSceneObjectPtr GetAttachSceneObject();
	protected:
		std::string m_strName;
		EnumSceneComponentType m_comType;
		std::weak_ptr<HrSceneObject> m_pAttachSceneObj;
	};

	class HR_CORE_API HrSceneObjectMutexCom : public HrSceneObjectComponent
	{
	public:
		HrSceneObjectMutexCom(const std::string& strName, const HrSceneObjectPtr& pSceneObj);
		~HrSceneObjectMutexCom();

		virtual bool IsMutex() override
		{
			return true;
		}
	};

	class HR_CORE_API HrSceneObjectSharedCom : public HrSceneObjectComponent
	{
	public:
		HrSceneObjectSharedCom(const std::string& strName, const HrSceneObjectPtr& pSceneObj);
		~HrSceneObjectSharedCom();

		virtual bool IsMutex() override
		{
			return false;
		}
	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////

	class HR_CORE_API HrCameraComponet : public HrSceneObjectMutexCom
	{
	public:
		HrCameraComponet(const std::string& strName, const HrSceneObjectPtr& pSceneObj);
		~HrCameraComponet();

		const HrCameraPtr& GetCamera();
	protected:
		HrCameraPtr m_pCamera;
	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////

	class HR_CORE_API HrLightComponent : public HrSceneObjectMutexCom
	{
	public:
		HrLightComponent(const std::string& strName, const HrSceneObjectPtr& pSceneObj, HrLight::EnumLightType lightType);
		~HrLightComponent();

		const HrLightPtr& GetLight();
	protected:
		HrLightPtr m_pLight;
	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////

	class HR_CORE_API HrRenderableComponent : public HrSceneObjectMutexCom
	{
	public:
		HrRenderableComponent(const std::string& strName, const HrSceneObjectPtr& pSceneObj);
		~HrRenderableComponent();

		void SetRenderable(const HrRenderablePtr& pRenderable);
		const HrRenderablePtr & GetRenderable() { return m_pRenderable; }
	protected:
		HrRenderablePtr m_pRenderable;
	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////
	class HR_CORE_API HrInstanceBatchComponent : public HrSceneObjectSharedCom
	{
	public:
		HrInstanceBatchComponent(const std::string& strName, const HrSceneObjectPtr& pSceneObj);
		~HrInstanceBatchComponent();

		void CreateInstanceBatch(const HrSubMeshPtr& pSubMesh);

		const HrInstanceBatchPtr& GetInstanceBatch();
		HrSceneNodePtr CreateInstance(const std::string& strName = "Default_Instance");

	protected:
		HrInstanceBatchPtr m_pInsBatch;
	};

	class HR_CORE_API HrInstanceObjectComponent : public HrSceneObjectMutexCom
	{
	public:
		HrInstanceObjectComponent(const std::string& strName, const HrSceneObjectPtr& pSceneObj);
		~HrInstanceObjectComponent();
	};


}

#endif


