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
			SCT_TRACKBALLCAMERA,

			SCT_COM_COUNT,
		};
	public:
		HrSceneObjectComponent(const std::string& strName, HrSceneObject* pSceneObj);
		~HrSceneObjectComponent();

		virtual bool InitComponent() override;
		virtual bool Update(float fDelta) override;
		
		virtual void OnEnter() {};
		virtual void OnExist() {};
		virtual bool IsMutex() = 0;
		

		const std::string& GetName();
		EnumSceneComponentType GetComType();

		HrSceneObject* GetAttachSceneObject();

		virtual void UpdateTransform(const HrTransformPtr& pTransform);
	protected:
		std::string m_strName;
		EnumSceneComponentType m_comType;
		/*
			@brief	宿主SceneObject 因为是主从关系 往往伴随着主的销毁而销毁 所以直接用原始指针或者引用 [10/29/2018 By Hr]
		*/
		HrSceneObject* m_pSceneObj;
	};

	class HR_CORE_API HrSceneObjectMutexCom : public HrSceneObjectComponent
	{
	public:
		HrSceneObjectMutexCom(const std::string& strName, HrSceneObject* pSceneObj);
		~HrSceneObjectMutexCom();

		virtual bool IsMutex() override
		{
			return true;
		}
	};

	class HR_CORE_API HrSceneObjectSharedCom : public HrSceneObjectComponent
	{
	public:
		HrSceneObjectSharedCom(const std::string& strName, HrSceneObject* pSceneObj);
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

		HrCameraComponet(const std::string& strName, HrSceneObject* pSceneObj);
		~HrCameraComponet();

		virtual void OnEnter() override;
		virtual void UpdateTransform(const HrTransformPtr& pTransform) override;

		const HrCameraPtr& GetCamera();
		const HrViewPortPtr& GetViewPort();

		void SetFov(float fFov);
		void SetAspect(float fAspect);
		void SetNearPlane(float fNear);
		void SetFarPlane(float fFar);
	protected:
		HrViewPortPtr m_pViewPort;
		HrCameraPtr m_pCamera;
	};

	class HR_CORE_API HrTrackBallCameraController : public HrSceneObjectSharedCom
	{
	public:
		HrTrackBallCameraController(const std::string& strName, HrSceneObject* pSceneObj);
		~HrTrackBallCameraController();

		virtual void OnEnter() override;

		void Move() {};
		void Rotate(const Vector3& v);
		void Zoom(float fZ);
	protected:
		HrCameraComponentPtr m_pCameraCom;

		Vector3 m_vTarget;
		Vector3 m_vRight;

		float m_fRotationScaler;
		float m_fMoveScaler;
		float m_fZoomScaler;
	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////

	class HR_CORE_API HrLightComponent : public HrSceneObjectMutexCom
	{
	public:
		HrLightComponent(const std::string& strName, HrSceneObject* pSceneObj, HrLight::EnumLightType lightType);
		~HrLightComponent();

		const HrLightPtr& GetLight();

		void SetColor(const HrColor& color);
		const HrColor& GetColor() const;

		virtual void UpdateTransform(const HrTransformPtr& pTransform) override;
	protected:
		HrLightPtr m_pLight;
	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////

	class HR_CORE_API HrRenderableComponent : public HrSceneObjectMutexCom
	{
	public:
		HrRenderableComponent(const std::string& strName, HrSceneObject* pSceneObj);
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
		HrInstanceBatchComponent(const std::string& strName, HrSceneObject* pSceneObj);
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
		HrInstanceObjectComponent(const std::string& strName, HrSceneObject* pSceneObj);
		~HrInstanceObjectComponent();
	};


}

#endif


