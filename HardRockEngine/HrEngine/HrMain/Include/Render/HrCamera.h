#ifndef _HR_CAMERA_H_
#define _HR_CAMERA_H_

#include "HrMainPrerequisiters.h"
#include "ICamera.h"

namespace Hr
{
	class HR_MAIN_API HrCamera : public ICamera
	{
	public:
		HrCamera();

		virtual void SetPosition(float x, float y, float z) override;

		virtual void Move(const Vector3& v3) override;

		virtual const Vector3& GetPosition() override
		{
			return m_v3Position;
		}

		virtual void ViewParams(Vector3 const & v3EvePos, Vector3 const& v3LookAt, Vector3 const& v3Up) override;
		virtual void ProjectParams(float fFov, float fAspect, float fNearPlane, float fFarPlane) override;

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




