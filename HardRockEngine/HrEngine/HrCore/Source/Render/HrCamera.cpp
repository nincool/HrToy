#include "Render/HrCamera.h"
#include "Render/HrViewPort.h"

using namespace Hr;

HrCamera::HrCamera(const std::string& strName) : m_fLookAtDistance(0.0f), m_fFov(0.0f), m_fAspect(0.0f), m_fNearPlane(0.0f), m_fFarPlane(0.0f)
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
	m_v3Right = m_matInverseView.Row(0);
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
	m_matInverseProject = HrMath::Inverse(m_matProject);

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
		m_matInverseViewProj = m_matInverseProject * m_matInverseView;
		m_bViewProjDirty = false;
	}

	return m_matViewProj;
}

Matrix4 const& HrCamera::GetInverseViewProjMatrix()
{
	if (m_bViewProjDirty)
	{
		m_matViewProj = (m_matView * m_matProject);
		m_matInverseViewProj = m_matInverseProject * m_matInverseView;
		m_bViewProjDirty = false;
	}

	return m_matInverseViewProj;
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

const Vector3& HrCamera::GetRight() const
{
	return m_v3Right;
}

float HrCamera::GetLookAtDistance()
{
	return m_fLookAtDistance;
}

float HrCamera::FOV() const
{
	return m_fFov;
}

void HrCamera::Fov(float fFov)
{
	m_fFov = fFov;
	ProjectParams(m_fFov, m_fAspect, m_fNearPlane, m_fFarPlane);
}

float HrCamera::Aspect() const
{
	return m_fAspect;
}

void HrCamera::Aspect(float fAspect)
{
	m_fAspect = fAspect;
	ProjectParams(m_fFov, m_fAspect, m_fNearPlane, m_fFarPlane);
}

float HrCamera::NearPlane() const
{
	return m_fNearPlane;
}

void HrCamera::NearPlane(float fNear)
{
	m_fNearPlane = fNear;
	ProjectParams(m_fFov, m_fAspect, m_fNearPlane, m_fFarPlane);
}

float HrCamera::FarPlane() const
{
	return m_fFarPlane;
}

void HrCamera::FarPlane(float fFar)
{
	m_fFarPlane = fFar;
	ProjectParams(m_fFov, m_fAspect, m_fNearPlane, m_fFarPlane);
}
