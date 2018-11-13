#pragma once

#include "HrCore/Include/Platform/AppWin/HrAppWindows.h"
#include "HrEngine.h"
#include "HrCommon/include/HrSingleton.h"
#include "HrConvertUtil.h"

namespace Hr
{
	class HrRenderAxis : public HrMeshModel
	{
	public:
		HrRenderAxis();
		~HrRenderAxis();



	protected:
		struct SAxisVertex
		{
			float3 position;
			float4 color;
			SAxisVertex()
			{
				position = Vector3::Zero();
				color = Vector4::Zero();
			}
		};
	private:
		void CreateAxisMesh();
	};

	class HrEditorScene : public HrScene
	{
	public:
		HrEditorScene();
		~HrEditorScene();

		virtual void OnEnter() override;

		virtual void Update(float fDelta) override;

		void OnMouseMove(float fX, float fY);
		void OnRMouseButtonDown(float fX, float fY);
		void OnRMouseButtonUp(float fX, float fY);
		void OnMouseWheel(float fDelta);

		const HrModelDataInfo& LoadOriginalMeshData(const std::string& strFileName);
		void SaveConvertMeshData(const std::string& strFileName);

		std::shared_ptr<HrConvertUtil> GetConvertUtil()
		{
			return m_pConvertUtil;
		}
	private:
		void CreateSceneElements();
		void CreateAxisNode();

		float Convert2ProjPosX(float fX);
		float Convert2ProjPosY(float fY);

		float Convert2ScreenPosX(float fX);
		float Convert2ScreenPosY(float fY);

		void UpdateAxisPos();
	private:
		float m_fFrameWidth;
		float m_fFrameHeight;

		bool m_bRButtonDown;

		std::shared_ptr<HrConvertUtil> m_pConvertUtil;

		HrSceneNodePtr m_pGodCamera;
		HrCameraComponentPtr m_pCameraCom;
		HrTrackBallCameraComponentPtr m_pTrackBallCameraCtrl;
		HrSceneNodePtr m_pEleRoot;

		std::shared_ptr<HrRenderAxis> m_pAxisModel;

		HrSceneNodePtr m_pPlane;
		HrSceneNodePtr m_pAxisNode;
		HrSceneNodePtr m_pModel;

		HrSceneNodePtr m_pPointLight1;
		HrSceneNodePtr m_pPointLight2;
		HrSceneNodePtr m_pPointLight3;
		HrSceneNodePtr m_pPointLight4;

		float m_fOldMouseX = 0;
		float m_fOldMouseY = 0;

		bool m_bCameraMatrixDirty;
	};

	class HrRenderApp : public HrAppWindows
	{
	public:
		HrRenderApp(HWND hWnd);
		~HrRenderApp();

		virtual bool ApplicationDidFinishLaunching() override;

		virtual void ApplicationDidEnterBackground() override;

		virtual void ApplicationWillEnterForeground() override;

		virtual bool Destroy() override;

		virtual void Run() override;

		void RenderOnce();

		const HrModelDataInfo& LoadOriginalMeshData(const std::string& strFileName);
		void SaveConvertMeshData(const std::string& strFileName);

		void OnMouseMove(float fX, float fY);
		void OnRMouseButtonDown(float fX, float fY);
		void OnRMouseButtonUp(float fX, float fY);
		void OnMouseWheel(float fDelta);

		std::shared_ptr<HrEditorScene> GetEditorScene()
		{
			return m_pEditorScene;
		}
	private:
		void LoadAssets();
		void CreateScene();

	private:
		HWND m_hWnd;
		HrRect m_displayRect;

		std::shared_ptr<HrEditorScene> m_pEditorScene;
	};


}

