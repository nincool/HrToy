#include "Config/HrContextConfig.h"

using namespace Hr;

HrContextConfig::HrContextConfig()
{
	m_nWindowWidth = 1200;
	m_nWindowHeight = 800;

	m_nRenderTargetViewWidth = 1200;
	m_nRenderTargetViewHeight = 800;
}

HrContextConfig::~HrContextConfig()
{

}

void HrContextConfig::SetWindowWidth(uint32 nWidth)
{
	m_nWindowWidth = nWidth;
}

void HrContextConfig::SetWindowHeight(uint32 nHeight)
{
	m_nWindowHeight = nHeight;
}

void HrContextConfig::SetRenderTargetViewWidth(uint32 nWidth)
{
	m_nRenderTargetViewWidth = nWidth;
}

void HrContextConfig::SetRenderTargetViewHeight(uint32 nHeight)
{
	m_nRenderTargetViewHeight = nHeight;
}

