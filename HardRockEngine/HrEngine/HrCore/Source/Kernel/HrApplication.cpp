#include "Kernel/HrApplication.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrLog.h"

using namespace Hr;

HrApplication::HrApplication()
{

}

HrApplication::~HrApplication()
{
}

void HrApplication::Run()
{
	HRLOG(_T("Application_win32 run"));

	if (!HrDirector::Instance()->Init(nullptr))
	{
		HRERROR(_T("Application Run Error!"));
	}
	else
	{
		ApplicationDidFinishLaunching();

		HrDirector::Instance()->StartMainLoop();
	}
}

bool HrApplication::Destroy()
{
	HrDirector::Instance()->Destroy();

	return true;
}
