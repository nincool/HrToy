#include "HrGeometryApp.h"
#include "HrGeometryScene.h"

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

