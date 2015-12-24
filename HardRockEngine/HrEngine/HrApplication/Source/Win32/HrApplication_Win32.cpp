#include "Win32/HrApplication_Win32.h"
#include "HrMain/Include/HrDirector.h"

using namespace Hr;

HR_INSTANCE_DEF(HrApplication);

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
	if (!HrDirector::GetInstance()->Init())
	{
		HRERROR(_T("HrApplication Run : HrDirector Init Error!"));
		return;
	}
	HrDirector::GetInstance()->StartMainLoop();
	HrDirector::GetInstance()->Release();
}

bool HrApplication::Destroy()
{
	HrDirector::ReleaseInstance();
	return true;
}


