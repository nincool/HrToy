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
			SCT_INSTANCEBATCH,

			SCT_COM_COUNT,
		};
	public:
		HrSceneObjectComponent(const std::string& strName);
		~HrSceneObjectComponent();

		virtual bool InitComponent() override;
		virtual bool Update(float fDelta) override;

		const std::string& GetName();
		EnumSceneComponentType GetComType();
	protected:
		std::string m_strName;
		EnumSceneComponentType m_comType;
	};

	class HR_CORE_API HrCameraComponet : public HrSceneObjectComponent
	{
	public:
		HrCameraComponet(const std::string& strName);
		~HrCameraComponet();

		const HrCameraPtr& GetCamera();
	protected:
		HrCameraPtr m_pCamera;
	};

	class HR_CORE_API HrLightComponent : public HrSceneObjectComponent
	{
	public:
		HrLightComponent(const std::string& strName, HrLight::EnumLightType lightType);
		~HrLightComponent();

		const HrLightPtr& GetLight();
	protected:
		HrLightPtr m_pLight;
	};

	class HR_CORE_API HrInstanceBatchComponent : public HrSceneObjectComponent
	{
	public:
		HrInstanceBatchComponent(const std::string& strName);
		~HrInstanceBatchComponent();

		HrSceneNodePtr CreateInstance(const std::string& strName = "Default_Instance");
	protected:
		HrInstanceBatchManagerPtr m_pInstanceBatchManager;

	};
}

#endif


