#include "HrCore/Include/Render/HrViewPort.h"
#include "HrCore/Include/Render/HrCamera.h"

using namespace Hr;

HrViewPort::HrViewPort( uint32 nTopX, uint32 nTopY, uint32 nWidth, uint32 nHeight, int nZOrder)
{
	m_nTopX = nTopX;
	m_nTopY = nTopY;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
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
		m_pCamera->ProjectParams(HrMath::PI() / 3.0f, m_nWidth / m_nHeight, 0.3f, 1000.0f);
	}
}

uint32 HrViewPort::GetTopX() const
{
	return m_nTopX;
}

uint32 HrViewPort::GetTopY() const
{
	return m_nTopY;
}

uint32 HrViewPort::GetWidth() const
{
	return m_nWidth;
}

uint32 HrViewPort::GetHeight() const
{
	return m_nHeight;
}

int HrViewPort::GetZOrder() const
{
	return m_nZOrder;
}

const HrCameraPtr& HrViewPort::GetCamera() const
{
	return m_pCamera;
}

