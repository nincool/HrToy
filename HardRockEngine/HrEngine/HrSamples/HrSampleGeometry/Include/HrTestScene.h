#ifndef _HR_TESTSCENE_H_
#define _HR_TESTSCENE_H_

#include "HrEngine.h"

namespace Hr
{
	class HrTestScene : public HrSceneImported
	{
	public:
		HrTestScene();
		~HrTestScene();

		virtual void OnEnter() override;

		void MouseUpdate(float fDelta);
	protected:
		virtual void CreateSceneFromData() override;
	
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



	};
}


#endif


