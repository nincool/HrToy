#include "Render/HrCamera.h"
#include "Render/HrViewPort.h"

using namespace Hr;

HrCamera::HrCamera(const std::string& strName)
	: m_fLookAtDistance(0.0f)
	, m_fFov(0.0f)
	, m_fAspect(0.0f)
	, m_fNearPlane(0.1f)
	, m_fFarPlane(1000.0f)
	, m_fWidth(1.0f)
	, m_fHeight(1.0f)
{	
	m_renderingPath = RP_FORWARD;
	m_cameraType = HrCamera::CT_PERSPECTIVE;
	m_nCameraMaskLayer = CML_ALL;
	m_bDirtyCamera = true;
	
	this->ViewParams(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f));
}

HrCamera::HrCamera(const std::string& strName, EnumCameraType cameraType)
	: m_fLookAtDistance(0.0f)
	, m_fFov(0.0f)
	, m_fAspect(0.0f)
	, m_fNearPlane(0.1f)
	, m_fFarPlane(1000.0f)
	, m_fWidth(1.0f)
	, m_fHeight(1.0f)
{
	m_renderingPath = RP_FORWARD;
	m_cameraType = HrCamera::CT_OTHOGRAPHIC;
	m_nCameraMaskLayer = CML_ALL;
	m_bDirtyCamera = true;
	
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
	
	m_bDirtyCamera = true;
}

void HrCamera::ProjectParams(float fFov, float fAspect, float fNearPlane, float fFarPlane)
{
	m_fFov = fFov;
	m_fAspect = fAspect;
	m_fNearPlane = fNearPlane;
	m_fFarPlane = fFarPlane;

	m_matProject = HrMath::PerspectiveFovLh(fFov, fAspect, fNearPlane, fFarPlane);
	m_matInverseProject = HrMath::Inverse(m_matProject);
	m_matViewProj = m_matView * m_matProject;
	m_matInverseViewProj = m_matInverseProject * m_matInverseView;
	
	m_frustum.ClipMatrix(m_matViewProj, m_matInverseViewProj);

	m_bDirtyCamera = false;
}

void HrCamera::ProjectOrthoParams(float fWidth, float fHeight, float fNearPlane, float fFarPlane)
{
	m_fFov = 0;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_fAspect = fWidth / fHeight;
	fNearPlane = fNearPlane;
	fFarPlane = fFarPlane;

	m_matProject = HrMath::OrthoLh(fWidth, fHeight, fNearPlane, fFarPlane);
	m_matInverseProject = HrMath::Inverse(m_matProject);
	m_matViewProj = m_matView * m_matProject;
	m_matInverseViewProj = m_matInverseProject * m_matInverseView;
	
	m_frustum.ClipMatrix(m_matViewProj, m_matInverseViewProj);

	m_bDirtyCamera = false;
}

Matrix4 const& HrCamera::GetViewMatrix() const
{
	return m_matView;
}

Matrix4 const& HrCamera::GetProjectMatrix()
{
	UpdateCameraParams();

	return m_matProject;
}

Matrix4 const& HrCamera::GetViewProjMatrix() 
{
	UpdateCameraParams();

	return m_matViewProj;
}

Matrix4 const& HrCamera::GetInverseViewProjMatrix()
{
	UpdateCameraParams();

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

	m_bDirtyCamera = true;
}

float HrCamera::Aspect() const
{
	return m_fAspect;
}

void HrCamera::Aspect(float fAspect)
{
	m_fAspect = fAspect;

	m_bDirtyCamera = true;
}

float HrCamera::NearPlane() const
{
	return m_fNearPlane;
}

void HrCamera::NearPlane(float fNear)
{
	m_fNearPlane = fNear;

	m_bDirtyCamera = true;

}

float HrCamera::FarPlane() const
{
	return m_fFarPlane;
}

void HrCamera::FarPlane(float fFar)
{
	m_fFarPlane = fFar;

	m_bDirtyCamera = true;
}

void HrCamera::Width(float fWidth)
{	  
	m_fWidth = fWidth;

	m_bDirtyCamera = true;
}	  
	  
void HrCamera::Height(float fHeight)
{	  
	m_fHeight = fHeight;

	m_bDirtyCamera = true;
}	  
	  
float HrCamera::Height() const
{	  
	return m_fHeight;
}	  
	  
float HrCamera::Width() const
{
	return m_fWidth;
}

const Frustum& HrCamera::ViewFrustum()
{
	UpdateCameraParams();

	return m_frustum;
}

EnumRenderingPath HrCamera::GetRenderPath()
{
	return m_renderingPath;
}

void HrCamera::SetRenderPath(EnumRenderingPath renderPath)
{
	m_renderingPath = renderPath;
}

HrCamera::EnumCameraType HrCamera::GetCameraType()
{
	return m_cameraType;
}

void HrCamera::SetCameraType(EnumCameraType cameraType)
{
	if (!m_bDirtyCamera)
		m_bDirtyCamera = m_cameraType != cameraType;

	m_cameraType = cameraType;
}

uint32 HrCamera::GetCameraMaskLayer()
{
	return m_nCameraMaskLayer;
}

void HrCamera::SetCameraMaskLayer(uint32 nMaskLayer)
{
	m_nCameraMaskLayer = nMaskLayer;
}

void HrCamera::UpdateCameraParams()
{
	if (m_bDirtyCamera)
	{
		if (m_cameraType == HrCamera::CT_PERSPECTIVE)
			ProjectParams(m_fFov, m_fAspect, m_fNearPlane, m_fFarPlane);
		else if (m_cameraType == HrCamera::CT_OTHOGRAPHIC)
			ProjectOrthoParams(m_fWidth, m_fHeight, m_fNearPlane, m_fFarPlane);
	}

	m_bDirtyCamera = false;
}

