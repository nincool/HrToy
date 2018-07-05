#pragma once

#include "HrEngine.h"

namespace Hr
{
	class HrRenderQueue : public HrScene
	{
	public:
		HrRenderQueue();
		~HrRenderQueue();

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
		HrSceneNodePtr m_pTestRoot;
		HrSceneNodePtr m_pPlane;
		HrSceneNodePtr m_pBox;

		HrSceneNodePtr m_pPointLight1;
		HrSceneNodePtr m_pPointLight2;
		HrSceneNodePtr m_pPointLight3;
		HrSceneNodePtr m_pPointLight4;

		bool m_bKeyAPressed;
		bool m_bKeyWPressed;
		bool m_bKeySPressed;
		bool m_bKeyDPressed;

		bool m_bKey0Pressed;
		bool m_bKey1Pressed;

		bool m_bLeftMousePressed;
		bool m_bRightMousePressed;

		bool m_bMoving;
	};
}



