#ifndef _HR_MATHCALCULATE_H_
#define _HR_MATHCALCULATE_H_

#include "HrMathPreDeclare.h"
#include "HrMathCom.h"
#include "HrMatrix4.h"
#include "Matrix_T.h"
#include "HrVector3.h"
#include "HrVector4.h"

namespace Hr
{
	namespace HrMath
	{
		inline Vector3 Normalize(const Vector3& rhs)
		{
			return rhs * Recip_Sqrt(rhs.SquareLength());
		}

		inline Vector3 Cross(Vector3 const& lhs, Vector3 const& rhs)
		{
			return Vector3(lhs.y() * rhs.z() - lhs.z() * rhs.y(),
				lhs.z() * rhs.x() - lhs.x() * rhs.z(),
				lhs.x() * rhs.y() - lhs.y() * rhs.x());
		}

		inline float Dot(Vector3 const& lhs, Vector3 const& rhs)
		{
			return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
		}

		inline Matrix4 Transpose(Matrix4 const & rhs)
		{
			return Matrix4(
			rhs(0, 0), rhs(1, 0), rhs(2, 0), rhs(3, 0),
			rhs(0, 1), rhs(1, 1), rhs(2, 1), rhs(3, 1),
			rhs(0, 2), rhs(1, 2), rhs(2, 2), rhs(3, 2),
			rhs(0, 3), rhs(1, 3), rhs(2, 3), rhs(3, 3));
		}

		inline Matrix4 Mul(const Matrix4& lhs, const Matrix4& rhs)
		{
			Matrix4 const tmp(Transpose(rhs));

			return Matrix4(
				lhs(0, 0) * tmp(0, 0) + lhs(0, 1) * tmp(0, 1) + lhs(0, 2) * tmp(0, 2) + lhs(0, 3) * tmp(0, 3),
				lhs(0, 0) * tmp(1, 0) + lhs(0, 1) * tmp(1, 1) + lhs(0, 2) * tmp(1, 2) + lhs(0, 3) * tmp(1, 3),
				lhs(0, 0) * tmp(2, 0) + lhs(0, 1) * tmp(2, 1) + lhs(0, 2) * tmp(2, 2) + lhs(0, 3) * tmp(2, 3),
				lhs(0, 0) * tmp(3, 0) + lhs(0, 1) * tmp(3, 1) + lhs(0, 2) * tmp(3, 2) + lhs(0, 3) * tmp(3, 3),

				lhs(1, 0) * tmp(0, 0) + lhs(1, 1) * tmp(0, 1) + lhs(1, 2) * tmp(0, 2) + lhs(1, 3) * tmp(0, 3),
				lhs(1, 0) * tmp(1, 0) + lhs(1, 1) * tmp(1, 1) + lhs(1, 2) * tmp(1, 2) + lhs(1, 3) * tmp(1, 3),
				lhs(1, 0) * tmp(2, 0) + lhs(1, 1) * tmp(2, 1) + lhs(1, 2) * tmp(2, 2) + lhs(1, 3) * tmp(2, 3),
				lhs(1, 0) * tmp(3, 0) + lhs(1, 1) * tmp(3, 1) + lhs(1, 2) * tmp(3, 2) + lhs(1, 3) * tmp(3, 3),

				lhs(2, 0) * tmp(0, 0) + lhs(2, 1) * tmp(0, 1) + lhs(2, 2) * tmp(0, 2) + lhs(2, 3) * tmp(0, 3),
				lhs(2, 0) * tmp(1, 0) + lhs(2, 1) * tmp(1, 1) + lhs(2, 2) * tmp(1, 2) + lhs(2, 3) * tmp(1, 3),
				lhs(2, 0) * tmp(2, 0) + lhs(2, 1) * tmp(2, 1) + lhs(2, 2) * tmp(2, 2) + lhs(2, 3) * tmp(2, 3),
				lhs(2, 0) * tmp(3, 0) + lhs(2, 1) * tmp(3, 1) + lhs(2, 2) * tmp(3, 2) + lhs(2, 3) * tmp(3, 3),

				lhs(3, 0) * tmp(0, 0) + lhs(3, 1) * tmp(0, 1) + lhs(3, 2) * tmp(0, 2) + lhs(3, 3) * tmp(0, 3),
				lhs(3, 0) * tmp(1, 0) + lhs(3, 1) * tmp(1, 1) + lhs(3, 2) * tmp(1, 2) + lhs(3, 3) * tmp(1, 3),
				lhs(3, 0) * tmp(2, 0) + lhs(3, 1) * tmp(2, 1) + lhs(3, 2) * tmp(2, 2) + lhs(3, 3) * tmp(2, 3),
				lhs(3, 0) * tmp(3, 0) + lhs(3, 1) * tmp(3, 1) + lhs(3, 2) * tmp(3, 2) + lhs(3, 3) * tmp(3, 3));
		}

		template <typename T>
		Matrix4 RotationX(T const& x)
		{
			float sx, cx;
			SinCos(x, sx, cx);

			return Matrix4(
				1,        0,        0,      0,
				0,        cx,       sx,     0,
				0,       -sx,       cx,     0,
				0,        0,        0,      1);
		}

		template <typename T>
		Matrix4 RotationY(T const& y)
		{
			float sy, cy;
			SinCos(y, sy, cy);

			return Matrix4(
				cy,        0,      -sy,       0,
				0,         1,       0,        0,
				sy,        0,       cy,       0,
				0,         0,        0,       1);
		}

		template <typename T>
		Matrix4 RotationZ(T const& z)
		{
			float sz, cz;
			SinCos(z, sz, cz);

			return Matrix4(
				cz,       sz,        0,        0,
				-sz,      cz,        0,        0,
				0,        0,         1,        0,
				0,        0,         0,        1);
		}

		//template <typename T>
		//Matrix4 Rotation(T const& angle, Vector3 const& axis)
		//{

		//}
		inline Matrix4 Inverse(Matrix4 m) 
		{
			REAL m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
			REAL m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
			REAL m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
			REAL m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

			REAL v0 = m20 * m31 - m21 * m30;
			REAL v1 = m20 * m32 - m22 * m30;
			REAL v2 = m20 * m33 - m23 * m30;
			REAL v3 = m21 * m32 - m22 * m31;
			REAL v4 = m21 * m33 - m23 * m31;
			REAL v5 = m22 * m33 - m23 * m32;

			REAL t00 = +(v5 * m11 - v4 * m12 + v3 * m13);
			REAL t10 = -(v5 * m10 - v2 * m12 + v1 * m13);
			REAL t20 = +(v4 * m10 - v2 * m11 + v0 * m13);
			REAL t30 = -(v3 * m10 - v1 * m11 + v0 * m12);

			REAL invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

			REAL d00 = t00 * invDet;
			REAL d10 = t10 * invDet;
			REAL d20 = t20 * invDet;
			REAL d30 = t30 * invDet;

			REAL d01 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
			REAL d11 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
			REAL d21 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
			REAL d31 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

			v0 = m10 * m31 - m11 * m30;
			v1 = m10 * m32 - m12 * m30;
			v2 = m10 * m33 - m13 * m30;
			v3 = m11 * m32 - m12 * m31;
			v4 = m11 * m33 - m13 * m31;
			v5 = m12 * m33 - m13 * m32;

			REAL d02 = +(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
			REAL d12 = -(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
			REAL d22 = +(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
			REAL d32 = -(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

			v0 = m21 * m10 - m20 * m11;
			v1 = m22 * m10 - m20 * m12;
			v2 = m23 * m10 - m20 * m13;
			v3 = m22 * m11 - m21 * m12;
			v4 = m23 * m11 - m21 * m13;
			v5 = m23 * m12 - m22 * m13;

			REAL d03 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
			REAL d13 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
			REAL d23 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
			REAL d33 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

			return Matrix4(
				d00, d01, d02, d03,
				d10, d11, d12, d13,
				d20, d21, d22, d23,
				d30, d31, d32, d33);
		}

		//矩阵 
		inline Matrix4 LookAtLh(Vector3 const& v3Eye, Vector3 const& v3At, Vector3 const& v3Up)
		{
			Vector3 zAxis(Normalize(v3At - v3Eye));
			Vector3 xAxis(Normalize(Cross(v3Up, zAxis)));
			Vector3 yAxis(Cross(zAxis, xAxis));

			return Matrix4(
				xAxis.x(), yAxis.x(), zAxis.x(), 0,
				xAxis.y(), yAxis.y(), zAxis.y(), 0,
				xAxis.z(), yAxis.z(), zAxis.z(), 0,
				-Dot(xAxis, v3Eye), -Dot(yAxis, v3Eye), -Dot(zAxis, v3Eye), 1);
		}

		template <typename T>
		Matrix4 PerspectiveLh(T const & width, T const & height, T const & nearPlane, T const & farPlane)
		{
			//   | 2N/(right-left )        0           0          0 |
			//   |         0        2N/(top-buttom)    0          0 |
			//   |         0               0        (a)F/(F-N)    1 |
			//   |         0               0       (b)-NF/(F-N)   0 |
			//
			// right-left和top-buttom可以分别看做是投影平面的宽w和高h

			T const a(farPlane / (farPlane - nearPlane));
			T const N2(nearPlane + nearPlane);

			return Matrix4(
				N2 / width, 0, 0, 0,
				0, N2 / height, 0, 0,
				0, 0, a, 1,
				0, 0, -nearPlane*a, 0);

		}

		template <typename T>
		Matrix4 PerspectiveFovLh(T const& fov, T const& aspect, T const& nearPlane, T const& farPlane)
		{
			//   | 2N/(right-left )        0           0          0 |
			//   |         0        2N/(top-buttom)    0          0 |
			//   |         0               0        (a)F/(F-N)    1 |
			//   |         0               0       (b)-NF/(F-N)   0 |
			//
			// right-left和top-buttom可以分别看做是投影平面的宽w和高h
			//
			//     top-buttom = h=> tan(fov/2) = h/2 / N => h=2N*tan(fov/2)
			//     2N/(top-buttom) = 2N/h = 2N/(2N*tan(fov/2)) = 1/tan(fov/2)
			//     2N/(right-left) = 2N/w = 2N/(h*aspect) = 2N/(2N*tan(fov/2)*aspect) = 1/(tan(fov/2)*aspect)

			T const m11(T(1) / tan(fov / 2));
			T const m00(m11 / aspect);
			T const a(farPlane / (farPlane - nearPlane));

			return Matrix4(
				m00, 0, 0, 0,
				0, m11, 0, 0,
				0, 0, a, 1,
				0, 0, -nearPlane*a, 0);
		}



	}
}


#endif





