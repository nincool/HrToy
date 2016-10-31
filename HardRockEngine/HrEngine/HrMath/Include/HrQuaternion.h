#ifndef _HR_QUATERNION_H_
#define _HR_QUATERNION_H_

#include "HrMathPrerequisites.h"
#include "HrMath.h"
#include "HrVector3.h"
#include "HrMatrix3.h"
#include "HrMatrix4.h"
#include "HrAngle.h"
#include <algorithm> 

namespace Hr
{

	class HrQuaternion
	{
	public:
		/// Default constructor, initializes to identity rotation (aka 0бу)
		inline HrQuaternion()
			: m_w(1), m_x(0), m_y(0), m_z(0)
		{
		}
		/// Construct from an explicit list of values
		inline HrQuaternion(
			REAL fW,
			REAL fX, REAL fY, REAL fZ)
			: m_w(fW), m_x(fX), m_y(fY), m_z(fZ)
		{
		}
		/// Construct a quaternion from a rotation matrix
		inline HrQuaternion(const Matrix3& rot)
		{
			this->FromRotationMatrix(rot);
		}
		/// Construct a quaternion from an angle/axis
		inline HrQuaternion(const Radian& rfAngle, const Vector3& rkAxis)
		{
			this->FromAngleAxis(rfAngle, rkAxis);
		}
		/// Construct a quaternion from 3 orthonormal local axes
		inline HrQuaternion(const Vector3& xaxis, const Vector3& yaxis, const Vector3& zaxis)
		{
			this->FromAxes(xaxis, yaxis, zaxis);
		}
		/// Construct a quaternion from 3 orthonormal local axes
		//inline Quaternion(const Vector3* akAxis)
		//{
		//	this->FromAxes(akAxis);
		//}
		/// Construct a quaternion from 4 manual w/x/y/z values
		//inline Quaternion(Real* valptr)
		//{
		//	memcpy(&w, valptr, sizeof(Real) * 4);
		//}

		///** Exchange the contents of this quaternion with another.
		inline void swap(HrQuaternion& other)
		{
			std::swap(m_w, other.m_w);
			std::swap(m_x, other.m_x);
			std::swap(m_y, other.m_y);
			std::swap(m_z, other.m_z);
		}

		/// Array accessor operator
		inline REAL operator [] (const size_t i) const
		{
			assert(i < 4);

			return *(&m_w + i);
		}

		/// Array accessor operator
		inline REAL& operator [] (const size_t i)
		{
			assert(i < 4);

			return *(&m_w + i);
		}

		/// Pointer accessor for direct copying
		inline REAL* ptr()
		{
			return &m_w;
		}

		/// Pointer accessor for direct copying
		inline const REAL* ptr() const
		{
			return &m_w;
		}

		void FromRotationMatrix(const Matrix3& kRot);
		void ToRotationMatrix(Matrix3& kRot) const;
		/** Setups the quaternion using the supplied vector, and "roll" around
			that vector by the specified radians.
		*/
		void FromAngleAxis(const Radian& rfAngle, const Vector3& rkAxis);
		void ToAngleAxis(Radian& rfAngle, Vector3& rkAxis) const;
		inline void ToAngleAxis(Degree& dAngle, Vector3& rkAxis) const {
			Radian rAngle;
			ToAngleAxis(rAngle, rkAxis);
			dAngle = rAngle;
		}
		/** Constructs the quaternion using 3 axes, the axes are assumed to be orthonormal
		@see FromAxes
		*/
		void FromAxes(const Vector3* akAxis);
		void FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);
		/** Gets the 3 orthonormal axes defining the quaternion. @see FromAxes */
		//void ToAxes(Vector3* akAxis) const;
		void ToAxes(Vector3& xAxis, Vector3& yAxis, Vector3& zAxis) const;

		/** Returns the X orthonormal axis defining the quaternion. Same as doing
			xAxis = Vector3::UNIT_X * this. Also called the local X-axis
		*/
		Vector3 xAxis(void) const;

		/** Returns the Y orthonormal axis defining the quaternion. Same as doing
			yAxis = Vector3::UNIT_Y * this. Also called the local Y-axis
		*/
		Vector3 yAxis(void) const;

		/** Returns the Z orthonormal axis defining the quaternion. Same as doing
			zAxis = Vector3::UNIT_Z * this. Also called the local Z-axis
		*/
		Vector3 zAxis(void) const;

		inline HrQuaternion& operator= (const HrQuaternion& rkQ)
		{
			m_w = rkQ.m_w;
			m_x = rkQ.m_x;
			m_y = rkQ.m_y;
			m_z = rkQ.m_z;
			return *this;
		}
		HrQuaternion operator+ (const HrQuaternion& rkQ) const;
		HrQuaternion operator- (const HrQuaternion& rkQ) const;
		HrQuaternion operator* (const HrQuaternion& rkQ) const;
		HrQuaternion operator* (REAL fScalar) const;
		HrQuaternion operator- () const;
		inline bool operator== (const HrQuaternion& rhs) const
		{
			return (rhs.m_x == m_x) && (rhs.m_y == m_y) &&
				(rhs.m_z == m_z) && (rhs.m_w == m_w);
		}
		inline bool operator!= (const HrQuaternion& rhs) const
		{
			return !operator==(rhs);
		}
		// functions of a quaternion
		/// Returns the dot product of the quaternion
		REAL Dot(const HrQuaternion& rkQ) const;
		/* Returns the normal length of this quaternion.
		@note This does <b>not</b> alter any values.
		*/
		REAL Norm() const;
		/// Normalises this quaternion, and returns the previous length
		REAL Normalise(void);
		HrQuaternion Inverse() const;  /// Apply to non-zero quaternion
		HrQuaternion UnitInverse() const;  /// Apply to unit-length quaternion
		HrQuaternion Exp() const;
		HrQuaternion Log() const;

		/// Rotation of a vector by a quaternion
		//Vector3 operator* (const Vector3& rkVector) const;

		/** Calculate the local roll element of this quaternion.
		@param reprojectAxis By default the method returns the 'intuitive' result
		that is, if you projected the local X of the quaternion onto the XY plane,
		the angle between it and global X is returned. The co-domain of the returned
		value is from -180 to 180 degrees. If set to false though, the result is
		the rotation around Z axis that could be used to implement the quaternion
		using some non-intuitive order of rotations. This behavior is preserved for
		backward compatibility, to decompose quaternion into yaw, pitch and roll use
		q.ToRotationMatrix().ToEulerAnglesYXZ(yaw, pitch, roll) instead.
		*/
		Radian GetRoll(bool reprojectAxis = true) const;
		///** Calculate the local pitch element of this quaternion
		//@param reprojectAxis By default the method returns the 'intuitive' result
		//that is, if you projected the local Y of the quaternion onto the YZ plane,
		//the angle between it and global Y is returned. The co-domain of the returned
		//value is from -180 to 180 degrees. If set to false though, the result is
		//the rotation around X axis that could be used to implement the quaternion
		//using some non-intuitive order of rotations. This behavior is preserved for
		//backward compatibility, to decompose quaternion into yaw, pitch and roll use
		//q.ToRotationMatrix().ToEulerAnglesYXZ(yaw, pitch, roll) instead.
		//*/
		//Radian getPitch(bool reprojectAxis = true) const;
		///** Calculate the local yaw element of this quaternion
		//@param reprojectAxis By default the method returns the 'intuitive' result
		//that is, if you projected the local Z of the quaternion onto the ZX plane,
		//the angle between it and global Z is returned. The co-domain of the returned
		//value is from -180 to 180 degrees. If set to false though, the result is
		//the rotation around Y axis that could be used to implement the quaternion
		//using some non-intuitive order of rotations. This behavior is preserved for
		//backward compatibility, to decompose quaternion into yaw, pitch and roll use
		//q.ToRotationMatrix().ToEulerAnglesYXZ(yaw, pitch, roll) instead.
		//*/
		//Radian getYaw(bool reprojectAxis = true) const;

		///** Equality with tolerance (tolerance is max angle difference)
		//@remark Both equals() and orientationEquals() measure the exact same thing.
		//One measures the difference by angle, the other by a different, non-linear metric.
		//*/
		//bool equals(const Quaternion& rhs, const Radian& tolerance) const;

		///** Compare two quaternions which are assumed to be used as orientations.
		//@remark Both equals() and orientationEquals() measure the exact same thing.
		//One measures the difference by angle, the other by a different, non-linear metric.
		//@return true if the two orientations are the same or very close, relative to the given tolerance.
		//Slerp ( 0.75f, A, B ) != Slerp ( 0.25f, B, A );
		//therefore be careful if your code relies in the order of the operands.
		//This is specially important in IK animation.
		//*/
		//inline bool orientationEquals(const Quaternion& other, Real tolerance = 1e-3) const
		//{
		//	Real d = this->Dot(other);
		//	return 1 - d*d < tolerance;
		//}

		///** Performs Spherical linear interpolation between two quaternions, and returns the result.
		//Slerp ( 0.0f, A, B ) = A
		//Slerp ( 1.0f, A, B ) = B
		//@return Interpolated quaternion
		//@remarks
		//Slerp has the proprieties of performing the interpolation at constant
		//velocity, and being torque-minimal (unless shortestPath=false).
		//However, it's NOT commutative, which means
		//Slerp ( 0.75f, A, B ) != Slerp ( 0.25f, B, A );
		//therefore be careful if your code relies in the order of the operands.
		//This is specially important in IK animation.
		//*/
		//static Quaternion Slerp(Real fT, const Quaternion& rkP,
		//	const Quaternion& rkQ, bool shortestPath = false);

		///** @see Slerp. It adds extra "spins" (i.e. rotates several times) specified
		//by parameter 'iExtraSpins' while interpolating before arriving to the
		//final values
		//*/
		//static Quaternion SlerpExtraSpins(Real fT,
		//	const Quaternion& rkP, const Quaternion& rkQ,
		//	int iExtraSpins);

		///// Setup for spherical quadratic interpolation
		//static void Intermediate(const Quaternion& rkQ0,
		//	const Quaternion& rkQ1, const Quaternion& rkQ2,
		//	Quaternion& rka, Quaternion& rkB);

		///// Spherical quadratic interpolation
		//static Quaternion Squad(Real fT, const Quaternion& rkP,
		//	const Quaternion& rkA, const Quaternion& rkB,
		//	const Quaternion& rkQ, bool shortestPath = false);

		///** Performs Normalised linear interpolation between two quaternions, and returns the result.
		//nlerp ( 0.0f, A, B ) = A
		//nlerp ( 1.0f, A, B ) = B
		//@remarks
		//Nlerp is faster than Slerp.
		//Nlerp has the proprieties of being commutative (@see Slerp;
		//commutativity is desired in certain places, like IK animation), and
		//being torque-minimal (unless shortestPath=false). However, it's performing
		//the interpolation at non-constant velocity; sometimes this is desired,
		//sometimes it is not. Having a non-constant velocity can produce a more
		//natural rotation feeling without the need of tweaking the weights; however
		//if your scene relies on the timing of the rotation or assumes it will point
		//at a specific angle at a specific weight value, Slerp is a better choice.
		//*/
		//static Quaternion nlerp(Real fT, const Quaternion& rkP,
		//	const Quaternion& rkQ, bool shortestPath = false);

		///// Cutoff for sine near zero
		//static const Real msEpsilon;

		//// special values
		//static const Quaternion ZERO;
		//static const Quaternion IDENTITY;

		//Real w, x, y, z;

		///// Check whether this quaternion contains valid values
		//inline bool isNaN() const
		//{
		//	return Math::isNaN(x) || Math::isNaN(y) || Math::isNaN(z) || Math::isNaN(w);
		//}

		///** Function for writing to a stream. Outputs "Quaternion(w, x, y, z)" with w,x,y,z
		//being the member values of the quaternion.
		//*/
		//inline _OgreExport friend std::ostream& operator <<
		//	(std::ostream& o, const Quaternion& q)
		//{
		//	o << "Quaternion(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
		//	return o;
		//}

	public:
		/// Cutoff for sine near zero
		static const REAL msEpsilon;

		// special values
		static const HrQuaternion ZERO;
		static const HrQuaternion IDENTITY;

	protected:
		REAL m_w, m_x, m_y, m_z;
	};
};

#endif

