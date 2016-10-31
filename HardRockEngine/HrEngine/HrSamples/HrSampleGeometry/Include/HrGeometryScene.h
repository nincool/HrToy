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

		void MouseUpdate(float fDelta);
	private:
		void CreateSceneElements();

		void CreateInputEvent();

		void OnKeyPressed(HrEventKeyboard::EnumKeyCode keyCode, HrEvent* pEvent);
		void OnKeyReleased(HrEventKeyboard::EnumKeyCode keyCode, HrEvent* pEvent);

		void ResetKeyFlag();
	private:
		HrCameraNode* m_pSceneMainCamera;

		bool m_bKeyAPressed;
		bool m_bKeyWPressed;
		bool m_bKeySPressed;
		bool m_bKeyDPressed;
	};
}

#endif


