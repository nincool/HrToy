#include "AppWin32/HrApplication_Win32.h"
#include "HrLog.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrDirector.h"


using namespace Hr;

HrApplicationPtr HrApplication::m_s_pUniqueApplication;

HrApplicationPtr& HrApplication::GetInstance()
{
	if (!m_s_pUniqueApplication)
	{
		m_s_pUniqueApplication = MakeUniquePtr<HrApplication>();
	}
	return m_s_pUniqueApplication;
}

void HrApplication::ReleaseInstance()
{
	if (m_s_pUniqueApplication)
	{
		m_s_pUniqueApplication->Destroy();
	}
	m_s_pUniqueApplication.reset();
}

HrApplication::HrApplication()
{
}

HrApplication::~HrApplication()
{
	Destroy();
}

bool HrApplication::ApplicationDidFinishLaunching()
{
	return true;
}

void HrApplication::ApplicationDidEnterBackground()
{

}

void HrApplication::ApplicationWillEnterForeground()
{

}

void HrApplication::Run()
{
	HRLOG(_T("Application_win32 run"));
	HrDirector::GetInstance().Init();
	//if (!HrDirector::GetInstance()->Init())
	//{
	//	HRERROR(_T("HrApplication Run : HrDirector Init Error!"));
	//	HrDirector::GetInstance()->Release();
	//	return;
	//}
	//HrDirector::GetInstance()->StartMainLoop();
	//HrDirector::GetInstance()->Release();

}

bool HrApplication::Destroy()
{
	HrDirector::ReleaseInstance();
	HrLog::ReleaseInstance();
	return true;
}
