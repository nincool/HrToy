#ifndef _HR_CAMERA_H_
#define _HR_CAMERA_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrMath/Include/HrMath.h"

namespace Hr
{
	class HR_CORE_API HrCamera
	{
	public:
		HrCamera();

		const Vector3& GetEyePos() const
		{
			return m_v3EyePos;
		}
		const Vector3& GetForward() const
		{
			return m_v3Forward;
		}
		const Vector3& GetUp() const
		{
			return m_v3Up;
		}
		const Vector3& GetLookAt() const
		{
			return m_v3LookAt;
		}
		float GetLookAtDistance()
		{
			return m_fLookAtDistance;
		}

		float FOV() const
		{
			return m_fFov;
		}
		float Apsect() const
		{
			return m_fAspect;
		}
		float NearPlane() const
		{
			return m_fNearPlane;
		}
		float FarPlane() const
		{
			return m_fFarPlane;
		}

		void ViewParams(Vector3 const & v3EvePos, Vector3 const& v3LookAt, Vector3 const& v3Up);
		virtual void ProjectParams(float fFov, float fAspect, float fNearPlane, float fFarPlane);

		Matrix4 const& GetViewMatrix() const;
		Matrix4 const& GetProjectMatrix() const;
		bool ViewProjDirty() { return m_bViewProjDirty; }
		Matrix4 const& GetViewProjMatrix();

		void AttachCameraNode(HrCameraNode* pCameraNode);
		HrCameraNode* GetAttachCameraNode() { return m_pAttachCameraNode; }
	private:
		float m_fLookAtDistance;

		mutable Matrix4 m_matView;
		mutable Matrix4 m_matInverseView;
		mutable Matrix4 m_matProject;
		mutable Matrix4 m_matViewProj;
		
		bool m_bViewProjDirty;

		Vector3 m_v3EyePos;
		Vector3 m_v3Forward;
		Vector3 m_v3Up;
		Vector3 m_v3LookAt;

		//ͶӰ���
		float m_fFov;
		float m_fAspect;
		float m_fNearPlane;
		float m_fFarPlane;


		HrCameraNode* m_pAttachCameraNode;
	};
}

#endif




