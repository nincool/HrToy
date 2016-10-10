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

bool HrRenderTarget::CreateRenderWindow(uint32 nWidth, uint32 nHeight)
{
	nWidth = 0;
	nHeight = 0;

	return false;
}

void HrRenderTarget::AddViewPort(HrViewPort* pViewPort)
{
	m_mapViewPort.insert(std::make_pair(pViewPort->GetZOrder(), pViewPort));
}

std::map<int, HrViewPort*>& HrRenderTarget::GetViewPorts()
{
	return m_mapViewPort;
}

