#include "HrCore/Include/Render/HrViewPort.h"
#include "HrCore/Include/Render/HrCamera.h"

using namespace Hr;

HrViewPort::HrViewPort(const HrCameraPtr& pCamera)
{
	m_fTopX = m_fTopY = 0;
	m_fWidth = m_fHeight = 100;
	m_nZOrder = 0;

	m_pCamera = pCamera;
	m_pCamera->ProjectParams(HrMath::PI() / 3.0f, m_fWidth / m_fHeight, 0.1f, 300.0f);
}

HrViewPort::HrViewPort(const HrCameraPtr& pCamera, float fTopX, float fTopY, float fWidth, float fHeight, int nZOrder)
{
	SetViewPortAttribute(fTopX, fTopY, fWidth, fHeight, nZOrder);
}

HrViewPort::~HrViewPort()
{
}

float HrViewPort::GetTopX() const
{
	return m_fTopX;
}

float HrViewPort::GetTopY() const
{
	return m_fTopY;
}

float HrViewPort::GetWidth() const
{
	return m_fWidth;
}

float HrViewPort::GetHeight() const
{
	return m_fHeight;
}

int HrViewPort::GetZOrder() const
{
	return m_nZOrder;
}

const HrCameraPtr& HrViewPort::GetCamera() const
{
	return m_pCamera;
}

void HrViewPort::SetViewPortAttribute(float fTopX, float fTopY, float fWidth, float fHeight, int nZOrder)
{
	m_fTopX = fTopX;
	m_fTopY = fTopY;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_nZOrder = nZOrder;

	m_pCamera->ProjectParams(m_pCamera->FOV(), m_fWidth / m_fHeight, m_pCamera->NearPlane(), m_pCamera->FarPlane());
}

