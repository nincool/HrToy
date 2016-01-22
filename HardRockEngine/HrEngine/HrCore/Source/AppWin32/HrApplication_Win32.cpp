#include "AppWin32/HrApplication_Win32.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrApplicationPtr HrApplication::m_pUniqueApplication;

HrApplicationPtr& HrApplication::GetInstance()
{
	if (!m_pUniqueApplication)
	{
		m_pUniqueApplication = MakeUniquePtr<HrApplication>();
	}
	return m_pUniqueApplication;
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
	//HrDirector::ReleaseInstance();
	return true;
}
