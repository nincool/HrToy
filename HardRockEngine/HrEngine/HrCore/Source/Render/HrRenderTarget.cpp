#include "HrCore/Include/Render/HrRenderTarget.h"
#include "Render/HrViewPort.h"

using namespace Hr;

HrRenderTarget::HrRenderTarget()
{

}

HrRenderTarget::~HrRenderTarget()
{
	m_mapViewPort.clear();
}

void HrRenderTarget::AddViewPort(HrViewPort* pViewPort)
{
	m_mapViewPort.insert(std::make_pair(pViewPort->GetZOrder(), pViewPort));
}

std::map<int, HrViewPort*>& HrRenderTarget::GetViewPorts()
{
	return m_mapViewPort;
}

