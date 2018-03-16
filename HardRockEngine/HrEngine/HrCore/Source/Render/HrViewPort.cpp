#include "HrCore/Include/Render/HrViewPort.h"
#include "HrCore/Include/Render/HrCamera.h"

using namespace Hr;

HrViewPort::HrViewPort(float fTopX, float fTopY, float fWidth, float fHeight, int nZOrder)
{
	m_fTopX = fTopX;
	m_fTopY = fTopY;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_nZOrder = nZOrder;
}

HrViewPort::~HrViewPort()
{
}

void HrViewPort::SetCamera(const HrCameraPtr& pCamera)
{
	m_pCamera = pCamera;
	if (m_pCamera)
	{
		m_pCamera->AttachViewPort(shared_from_this());

		m_pCamera->ViewParams(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f));
		m_pCamera->ProjectParams(HrMath::PI() / 3.0f, m_fWidth / m_fHeight, 0.3f, 1000.0f);
	}
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

