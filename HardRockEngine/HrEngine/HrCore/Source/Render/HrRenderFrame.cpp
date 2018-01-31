#include "Render/HrRenderFrame.h"
#include "Render/HrViewPort.h"

using namespace Hr;

HrRenderFrame::HrRenderFrame()
{
	m_clearDepth = 1.0f;
	m_clearStencil = 0.0f;

	m_clearColor = HrColor(0.69f, 0.77f, 0.87f, 1.0f);
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

void HrRenderFrame::AddViewPort(const HrViewPortPtr& pViewPort)
{
	if (m_mapViewPorts.find(pViewPort->GetZOrder()) != m_mapViewPorts.end())
	{
		TRE("HrRenderFrame::AddViewPort Error! can not add a same zOrder");
	}
	
	m_mapViewPorts.insert(std::make_pair(pViewPort->GetZOrder(), pViewPort));
}

const HrViewPortPtr& HrRenderFrame::GetViewPort(uint32 zOrder) const
{
	auto itemViewPort = m_mapViewPorts.find(zOrder);
	if (itemViewPort != m_mapViewPorts.end())
	{
		return itemViewPort->second;
	}

	return nullptr;
}

void HrRenderFrame::AttachRenderTarget(EnumRenderTargetLayer attachLayer, HrRenderTargetPtr& pRenderTarget)
{
	BOOST_ASSERT(attachLayer < HrRenderFrame::RTL_MAX);
	m_arrRenderTargets[attachLayer] = pRenderTarget;
}

void HrRenderFrame::DetachRenderTarget(EnumRenderTargetLayer attachLayer)
{
	if (m_arrRenderTargets[attachLayer])
	{
		m_arrRenderTargets[attachLayer].reset();
	}
}

const std::map<uint32, Hr::HrViewPortPtr>& HrRenderFrame::GetAllViewPorts()
{
	return m_mapViewPorts;
}

