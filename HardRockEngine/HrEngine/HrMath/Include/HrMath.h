#ifndef _HR_MATH_H_
#define _HR_MATH_H_

#include "HrMathPrerequisites.h"
#include "HrMathPreDeclare.h"
//#include "HrVector3.h"
//#include "HrMatrix3.h"
#include "HrMatrix4.h"

//#include "Vector_T.h"
//#include "Plane_T.h"
//#include "Matrix_T.h"

#include <cmath>

namespace Hr
{
	// 常量定义
	/////////////////////////////////////////////////////////////////////////////////
	float const PI = 3.141592f;			    // PI
	float const PI2 = 6.283185f;			// PI * 2
	float const PIdiv2 = 1.570796f;			// PI / 2

	float const DEG90 = 1.570796f;			// 90 度
	float const DEG270 = -1.570796f;		// 270 度
	float const DEG45 = 0.7853981f;			// 45 度
	float const DEG5 = 0.0872664f;			// 5 度
	float const DEG10 = 0.1745329f;			// 10 度
	float const DEG20 = 0.3490658f;			// 20 度
	float const DEG30 = 0.5235987f;			// 30 度
	float const DEG60 = 1.047197f;			// 60 度
	float const DEG120 = 2.094395f;			// 120 度

	float const DEG40 = 0.6981317f;			// 40 度
	float const DEG80 = 1.396263f;			// 80 度
	float const DEG140 = 2.443460f;			// 140 度
	float const DEG160 = 2.792526f;			// 160 度

	float const SQRT2 = 1.414213f;			// 根2
	float const SQRT_2 = 0.7071068f;		// 1 / SQRT2
	float const SQRT3 = 1.732050f;			// 根3

	float const DEG2RAD = 0.01745329f;		// 角度化弧度因数
	float const RAD2DEG = 57.29577f;		// 弧度化角度因数

	namespace HrMath
	{
		template <typename T>
		inline T Sqrt(T value)
		{
			return T(std::sqrt(value));
		}

		template <typename T>
		inline T Abs(T value)
		{
			return T(std::fabs(value));
		}

		inline float tan(float x)
		{
			return std::tan(x);
		}

		//矩阵 
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
				N2/width,     0,                0,            0,      
				0,         N2/height,           0,            0,
				0,            0,                a,            1,
				0,            0,           -nearPlane*a,      0);

		}

		template <typename T>
		HrMatrix4 PerspectiveFovLh(T const& fov, T const& aspect, T const& nearPlane, T const& farPlane)
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
			
			T const m11( T(1) / tan(fov / 2));
			T const m00(m11 / aspect);
			T const a(farPlane / (farPlane - nearPlane));

			return HrMatrix4(
				m00,          0,                0,             0,
				0,            m11,              0,             0,
				0,            0,                a,             1,
				0,            0,           -nearPlane*a,       0);
		}
	}
}


#endif

