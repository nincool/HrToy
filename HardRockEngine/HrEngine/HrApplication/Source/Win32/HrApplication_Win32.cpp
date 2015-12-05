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
	HrDirector::GetInstance()->Init();
	HrDirector::GetInstance()->StartMainLoop();
	HrDirector::GetInstance()->Release();
}

bool HrApplication::Destroy()
{
	HrDirector::ReleaseInstance();
	return true;
}

