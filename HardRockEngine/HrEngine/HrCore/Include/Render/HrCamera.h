#ifndef _HR_CAMERA_H_
#define _HR_CAMERA_H_

#include "HrCore/Include/HrCorePrerequisite.h"
#include "HrCore/Include/MemoryAlloc/HrMemoryAllocatorConfig.h"
#include "HrMath/Include/HrMath.h"

namespace Hr
{
	class HR_CORE_API HrCamera 
	{
	public:
		HrCamera();

		void SetPosition(float x, float y, float z);
		void Move(const Vector3& v3);
		const Vector3& GetPosition()
		{
			return m_v3Position;
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
	private:
		float m_fLookAtDistance;

		Vector3 m_v3Position;
		Matrix4 m_matView;

		//投影相关
		float m_fFov;
		float m_fAspect;
		float m_fNearPlane;
		float m_fFarPlane;

		Matrix4 m_matProject;
	};
}

#endif




