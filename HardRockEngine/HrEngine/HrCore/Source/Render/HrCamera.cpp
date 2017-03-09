#include "Render/HrCamera.h"
#include "Scene/HrEntityNode.h"

using namespace Hr;

HrCamera::HrCamera()
	:m_fLookAtDistance(0.0f), m_fFov(0.0f), m_fAspect(0.0f), m_fNearPlane(0.0f), m_fFarPlane(0.0f)
{
	m_bViewProjDirty = false;
}

void HrCamera::AttachCameraNode(HrCameraNode* pCameraNode)
{
	m_pAttachCameraNode = pCameraNode;
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
