#ifndef _HR_SCENEOBJECTCOMPONENT_H_
#define _HR_SCENEOBJECTCOMPONENT_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCommon/Include/HrComponent.h"
#include "HrCore/Include/Render/HrLight.h"
#include "HrCore/Include/Render/HrCamera.h"
#include "HrCore/Include/Event/HrEvent.h"

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
			SCT_UICANVAS,
			SCT_UI,
			SCT_SKYBOX,

			SCT_COM_COUNT,
		};
	public:
		HrSceneObjectComponent(const std::string& strName, HrSceneObject* pSceneObj);
		~HrSceneObjectComponent();

		virtual bool InitComponent() override;
		virtual bool Update(float fDelta) override;
		
		virtual void OnEnter() {};
		virtual void OnExist() {};

		const std::string& GetName();
		int GetComType();

		HrSceneObject* GetAttachSceneObject();

		virtual void UpdateTransform(const HrTransformPtr& pTransform);
	protected:
		std::string m_strName;
		int m_comType;
		/*
			@brief	宿主SceneObject 因为是主从关系 往往伴随着主的销毁而销毁 所以直接用原始指针或者引用 [10/29/2018 By Hr]
		*/
		HrSceneObject* m_pSceneObj;
	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////

	class HR_CORE_API HrCameraComponet : public HrSceneObjectComponent
	{
	public:

		HrCameraComponet(const std::string& strName, HrSceneObject* pSceneObj);
		~HrCameraComponet();

		virtual void OnEnter() override;
		virtual void UpdateTransform(const HrTransformPtr& pTransform) override;

		const HrCameraPtr& GetCamera();
		const HrViewPortPtr& GetViewPort();

		void SetCameraType(HrCamera::EnumCameraType cameraType);
		void SetFov(float fFov);
		void SetAspect(float fAspect);
		void SetNearPlane(float fNear);
		void SetFarPlane(float fFar);

		void OnEndRenderScene(const HrEventPtr& pEvent);

		int GetCameraMaskLayer();
		void SetCameraMaskLayer(int nMaskLayer);
	protected:
		HrViewPortPtr m_pViewPort;
		HrCameraPtr m_pCamera;
	};

	class HR_CORE_API HrTrackBallCameraController : public HrSceneObjectComponent
	{
	public:
		HrTrackBallCameraController(const std::string& strName, HrSceneObject* pSceneObj);
		~HrTrackBallCameraController();

		virtual void OnEnter() override;

		void Move() {};
		void Rotate(const Vector3& v);
		void Forward(float fZ);
	protected:
		HrCameraComponentPtr m_pCameraCom;

		Vector3 m_vTarget;
		Vector3 m_vRight;

		float m_fRotationScaler;
		float m_fMoveScaler;
		float m_fZoomScaler;
	};

	class HR_CORE_API HrFirstPersonCameraController : public HrSceneObjectComponent
	{
	public:
		HrFirstPersonCameraController(const std::string& strName, HrSceneObject* pSceneObj);
		
		virtual bool Update(float fDelta) override;
	protected:
		void CreateInputEvent();

		void OnKeyPressed(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent);
		void OnKeyReleased(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent);

		void OnMousePressed(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent);
		void OnMouseReleased(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent);
		void OnMouseMove(const HrEventPtr& pEvent);
	protected:
		
		float m_fOldMouseX;
		float m_fOldMouseY;

		float m_fRotationY;


		float m_fForwardSpeed;

		bool m_bKeyAPressed;
		bool m_bKeyWPressed;
		bool m_bKeySPressed;
		bool m_bKeyDPressed;
	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////

	class HR_CORE_API HrLightComponent : public HrSceneObjectComponent
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

	class HR_CORE_API HrRenderableComponent : public HrSceneObjectComponent
	{
	public:
		HrRenderableComponent(const std::string& strName, HrSceneObject* pSceneObj);
		~HrRenderableComponent();

		void SetRenderable(const HrRenderablePtr& pRenderable);
		const HrRenderablePtr & GetRenderable() { return m_pRenderable; }

		void SetRenderEffect(const HrRenderEffectPtr& pRenderEffect);
	protected:
		HrRenderablePtr m_pRenderable;

		
	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////
	class HR_CORE_API HrInstanceBatchComponent : public HrSceneObjectComponent
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

	class HR_CORE_API HrInstanceObjectComponent : public HrSceneObjectComponent
	{
	public:
		HrInstanceObjectComponent(const std::string& strName, HrSceneObject* pSceneObj);
		~HrInstanceObjectComponent();

	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////

	class HR_CORE_API HrUICanvasComponent : public HrSceneObjectComponent
	{
	public:
		HrUICanvasComponent(const std::string& strName, HrSceneObject* pSceneObj);
		~HrUICanvasComponent();

		virtual void OnEnter() override;
	protected:
		HrCameraComponentPtr m_pCameraCom;
	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////

	class HR_CORE_API HrUIComponent : public HrSceneObjectComponent
	{
	public:
		HrUIComponent(const std::string& strName, HrSceneObject* pSceneObj);
		~HrUIComponent();

		void SetUI(const HrUIWidgetPtr& pUIWidget);
	
		const HrUIWidgetPtr& GetUIWidget() const;
	protected:
		HrUIWidgetPtr m_pUIWidget;
	};

	///////////////////////////////////////////////////
	//
	///////////////////////////////////////////////////
	class HrMeshModelSpherePTNUV;
	class HR_CORE_API HrSkyBoxComponent : public HrSceneObjectComponent
	{
	public:
		HrSkyBoxComponent(const std::string& strName, HrSceneObject* pSceneObj);

		void SetCubeMap(const HrTexturePtr& pCubeMap);
	protected:
		HrSkyBoxPtr m_pSkyBox;
		HrTexturePtr m_pCubeMap;

		std::shared_ptr<HrMeshModelSpherePTNUV> m_pMeshModelSphere;
		
	};
}

#endif


