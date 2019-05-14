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
		enum EnumCameraType
		{
			CT_PERSPECTIVE,
			CT_OTHOGRAPHIC,
		};

		HrCamera(const std::string& strName);
		HrCamera(const std::string& strName, EnumCameraType cameraType);

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

		void Width(float fWidth);
		float Width() const;

		void Height(float fHeight);
		float Height() const;

		void ViewParams(Vector3 const & v3EvePos, Vector3 const& v3LookAt, Vector3 const& v3Up);
		void ProjectParams(float fFov, float fAspect, float fNearPlane, float fFarPlane);
		void ProjectOrthoParams(float fWidth, float fHeight, float fNearPlane, float fFarPlane);

		Matrix4 const& GetViewMatrix() const;
		Matrix4 const& GetProjectMatrix();
		Matrix4 const& GetViewProjMatrix();
		Matrix4 const& GetInverseViewProjMatrix();

		const Frustum& ViewFrustum();

		EnumRenderingPath GetRenderPath();
		void SetRenderPath(EnumRenderingPath renderPath);

		EnumCameraType GetCameraType();
		void SetCameraType(EnumCameraType cameraType);

		uint32 GetCameraMaskLayer();
		void SetCameraMaskLayer(uint32 nMaskLayer);

	protected:
		void UpdateCameraParams();
	private:
		EnumCameraType m_cameraType;

		float m_fLookAtDistance;

		mutable Matrix4 m_matView;
		mutable Matrix4 m_matInverseView;
		mutable Matrix4 m_matProject;
		mutable Matrix4 m_matInverseProject;
		mutable Matrix4 m_matViewProj;
		mutable Matrix4 m_matInverseViewProj;
		
		bool m_bDirtyCamera;

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
		float m_fWidth;
		float m_fHeight;

		Frustum m_frustum;

		EnumRenderingPath m_renderingPath;
		uint32 m_nCameraMaskLayer;
	};
}

#endif




