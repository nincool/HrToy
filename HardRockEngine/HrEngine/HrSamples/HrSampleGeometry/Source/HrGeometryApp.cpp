#include "HrGeometryApp.h"
#include "HrGeometryScene.h"

using namespace Hr;

HrGeometryAppPtr HrGeometryApp::m_s_pUniqueGeometryApp;

HrGeometryApp& Hr::HrGeometryApp::GetInstance()
{
	if (!m_s_pUniqueGeometryApp)
	{
		m_s_pUniqueGeometryApp = MakeUniquePtr<HrGeometryApp>();
	}

	return *m_s_pUniqueGeometryApp;
}

void HrGeometryApp::ReleaseInstance()
{
	if (m_s_pUniqueGeometryApp)
	{
		m_s_pUniqueGeometryApp->Destroy();
	}
	m_s_pUniqueGeometryApp.reset();
}

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
	bool bRet = HrApplication::Destroy();

	return bRet;
}

void HrGeometryApp::LoadAssets()
{

}

void HrGeometryApp::CreateScene()
{
	std::shared_ptr<HrGeometryScene> pGeometryScene = MakeSharedPtr<HrGeometryScene>();
	HrDirector::GetInstance().RunScene(pGeometryScene);
}

