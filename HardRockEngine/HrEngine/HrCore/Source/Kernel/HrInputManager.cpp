#include "Kernel/HrInputManager.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrCoreComponentEvent.h"
#include "Kernel/HrCoreComponentWin.h"
#include "Event/HrEvent.h"
#include "Event/HrEventDispatcher.h"
#include "HrUtilTools/Include/HrUtil.h"
using namespace Hr;


bool HrInputEventListener::keyPressed(const OIS::KeyEvent &arg)
{
	HrEventKeyboard::EnumKeyCode keyCode = GetKeyCodeMap(arg.key);

	HrEventPtr pEvent = HrMakeSharedPtr<HrEventKeyboard>(keyCode, true);
	HrDirector::Instance()->GetEventComponent()->DispatcherEvent(pEvent);
	
	return true;
}

bool HrInputEventListener::keyReleased(const OIS::KeyEvent &arg)
{
	HrEventKeyboard::EnumKeyCode keyCode = GetKeyCodeMap(arg.key);

	HrEventPtr pEvent = HrMakeSharedPtr<HrEventKeyboard>(keyCode, false);
	HrDirector::Instance()->GetEventComponent()->DispatcherEvent(pEvent);

	return true;
}

bool HrInputEventListener::mouseMoved(const OIS::MouseEvent &arg)
{
	float x, y, z;
	HrInputManager::Instance()->GetCursorPosition(x, y);
	HrInputManager::Instance()->GetMouseWheelSlidingDistance(z);
	HrEventPtr pEvent = HrMakeSharedPtr<HrEventMouse>(HrEventMouse::EnumMouseButtonID::MBI_UNKNOW, HrEventMouse::EnumMouseEventFlag::MEF_MOVE, x, y, z);
	HrDirector::Instance()->GetEventComponent()->DispatcherEvent(pEvent);

	return true;
}

bool HrInputEventListener::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	HrEventMouse::EnumMouseButtonID mouseID = GetMouseButtonMap(id);
	float x, y;
	HrInputManager::Instance()->GetCursorPosition(x, y);
	//HrEventMouse event(mouseID, HrEventMouse::EnumMouseEventFlag::MEF_PRESSED, x, y);
	//HrEventDispatcher::Instance()->DispatcherEvent(&event);
	return true;
}

bool HrInputEventListener::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	HrEventMouse::EnumMouseButtonID mouseID = GetMouseButtonMap(id);
	float x, y;
	HrInputManager::Instance()->GetCursorPosition(x, y);
	//HrEventMouse event(mouseID, HrEventMouse::EnumMouseEventFlag::MEF_RELEASED, x, y);
	//HrEventDispatcher::Instance()->DispatcherEvent(&event);
	return true;
}

HrEventKeyboard::EnumKeyCode HrInputEventListener::GetKeyCodeMap(OIS::KeyCode keyCode)
{
	switch (keyCode)
	{
	case OIS::KC_UNASSIGNED:
		return HrEventKeyboard::EnumKeyCode::KEY_NONE;
	case OIS::KC_ESCAPE:
		return HrEventKeyboard::EnumKeyCode::KEY_ESCAPE;
	case OIS::KC_1:
		return HrEventKeyboard::EnumKeyCode::KEY_1;
	case OIS::KC_2:
		return HrEventKeyboard::EnumKeyCode::KEY_2;
	case OIS::KC_3:
		return HrEventKeyboard::EnumKeyCode::KEY_3;
	case OIS::KC_4:
		return HrEventKeyboard::EnumKeyCode::KEY_4;
	case OIS::KC_5:
		return HrEventKeyboard::EnumKeyCode::KEY_5;
	case OIS::KC_6:
		return HrEventKeyboard::EnumKeyCode::KEY_6;
	case OIS::KC_7:
		return HrEventKeyboard::EnumKeyCode::KEY_7;
	case OIS::KC_8:
		return HrEventKeyboard::EnumKeyCode::KEY_8;
	case OIS::KC_9:
		return HrEventKeyboard::EnumKeyCode::KEY_9;
	case OIS::KC_0:
		return HrEventKeyboard::EnumKeyCode::KEY_0;
	case OIS::KC_MINUS:
		return HrEventKeyboard::EnumKeyCode::KEY_MINUS;
	case OIS::KC_EQUALS:
		return HrEventKeyboard::EnumKeyCode::KEY_EQUAL;
	case OIS::KC_BACK:
		return HrEventKeyboard::EnumKeyCode::KEY_BACK;
	case OIS::KC_TAB:
		return HrEventKeyboard::EnumKeyCode::KEY_TAB;
	case OIS::KC_Q:
		return HrEventKeyboard::EnumKeyCode::KEY_Q;
	case OIS::KC_W:
		return HrEventKeyboard::EnumKeyCode::KEY_W;
	case OIS::KC_E:
		return HrEventKeyboard::EnumKeyCode::KEY_E;
	case OIS::KC_R:
		return HrEventKeyboard::EnumKeyCode::KEY_R;
	case OIS::KC_T:
		return HrEventKeyboard::EnumKeyCode::KEY_T;
	case OIS::KC_Y:
		return HrEventKeyboard::EnumKeyCode::KEY_Y;
	case OIS::KC_U:
		return HrEventKeyboard::EnumKeyCode::KEY_U;
	case OIS::KC_I:
		return HrEventKeyboard::EnumKeyCode::KEY_I;
	case OIS::KC_O:
		return HrEventKeyboard::EnumKeyCode::KEY_O;
	case OIS::KC_P:
		return HrEventKeyboard::EnumKeyCode::KEY_P;
	case OIS::KC_LBRACKET:
		break;
	case OIS::KC_RBRACKET:
		break;
	case OIS::KC_RETURN:
		break;
	case OIS::KC_LCONTROL:
		break;
	case OIS::KC_A:
		return HrEventKeyboard::EnumKeyCode::KEY_A;
	case OIS::KC_S:
		return HrEventKeyboard::EnumKeyCode::KEY_S;
	case OIS::KC_D:
		return HrEventKeyboard::EnumKeyCode::KEY_D;
	case OIS::KC_F:
		return HrEventKeyboard::EnumKeyCode::KEY_F;
	case OIS::KC_G:
		return HrEventKeyboard::EnumKeyCode::KEY_G;
	case OIS::KC_H:
		return HrEventKeyboard::EnumKeyCode::KEY_H;
	case OIS::KC_J:
		return HrEventKeyboard::EnumKeyCode::KEY_J;
	case OIS::KC_K:
		return HrEventKeyboard::EnumKeyCode::KEY_K;
	case OIS::KC_L:
		return HrEventKeyboard::EnumKeyCode::KEY_L;
	case OIS::KC_SEMICOLON:
		break;
	case OIS::KC_APOSTROPHE:
		break;
	case OIS::KC_GRAVE:
		break;
	case OIS::KC_LSHIFT:
		break;
	case OIS::KC_BACKSLASH:
		break;
	case OIS::KC_Z:
		return HrEventKeyboard::EnumKeyCode::KEY_Z;
	case OIS::KC_X:
		return HrEventKeyboard::EnumKeyCode::KEY_X;
	case OIS::KC_C:
		return HrEventKeyboard::EnumKeyCode::KEY_C;
	case OIS::KC_V:
		return HrEventKeyboard::EnumKeyCode::KEY_V;
	case OIS::KC_B:
		return HrEventKeyboard::EnumKeyCode::KEY_B;
	case OIS::KC_N:
		break;
	case OIS::KC_M:
		return HrEventKeyboard::EnumKeyCode::KEY_M;
	case OIS::KC_COMMA:
		break;
	case OIS::KC_PERIOD:
		break;
	case OIS::KC_SLASH:
		break;
	case OIS::KC_RSHIFT:
		break;
	case OIS::KC_MULTIPLY:
		break;
	case OIS::KC_LMENU:
		break;
	case OIS::KC_SPACE:
		break;
	case OIS::KC_CAPITAL:
		break;
	case OIS::KC_F1:
		return HrEventKeyboard::EnumKeyCode::KEY_F1;
	case OIS::KC_F2:
		return HrEventKeyboard::EnumKeyCode::KEY_F2;
	case OIS::KC_F3:
		return HrEventKeyboard::EnumKeyCode::KEY_F3;
	case OIS::KC_F4:
		return HrEventKeyboard::EnumKeyCode::KEY_F4;
	case OIS::KC_F5:
		return HrEventKeyboard::EnumKeyCode::KEY_F5;
	case OIS::KC_F6:
		return HrEventKeyboard::EnumKeyCode::KEY_F6;
	case OIS::KC_F7:
		return HrEventKeyboard::EnumKeyCode::KEY_F7;
	case OIS::KC_F8:
		return HrEventKeyboard::EnumKeyCode::KEY_F8;
	case OIS::KC_F9:
		return HrEventKeyboard::EnumKeyCode::KEY_F9;
	case OIS::KC_F10:
		return HrEventKeyboard::EnumKeyCode::KEY_F10;
	case OIS::KC_NUMLOCK:
		break;
	case OIS::KC_SCROLL:
		break;
	case OIS::KC_NUMPAD7:
		break;
	case OIS::KC_NUMPAD8:
		break;
	case OIS::KC_NUMPAD9:
		break;
	case OIS::KC_SUBTRACT:
		break;
	case OIS::KC_NUMPAD4:
		break;
	case OIS::KC_NUMPAD5:
		break;
	case OIS::KC_NUMPAD6:
		break;
	case OIS::KC_ADD:
		break;
	case OIS::KC_NUMPAD1:
		break;
	case OIS::KC_NUMPAD2:
		break;
	case OIS::KC_NUMPAD3:
		break;
	case OIS::KC_NUMPAD0:
		break;
	case OIS::KC_DECIMAL:
		break;
	case OIS::KC_OEM_102:
		break;
	case OIS::KC_F11:
		break;
	case OIS::KC_F12:
		break;
	case OIS::KC_F13:
		break;
	case OIS::KC_F14:
		break;
	case OIS::KC_F15:
		break;
	case OIS::KC_KANA:
		break;
	case OIS::KC_ABNT_C1:
		break;
	case OIS::KC_CONVERT:
		break;
	case OIS::KC_NOCONVERT:
		break;
	case OIS::KC_YEN:
		break;
	case OIS::KC_ABNT_C2:
		break;
	case OIS::KC_NUMPADEQUALS:
		break;
	case OIS::KC_PREVTRACK:
		break;
	case OIS::KC_AT:
		break;
	case OIS::KC_COLON:
		break;
	case OIS::KC_UNDERLINE:
		break;
	case OIS::KC_KANJI:
		break;
	case OIS::KC_STOP:
		break;
	case OIS::KC_AX:
		break;
	case OIS::KC_UNLABELED:
		break;
	case OIS::KC_NEXTTRACK:
		break;
	case OIS::KC_NUMPADENTER:
		break;
	case OIS::KC_RCONTROL:
		break;
	case OIS::KC_MUTE:
		break;
	case OIS::KC_CALCULATOR:
		break;
	case OIS::KC_PLAYPAUSE:
		break;
	case OIS::KC_MEDIASTOP:
		break;
	case OIS::KC_VOLUMEDOWN:
		break;
	case OIS::KC_VOLUMEUP:
		break;
	case OIS::KC_WEBHOME:
		break;
	case OIS::KC_NUMPADCOMMA:
		break;
	case OIS::KC_DIVIDE:
		break;
	case OIS::KC_SYSRQ:
		break;
	case OIS::KC_RMENU:
		break;
	case OIS::KC_PAUSE:
		break;
	case OIS::KC_HOME:
		break;
	case OIS::KC_UP:
		return HrEventKeyboard::EnumKeyCode::KEY_KP_UP;
	case OIS::KC_PGUP:
		break;
	case OIS::KC_LEFT:
		return HrEventKeyboard::EnumKeyCode::KEY_KP_LEFT;
	case OIS::KC_RIGHT:
		return HrEventKeyboard::EnumKeyCode::KEY_KP_RIGHT;
	case OIS::KC_END:
		break;
	case OIS::KC_DOWN:
		return HrEventKeyboard::EnumKeyCode::KEY_KP_DOWN;
	case OIS::KC_PGDOWN:
		break;
	case OIS::KC_INSERT:
		break;
	case OIS::KC_DELETE:
		break;
	case OIS::KC_LWIN:
		break;
	case OIS::KC_RWIN:
		break;
	case OIS::KC_APPS:
		break;
	case OIS::KC_POWER:
		break;
	case OIS::KC_SLEEP:
		break;
	case OIS::KC_WAKE:
		break;
	case OIS::KC_WEBSEARCH:
		break;
	case OIS::KC_WEBFAVORITES:
		break;
	case OIS::KC_WEBREFRESH:
		break;
	case OIS::KC_WEBSTOP:
		break;
	case OIS::KC_WEBFORWARD:
		break;
	case OIS::KC_WEBBACK:
		break;
	case OIS::KC_MYCOMPUTER:
		break;
	case OIS::KC_MAIL:
		break;
	case OIS::KC_MEDIASELECT:
		break;
	default:
		break;
	}
	return HrEventKeyboard::EnumKeyCode::KEY_0;
}

HrEventMouse::EnumMouseButtonID HrInputEventListener::GetMouseButtonMap(OIS::MouseButtonID mouseID)
{
	switch (mouseID)
	{
	case OIS::MB_Left:
		return HrEventMouse::EnumMouseButtonID::MBI_LEFT;
	case OIS::MB_Right:
		return HrEventMouse::EnumMouseButtonID::MBI_RIGHT;
	case OIS::MB_Middle:
		return HrEventMouse::EnumMouseButtonID::MBI_MIDDLE;
	case OIS::MB_Button3:
		return HrEventMouse::EnumMouseButtonID::MBI_BUTTON3;
	case OIS::MB_Button4:
		return HrEventMouse::EnumMouseButtonID::MBI_BUTTON4;
	case OIS::MB_Button5:
		return HrEventMouse::EnumMouseButtonID::MBI_BUTTON5;
	case OIS::MB_Button6:
		return HrEventMouse::EnumMouseButtonID::MBI_BUTTON6;
	case OIS::MB_Button7:
		return HrEventMouse::EnumMouseButtonID::MBI_BUTTON7;
	default:
		break;
	}
	return HrEventMouse::EnumMouseButtonID::MBI_LEFT;
}

///////////////////////////////////////////////////////////////
//CreateInputSystem
///////////////////////////////////////////////////////////////

void HrInputManager::CreateInputSystem()
{
	OIS::ParamList pl;
	size_t winHandle = 0;
	std::ostringstream winHandleStr;

	const HrCoreComponentWinPtr& pWindowComponet = HrDirector::Instance()->GetWinCoreComponent();
	size_t nWinHandle = (size_t)(pWindowComponet->GetWindowHWnd());
	winHandleStr << nWinHandle;

	pl.insert(std::make_pair("WINDOW", winHandleStr.str()));
	if (true)
	{
		pl.insert(std::make_pair("w32_mouse", "DISCL_FOREGROUND"));
		pl.insert(std::make_pair("w32_mouse", "DISCL_NONEXCLUSIVE"));
		pl.insert(std::make_pair("w32_keyboard", "DISCL_FOREGROUND"));
		pl.insert(std::make_pair("w32_keyboard", "DISCL_NONEXCLUSIVE"));
	}

	m_pInputManager = OIS::InputManager::createInputSystem(pl);
	mKeyboard = static_cast<OIS::Keyboard*>(m_pInputManager->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(m_pInputManager->createInputObject(OIS::OISMouse, true));

	mMouse->getMouseState().width = pWindowComponet->GetWindowWidth();
	mMouse->getMouseState().height = pWindowComponet->GetWindowHeight();
	
	mKeyboard->setEventCallback(&m_inputEventListener);
	mMouse->setEventCallback(&m_inputEventListener);
}
