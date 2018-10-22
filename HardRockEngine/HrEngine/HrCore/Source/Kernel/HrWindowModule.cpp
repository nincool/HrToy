#include "Kernel/HrWindowModule.h"
#include "Platform/AppWin/HrWindowWin.h"
#include "Platform/AppWin/HrWrapperWin.h"
#include "Config/HrContextConfig.h"
#include "HrMath/Include/HrRect.h"

using namespace Hr;

HrWindowModule::HrWindowModule()
{
	CreateAppWindow();
}

HrWindowModule::HrWindowModule(void* pWnd)
{
	if (pWnd)
		m_pWindow = HrMakeSharedPtr<HrWrapperWin>(static_cast<HWND>(pWnd));
	else
		CreateAppWindow();
}

HrWindowModule::~HrWindowModule()
{

}

void HrWindowModule::CreateAppWindow()
{
	uint32 nWidth = HrContextConfig::Instance()->GetWindowWidth();
	uint32 nHeight = HrContextConfig::Instance()->GetWindowHeight();

	m_pWindow = HrCheckPointerCast<HrWindow>(HrMakeSharedPtr<HrWindowWin>(nWidth, nHeight));
}

bool HrWindowModule::Update(float fDelta)
{
	return true;
}

HWND HrWindowModule::GetWindowHWnd()
{
	if (m_pWindow)
	{
		return m_pWindow->GetHWnd();
	}

	return 0;
}

uint32 HrWindowModule::GetWindowX()
{
	if(m_pWindow)
	{
		return m_pWindow->GetTopX();
	}
}

uint32 HrWindowModule::GetWindowY()
{
	if (m_pWindow)
	{
		return m_pWindow->GetTopY();
	}
}

uint32 HrWindowModule::GetWindowWidth()
{
	if (m_pWindow)
	{
		return m_pWindow->GetWidth();
	}

	return 0;
}

uint32 HrWindowModule::GetWindowHeight()
{
	if (m_pWindow)
	{
		return m_pWindow->GetHeight();
	}

	return 0;
}

void HrWindowModule::DestroyWindow()
{
	if (m_pWindow)
	{
		m_pWindow->Destroy();
	}
}

void HrWindowModule::UpdateWindowMsg()
{
	if (m_pWindow)
	{
		m_pWindow->UpdateMsg();
	}
}








