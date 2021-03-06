#ifndef _HR_UITESTSCENE_H_
#define _HR_UITESTSCENE_H_

#include "HrEngine.h"

namespace Hr
{
	class HrUITestScene : public HrScene
	{
	public:
		HrUITestScene();
		~HrUITestScene();

		virtual void OnEnter() override;

		void MouseUpdate(float fDelta);
	protected:
		void CreateInputEvent();

		void OnKeyPressed(HrEventKeyboard::EnumKeyCode keyCode, HrEvent* pEvent);
		void OnKeyReleased(HrEventKeyboard::EnumKeyCode keyCode, HrEvent* pEvent);

		void OnMousePressed(HrEventMouse::EnumMouseButtonID mouseID, HrEvent* pEvent);
		void OnMouseReleased(HrEventMouse::EnumMouseButtonID mouseID, HrEvent* pEvent);
		void OnMouseMove(HrEvent* pEvent);

		void ResetKeyFlag();

	private:
		bool m_bKeyAPressed;
		bool m_bKeyWPressed;
		bool m_bKeySPressed;
		bool m_bKeyDPressed;

		bool m_bKey0Pressed;
		bool m_bKey1Pressed;
		bool m_bKeyF1Pressed;
		bool m_bKeyF2Pressed;

		bool m_bLeftMousePressed;
		bool m_bRightMousePressed;

		bool m_bKeyLeftPressed;
		bool m_bKeyRightPressed;
		bool m_bKeyUpPressed;
		bool m_bKeyDownPressed;

		bool m_bSphereDir;

		unsigned int m_nShiness;
	};
}


#endif


