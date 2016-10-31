#include "Platform/AppWin32/HrApplicationWin.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrLog.h"

using namespace Hr;

HrApplicationWin::HrApplicationWin()
{
}

HrApplicationWin::~HrApplicationWin()
{
	Destroy();
}

bool HrApplicationWin::ApplicationDidFinishLaunching()
{
	return true;
}

void HrApplicationWin::ApplicationDidEnterBackground()
{

}

void HrApplicationWin::ApplicationWillEnterForeground()
{

}

void HrApplicationWin::Run()
{
	HRLOG(_T("Application_win32 run"));
	
	if (!HrDirector::Instance()->Init())
	{
		HRERROR(_T("Application Run Error!"));
	}
	else
	{
		ApplicationDidFinishLaunching();

		HrDirector::Instance()->StartMainLoop();
	}
}

bool HrApplicationWin::Destroy()
{
	HrDirector::Instance()->Release();
	HrLog::Instance()->Release();
	
	return true;
}
