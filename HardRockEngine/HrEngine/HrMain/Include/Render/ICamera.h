#ifndef _I_CAMERA_H_
#define _I_CAMERA_H_

#include "HrMainPrerequisiters.h"
#include "MemoryAlloc/HrMemoryAllocatorConfig.h"
#include "HrMath/Include/HrMath.h"

namespace Hr
{
	class HR_MAIN_API ICamera : public SceneObjAllocatedObject
	{
	public:
		virtual ~ICamera(){}

		virtual void SetPosition(float x, float y, float z) = 0;
		
		/**
		 *	@Brief: �ƶ� [1/8/2016 By Hr]
		*/
		virtual void Move(const Vector3& v3) = 0;

		virtual const Vector3& GetPosition() = 0;
		
		virtual void ViewParams(Vector3 const & v3EvePos, Vector3 const& v3LookAt, Vector3 const& v3Up) = 0;
		virtual void ProjectParams(float fFov, float fAspect, float fNearPlane, float fFarPlane) = 0;

	};
}

#endif