#include "HrGeometryApp.h"

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



HrGeometryApp::HrGeometryApp()
{

}

HrGeometryApp::~HrGeometryApp()
{

}

bool HrGeometryApp::ApplicationDidFinishLaunching()
{
	return true;
}

void HrGeometryApp::ApplicationDidEnterBackground()
{

}

void HrGeometryApp::ApplicationWillEnterForeground()
{

}

void HrGeometryApp::Run()
{
	HRLOG(_T("HrGeometryApp_win32 run"));
	if (!HrDirector::GetInstance().Init())
	{
		HRERROR(_T("HrGeometryApp Run Error!"));
	}

	ApplicationDidFinishLaunching();

	OnEnter();
}

bool HrGeometryApp::Destroy()
{
	bool bRet = HrApplication::Destroy();

	return bRet;
}

void HrGeometryApp::OnEnter()
{
	LoadAssets();
}

void HrGeometryApp::LoadAssets()
{

}
