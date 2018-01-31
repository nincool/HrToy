#include "Render/HrCamera.h"
#include "Render/HrViewPort.h"

using namespace Hr;

HrCamera::HrCamera(const std::string& strName) : HrSceneObjectComponent(strName)
	, m_fLookAtDistance(0.0f), m_fFov(0.0f), m_fAspect(0.0f), m_fNearPlane(0.0f), m_fFarPlane(0.0f)
{
	m_bViewProjDirty = false;

	this->ViewParams(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f));
}

void HrCamera::ViewParams(Vector3 const & v3EvePos, Vector3 const& v3LookAt, Vector3 const& v3Up)
{
	m_fLookAtDistance = HrMath::Length(v3EvePos - v3LookAt);
	m_matView = HrMath::LookAtLh(v3EvePos, v3LookAt, v3Up);
	m_matInverseView = HrMath::Inverse(m_matView);

	m_v3EyePos = m_matInverseView.Row(3);
	m_v3Forward = m_matInverseView.Row(2);
	m_v3Up = m_matInverseView.Row(1);
	m_v3LookAt = m_v3EyePos + m_v3Forward * m_fLookAtDistance;

	m_bViewProjDirty = true;
}

void HrCamera::ProjectParams(float fFov, float fAspect, float fNearPlane, float fFarPlane)
{
	m_fFov = fFov;
	m_fAspect = fAspect;
	m_fNearPlane = fNearPlane;
	m_fFarPlane = fFarPlane;

	m_matProject = HrMath::PerspectiveFovLh(fFov, fAspect, fNearPlane, fFarPlane);

	m_bViewProjDirty = true;
}

Matrix4 const& HrCamera::GetViewMatrix() const
{
	return m_matView;
}

Matrix4 const& HrCamera::GetProjectMatrix() const
{
	return m_matProject;
}

Matrix4 const& HrCamera::GetViewProjMatrix() 
{
	if (m_bViewProjDirty)
	{
		m_matViewProj = (m_matView * m_matProject);
		m_bViewProjDirty = false;
	}

	return m_matViewProj;
}

const Vector3& HrCamera::GetEyePos() const
{
	return m_v3EyePos;
}

const Vector3& HrCamera::GetForward() const
{
	return m_v3Forward;
}

const Vector3& HrCamera::GetUp() const
{
	return m_v3Up;
}

const Vector3& HrCamera::GetLookAt() const
{
	return m_v3LookAt;
}

float HrCamera::GetLookAtDistance()
{
	return m_fLookAtDistance;
}

float HrCamera::FOV() const
{
	return m_fFov;
}

float HrCamera::Apsect() const
{
	return m_fAspect;
}

float HrCamera::NearPlane() const
{
	return m_fNearPlane;
}

float HrCamera::FarPlane() const
{
	return m_fFarPlane;
}

void HrCamera::AttachViewPort(const HrViewPortPtr& pViewPort)
{
	m_pViewPort = pViewPort;
}

const HrViewPortPtr& HrCamera::GetViewPort()
{
	return m_pViewPort;
}
