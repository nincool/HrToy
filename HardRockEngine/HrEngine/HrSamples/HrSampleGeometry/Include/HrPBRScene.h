#ifndef _HR_PBR_SCENE_H_
#define _HR_PBR_SCENE_H_

#include "HrEngine.h"

namespace Hr
{
	class HrPBRScene : public HrScene
	{
	public:
		HrPBRScene();
		~HrPBRScene();

		virtual void OnEnter() override;

		void SceneUpdate(float fDelta);
	private:
		void CreateSceneElements();

		void CreateInputEvent();

		void OnKeyPressed(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent);
		void OnKeyReleased(HrEventKeyboard::EnumKeyCode keyCode, const HrEventPtr& pEvent);

		void OnMousePressed(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent);
		void OnMouseReleased(HrEventMouse::EnumMouseButtonID mouseID, const HrEventPtr& pEvent);
		void OnMouseMove(const HrEventPtr& pEvent);

		void ResetKeyFlag();
	private:
		HrSceneNodePtr m_pSceneMainCamera;
		HrSceneNodePtr m_pModelNode;
		HrTrackBallCameraComponentPtr m_pTrackBallCameraCtrl;

		bool m_bKeyAPressed;
		bool m_bKeyWPressed;
		bool m_bKeySPressed;
		bool m_bKeyDPressed;

		bool m_bKey0Pressed;
		bool m_bKey1Pressed;

		bool m_bLeftMousePressed;
		bool m_bRightMousePressed;
	};
}

#endif


