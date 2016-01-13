#ifndef _HR_QUATERNION_H_
#define _HR_QUATERNION_H_

#include "HrMathPrerequisites.h"
#include "HrMath.h"
#include "HrVector3.h"
#include "HrMatrix3.h"
#include "HrMatrix4.h"

namespace Hr
{
	class HrQuaternion
	{
	public:
		/// Default constructor, initializes to identity rotation (aka 0бу)
		inline HrQuaternion()
			: w(1), x(0), y(0), z(0)
		{
		}

		/// Construct from an explicit list of values
		inline HrQuaternion(
			REAL fW,
			REAL fX, REAL fY, REAL fZ)
			: w(fW), x(fX), y(fY), z(fZ)
		{
		}

		/// Construct a quaternion from a rotation matrix
		inline HrQuaternion(const HrMatrix3& rot)
		{
			this->FromRotationMatrix(rot);
		}

		/// Construct a quaternion from 3 orthonormal local axes
		inline HrQuaternion(const HrVector3* akAxis)
		{
			this->FromAxes(akAxis);
		}


		/** Constructs the quaternion using 3 axes, the axes are assumed to be orthonormal
		@see FromAxes
		*/
		void FromAxes(const HrVector3* akAxis);

		void FromRotationMatrix(const HrMatrix3& kRot);
	public:
		REAL w, x, y, z;
	};


}

#endif

