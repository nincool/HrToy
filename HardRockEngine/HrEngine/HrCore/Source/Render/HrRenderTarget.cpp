#include "HrCore/Include/Render/HrRenderTarget.h"
#include "Render/HrViewPort.h"

using namespace Hr;

HrRenderTarget::HrRenderTarget()
{

}

HrRenderTarget::~HrRenderTarget()
{
	for (auto& item : m_mapViewPort)
	{
		SAFE_DELETE(item.second);
	}
	m_mapViewPort.clear();
}

HrViewPort* HrRenderTarget::AddViewPort(HrCamera* pCamera, float fLeft, float fTop, float fWidth, float fHeight, int nZOrder)
{
	HrViewPort* pViewPort = HR_NEW HrViewPort(fLeft, fTop, fWidth, fHeight, nZOrder, pCamera);
	m_mapViewPort.insert(std::make_pair(nZOrder, pViewPort));

	return pViewPort;
}

std::map<int, HrViewPort*>& HrRenderTarget::GetViewPorts()
{
	return m_mapViewPort;
}

