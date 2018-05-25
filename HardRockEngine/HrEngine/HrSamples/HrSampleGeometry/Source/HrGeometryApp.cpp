#include "HrGeometryApp.h"
#include "HrGeometryScene.h"
#include "HrInstanceBatchTest.h"
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
	bool bRet = HrAppWindows::Destroy();

	return bRet;
}

void HrGeometryApp::LoadAssets()
{
}

void HrGeometryApp::CreateScene()
{
	//auto pTestScene = HrMakeSharedPtr<HrInstanceBatchTest>();
	auto pTestScene = HrMakeSharedPtr<HrGeometryScene>();
	HrDirector::Instance()->GetSceneCoreComponent()->RunScene(pTestScene);

	//std::shared_ptr<HrTestScene> pTestScene = HrMakeSharedPtr<HrTestScene>();
	//pTestScene->LoadScene("PlayerScene.json");
	//HrDirector::Instance()->RunScene(pTestScene);
}
