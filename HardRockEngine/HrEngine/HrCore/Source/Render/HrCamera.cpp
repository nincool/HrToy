#include "Render/HrCamera.h"

using namespace Hr;

HrCamera::HrCamera()
	:m_fLookAtDistance(0.0f), m_fFov(0.0f), m_fAspect(0.0f), m_fNearPlane(0.0f), m_fFarPlane(0.0f)
{
	
}

void HrCamera::SetPosition(float x, float y, float z)
{
	m_v3Position = Vector3(x, y, z);
}

void HrCamera::Move(const Vector3& v3)
{

}

void HrCamera::ViewParams(Vector3 const & v3EvePos, Vector3 const& v3LookAt, Vector3 const& v3Up)
{
	m_fLookAtDistance = (v3EvePos - v3LookAt).Length();
	m_matView = HrMath::LookAtLh(v3EvePos, v3LookAt, v3Up);
}

void HrCamera::ProjectParams(float fFov, float fAspect, float fNearPlane, float fFarPlane)
{
	m_fFov = fFov;
	m_fAspect = fAspect;
	m_fNearPlane = fNearPlane;
	m_fFarPlane = fFarPlane;

	m_matProject = Hr::HrMath::PerspectiveFovLh(fFov, fAspect, fNearPlane, fFarPlane);
}

Matrix4 const& HrCamera::GetViewMatrix() const
{
	return m_matView;
}

Matrix4 const& HrCamera::GetProjectMatrix() const
{
	return m_matProject;
}
