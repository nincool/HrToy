#include "Kernel/HrCoreComponentWin.h"
#include "Platform/AppWin/HrWindowWin.h"
#include "Platform/AppWin/HrWrapperWin.h"
#include "Config/HrContextConfig.h"

using namespace Hr;

HrCoreComponentWin::HrCoreComponentWin()
{
	CreateAppWindow();
}

HrCoreComponentWin::HrCoreComponentWin(void* pWnd)
{
	if (pWnd)
		m_pWindow = HrMakeSharedPtr<HrWrapperWin>(static_cast<HWND>(pWnd));
	else
		CreateAppWindow();
}

HrCoreComponentWin::~HrCoreComponentWin()
{

}

void HrCoreComponentWin::CreateAppWindow()
{
	uint32 nWidth = HrContextConfig::Instance()->GetWindowWidth();
	uint32 nHeight = HrContextConfig::Instance()->GetWindowHeight();

	m_pWindow = HrCheckPointerCast<HrWindow>(HrMakeSharedPtr<HrWindowWin>(nWidth, nHeight));
}

bool HrCoreComponentWin::Update(float fDelta)
{
	return true;
}

HWND HrCoreComponentWin::GetWindowHWnd()
{
	if (m_pWindow)
	{
		return m_pWindow->GetHWnd();
	}

	return 0;
}

uint32 HrCoreComponentWin::GetWindowWidth()
{
	if (m_pWindow)
	{
		return m_pWindow->GetWidth();
	}

	return 0;
}

uint32 HrCoreComponentWin::GetWindowHeight()
{
	if (m_pWindow)
	{
		return m_pWindow->GetHeight();
	}

	return 0;
}

void HrCoreComponentWin::DestroyWindow()
{
	if (m_pWindow)
	{
		m_pWindow->Destroy();
	}
}

void HrCoreComponentWin::UpdateWindowMsg()
{
	if (m_pWindow)
	{
		m_pWindow->UpdateMsg();
	}
}

