#include "HrCore/Include/Render/HrViewPort.h"
#include "HrCore/Include/Render/HrCamera.h"

using namespace Hr;

HrViewPort::HrViewPort(float fLeft, float fTop, float fWidth, float fHeight, int nZOrder, HrCamera* pCamera)
{
	m_fLeft = fLeft;
	m_fTop = fTop;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_nZOrder = nZOrder;
	m_pCamera = pCamera;
}

HrViewPort::~HrViewPort()
{
	SAFE_DELETE(m_pCamera);
}


