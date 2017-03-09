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

	m_pCamera->ViewParams(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f));
	m_pCamera->ProjectParams(HrMath::PI() / 3.0f, fWidth / fHeight, 0.3f, 1000.0f);
}

HrViewPort::~HrViewPort()
{
	SAFE_DELETE(m_pCamera);
}


