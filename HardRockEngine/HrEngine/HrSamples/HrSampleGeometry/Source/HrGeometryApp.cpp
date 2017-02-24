#include "HrGeometryApp.h"
#include "HrGeometryScene.h"
#include "HrTestScene.h"
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
	std::shared_ptr<HrGeometryScene> pTestScene = MakeSharedPtr<HrGeometryScene>();
	HrDirector::Instance()->RunScene(pTestScene);

	//std::shared_ptr<HrTestScene> pTestScene = MakeSharedPtr<HrTestScene>();
	//pTestScene->LoadScene("HrTestScene.json");
	//HrDirector::Instance()->RunScene(pTestScene);
}
