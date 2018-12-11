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

	class HrModelDataPropertiesInfo
	{
	public:
		HrModelDataPropertiesInfo() : m_pModelDataInfo(nullptr), m_pSceneNode(nullptr)
		{}
		HrModelDataPropertiesInfo(const HrModelDataInfo* pModelDataInfo, const HrSceneNode* pSceneNode)
		{
			m_pModelDataInfo = const_cast<HrModelDataInfo*>(pModelDataInfo);
			m_pSceneNode = const_cast<HrSceneNode*>(pSceneNode);
		}

		HrModelDataInfo* m_pModelDataInfo;
		HrSceneNode* m_pSceneNode;
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

		void LoadOriginalMeshData(const std::string& strFileName);
		void SaveConvertMeshData(const std::string& strFileName);

		void LoadPrefabData(const std::string& strFileName);

		void SavePrefabData(const std::string& strFileName);

		const std::vector<HrSceneNodePtr>& GetModelNodes();
		const std::vector<HrModelDataPropertiesInfo>& GetModelDataInfos();
	private:
		void CreateSceneElements();
		void CreateAxisNode();

		float Convert2ProjPosX(float fX);
		float Convert2ProjPosY(float fY);

		float Convert2ScreenPosX(float fX);
		float Convert2ScreenPosY(float fY);

		void UpdateAxisPos();

		void WritePrefabModelInfo(rapidjson::Document& doc);

		std::string FormatJsonData(const std::string& strContent);
		void FlushDataToFile(const std::string& strOutputFile, rapidjson::Document& doc);

		std::string MakeFloat3StringWithEndMark(const float3& v);
		std::string MakeFloat3String(const float3& v);
	private:
		float m_fFrameWidth;
		float m_fFrameHeight;

		bool m_bRButtonDown;

		HrSceneNodePtr m_pModelRoot;
		std::vector<HrSceneNodePtr> m_vecModelNodes;
		std::vector<HrModelDataPropertiesInfo> m_vecModelDataInfos;

		HrSceneNodePtr m_pGodCamera;
		HrCameraComponentPtr m_pCameraCom;
		HrTrackBallCameraComponentPtr m_pTrackBallCameraCtrl;
		HrSceneNodePtr m_pEleRoot;

		std::shared_ptr<HrRenderAxis> m_pAxisModel;

		HrSceneNodePtr m_pPlane;
		HrSceneNodePtr m_pAxisNode;

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

		void LoadOriginalMeshData(const std::string& strFileName);
		void SaveTextFile(const std::string& strFileName);

		void LoadPrefabData(const std::string& strFileName);

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

