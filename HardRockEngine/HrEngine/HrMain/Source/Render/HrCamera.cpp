#include "Render/HrCamera.h"

using namespace Hr;

HrCamera::HrCamera()
	:m_fLookAtDistance(0.0f), m_fFov(0.0f), m_fAspect(0.0f), m_fNearPlane(0.0f), m_fFarPlane(0.0f)
{
	
}

void HrCamera::SetPosition(float x, float y, float z)
{
	m_v3Position.Set(x, y, z);
}

void HrCamera::Move(const Vector3& v3)
{

}

void HrCamera::ViewParams(Vector3 const & v3EvePos, Vector3 const& v3LookAt, Vector3 const& v3Up)
{
	m_fLookAtDistance = (v3EvePos - v3LookAt).Length();
}

void HrCamera::ProjectParams(float fFov, float fAspect, float fNearPlane, float fFarPlane)
{
	m_fFov = fFov;
	m_fAspect = fAspect;
	m_fNearPlane = fNearPlane;
	m_fFarPlane = fFarPlane;

	m_matProject = Hr::HrMath::PerspectiveFovLh(fFov, fAspect, fNearPlane, fFarPlane);
}
