#include "HrCore/Include/Render/HrViewPort.h"
#include "HrCore/Include/Render/HrCamera.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrCore/Include/Kernel/HrWindowModule.h"

using namespace Hr;

HrViewPortDeferredInfo::HrViewPortDeferredInfo()
{
	m_arrGBuffers.assign(nullptr);
	m_arrGBuffersEnable.assign(false);
}

HrViewPortDeferredInfo::~HrViewPortDeferredInfo()
{

}

//////////////////////////////////////////////////
//
//////////////////////////////////////////////////

HrViewPort::HrViewPort(const HrCameraPtr& pCamera)
{
	m_nZOrder = 0;

	auto& pWinCom = HrDirector::Instance()->GetWindowModule();
	m_fTopX = pWinCom->GetWindowX();
	m_fTopY = pWinCom->GetWindowY();
	m_fWidth = pWinCom->GetWindowWidth();
	m_fHeight = pWinCom->GetWindowHeight();

	m_pCamera = pCamera;
	m_pCamera->Fov(HrMath::PI() / 3.0f);
	m_pCamera->Width(m_fWidth);
	m_pCamera->Height(m_fHeight);
	m_pCamera->Aspect(m_fWidth / m_fHeight);

	m_pViewProtDeferredInfo = HrMakeSharedPtr<HrViewPortDeferredInfo>();
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
}

const HrViewPortDeferredInfoPtr& HrViewPort::GetViewPortDeferredInfo() const
{
	return m_pViewProtDeferredInfo;
}


