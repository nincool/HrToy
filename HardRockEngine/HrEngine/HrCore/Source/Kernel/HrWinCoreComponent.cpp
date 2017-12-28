#include "Kernel/HrWinCoreComponent.h"
#include "Platform/AppWin32/HrWindowWin.h"
#include "Config/HrContextConfig.h"

using namespace Hr;

HrWinCoreComponent::HrWinCoreComponent()
{
	CreateAppWindow();
}

HrWinCoreComponent::~HrWinCoreComponent()
{

}

void HrWinCoreComponent::CreateAppWindow()
{
	uint32 nWidth = HrContextConfig::Instance()->GetWindowWidth();
	uint32 nHeight = HrContextConfig::Instance()->GetWindowHeight();

	m_pWindow = HrCheckPointerCast<HrWindow>(HrMakeSharedPtr<HrWindowWin>(nWidth, nHeight));
}

bool HrWinCoreComponent::Update(float fDelta)
{
	return true;
}

HWND HrWinCoreComponent::GetWindowHWnd()
{
	if (m_pWindow)
	{
		return m_pWindow->GetHWnd();
	}

	return 0;
}

uint32 HrWinCoreComponent::GetWindowWidth()
{
	if (m_pWindow)
	{
		return m_pWindow->GetWidth();
	}

	return 0;
}

uint32 HrWinCoreComponent::GetWindowHeight()
{
	if (m_pWindow)
	{
		return m_pWindow->GetHeight();
	}

	return 0;
}

void HrWinCoreComponent::DestroyWindow()
{
	if (m_pWindow)
	{
		m_pWindow->Destroy();
	}
}

void HrWinCoreComponent::UpdateWindowMsg()
{
	if (m_pWindow)
	{
		m_pWindow->UpdateMsg();
	}
}

