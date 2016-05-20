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

	m_pCamera->ViewParams(Vector3(0.0f, 2.0, -5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	m_pCamera->ProjectParams(Hr::PI * 0.25f, fWidth / fHeight, 1.0f, 1000.0f);
}

HrViewPort::~HrViewPort()
{
	SAFE_DELETE(m_pCamera);
}

