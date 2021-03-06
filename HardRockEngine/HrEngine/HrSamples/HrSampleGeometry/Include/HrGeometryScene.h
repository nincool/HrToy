#ifndef _HR_GEOMETRYSCENE_H_
#define _HR_GEOMETRYSCENE_H_

#include "HrEngine.h"

namespace Hr
{
	class HrGeometryScene : public HrScene
	{
	public:
		HrGeometryScene();
		~HrGeometryScene();

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
		HrSceneNodePtr m_pTestNode;

		bool m_bKeyAPressed;
		bool m_bKeyWPressed;
		bool m_bKeySPressed;
		bool m_bKeyDPressed;

		bool m_bKey0Pressed;
		bool m_bKey1Pressed;

	};
}

#endif


