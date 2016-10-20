#include "HrGeometryApp.h"
#include "HrGeometryScene.h"
#include <sstream>
#include "HrEngine.h"

using namespace Hr;

HrGeometryApp::HrGeometryApp()
{
}

HrGeometryApp::~HrGeometryApp()
{
}

bool HrGeometryApp::ApplicationDidFinishLaunching()
{
	LoadAssets();
	
	CreateScene();

	CreateInputEvent();

	return true;
}

void HrGeometryApp::ApplicationDidEnterBackground()
{
}

void HrGeometryApp::ApplicationWillEnterForeground()
{
}

bool HrGeometryApp::Destroy()
{
	bool bRet = HrApplicationWin::Destroy();

	return bRet;
}

void HrGeometryApp::LoadAssets()
{
}

void HrGeometryApp::CreateScene()
{
	std::shared_ptr<HrGeometryScene> pGeometryScene = MakeSharedPtr<HrGeometryScene>();
	HrDirector::Instance()->RunScene(pGeometryScene);
}

void HrGeometryApp::CreateInputEvent()
{
	HrEventListenerKeyboardPtr pEventListenerKeyboard = MakeSharedPtr<HrEventListenerKeyboard>([](HrEventKeyboard::EnumKeyCode keyCode, HrEvent* pEvent) {
		std::cout << " Key Pressed!!!!! Key Code:" << (int)keyCode << std::endl;
	}, [](HrEventKeyboard::EnumKeyCode keyCode, HrEvent* pEvent) {
		std::cout << " Key Released!!!!! Key code:" << (int)keyCode << std::endl;
	});
	HrEventDispatcher::Instance()->AddEventListener(CheckPointerCast<HrEventListener>(pEventListenerKeyboard));
}

