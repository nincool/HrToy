#include "Render/HrRenderFrame.h"

using namespace Hr;

HrRenderFrame::HrRenderFrame()
{
	m_nLeft = 0;
	m_nBottom = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_clearDepth = 0;
}

HrRenderFrame::~HrRenderFrame()
{

}

void HrRenderFrame::SetClearColor(const HrColor& color)
{
	m_clearColor = color;
}

void HrRenderFrame::SetClearDepth(float fDepth)
{
	m_clearDepth = fDepth;
}

uint32 HrRenderFrame::GetLeft() const
{
	return m_nLeft;
}

uint32 HrRenderFrame::GetBottom() const
{
	return m_nBottom;
}

uint32 HrRenderFrame::GetWidht() const
{
	return m_nWidth;
}

uint32 HrRenderFrame::GetHeight() const
{
	return m_nHeight;
}

const HrViewPortPtr& HrRenderFrame::GetViewPort() const
{
	return m_pCurViewPort;
}

void HrRenderFrame::SetViewPort(const HrViewPortPtr& pViewPort)
{
	m_pCurViewPort = pViewPort;
}

void HrRenderFrame::AttachRenderTarget(HrRenderTargetPtr& pRenderTarget)
{
	m_pRenderTarget = pRenderTarget;
}

void HrRenderFrame::DetachRenderTarget()
{
	m_pRenderTarget.reset();
}

