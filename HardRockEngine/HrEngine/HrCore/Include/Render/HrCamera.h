#ifndef _HR_CAMERA_H_
#define _HR_CAMERA_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrMath/Include/HrMath.h"
#include "HrCore/Include/Render/HrDataDefine.h"

namespace Hr
{
	class HR_CORE_API HrCamera
	{
	public:
		HrCamera(const std::string& strName);

		const Vector3& GetEyePos() const;
		const Vector3& GetForward() const;
		const Vector3& GetUp() const;
		const Vector3& GetRight() const;
	
		const Vector3& GetLookAt() const;
		float GetLookAtDistance();


		void Fov(float fFov);
		float FOV() const;
		void Aspect(float fAspect);
		float Aspect() const;
		void NearPlane(float fNear);
		float NearPlane() const;
		void FarPlane(float fFar);
		float FarPlane() const;

		void ViewParams(Vector3 const & v3EvePos, Vector3 const& v3LookAt, Vector3 const& v3Up);
		virtual void ProjectParams(float fFov, float fAspect, float fNearPlane, float fFarPlane);

		Matrix4 const& GetViewMatrix() const;
		Matrix4 const& GetProjectMatrix() const;
		bool ViewProjDirty() { return m_bViewProjDirty; }
		Matrix4 const& GetViewProjMatrix();
		Matrix4 const& GetInverseViewProjMatrix();

		const Frustum& ViewFrustum();

		EnumRenderingPath GetRenderPath();
		void SetRenderPath(EnumRenderingPath renderPath);
	private:
		float m_fLookAtDistance;

		mutable Matrix4 m_matView;
		mutable Matrix4 m_matInverseView;
		mutable Matrix4 m_matProject;
		mutable Matrix4 m_matInverseProject;
		mutable Matrix4 m_matViewProj;
		mutable Matrix4 m_matInverseViewProj;
		
		bool m_bViewProjDirty;
		bool m_bFrustumDirty;

		Vector3 m_v3EyePos;
		Vector3 m_v3Forward;
		Vector3 m_v3Up;
		Vector3 m_v3LookAt;
		Vector3 m_v3Right;

		//投影相关
		float m_fFov;
		float m_fAspect;
		float m_fNearPlane;
		float m_fFarPlane;

		Frustum m_frustum;

		EnumRenderingPath m_renderingPath;
	};
}

#endif




