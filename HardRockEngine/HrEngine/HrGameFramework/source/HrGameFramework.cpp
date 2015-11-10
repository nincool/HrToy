#include "HrGameFramework.h"
#include "HrSystemCenter/Include/HrDirector.h"

using namespace Hr;

HrGameFramework* HrGameFramework::m_s_pInstance = nullptr;

HrGameFramework::HrGameFramework()
{
	m_hHandleSystemCenter = nullptr;
	m_pDirector = nullptr;
}

HrGameFramework::~HrGameFramework()
{
}

bool HrGameFramework::Init()
{
	bool bFrameworkInitSuccess = true;

	typedef IDirector*(*SYSTEM_CENTER_STARTCALL)();
	TCHAR finalModuleName[MAX_PATH] = HR_PREFIX;
	_tcscat(finalModuleName, "HrSystemCenter");
	_tcscat(finalModuleName, HR_SUFFIX);

	m_hHandleSystemCenter = HR_MODULE_OPEN(finalModuleName);
	if (m_hHandleSystemCenter != nullptr)
	{
		SYSTEM_CENTER_STARTCALL pFuncStart = (SYSTEM_CENTER_STARTCALL)HR_MODULE_GETSYSTEM(m_hHandleSystemCenter, HR_MODULE_START_FUNC);
		m_pDirector = pFuncStart();
	}
	else
	{
		bFrameworkInitSuccess = false;
	}

	if (m_pDirector != nullptr)
	{
		m_pDirector->Init();
	}
	else
	{
		bFrameworkInitSuccess = false;
	}

	if (bFrameworkInitSuccess)
	{
		this->Run();
	}

	return bFrameworkInitSuccess;
}

void HrGameFramework::Run()
{
	m_pDirector->Go();
}



