#ifndef _HR_MATHCALCULATE_H_
#define _HR_MATHCALCULATE_H_

#include "HrMathPreDeclare.h"
#include "HrMathCom.h"
#include "HrMatrix4.h"
#include "Matrix_T.h"

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





