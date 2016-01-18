#ifndef _HR_MATHCOM_H_
#define _HR_MATHCOM_H_

#include "HrMathPrerequisites.h"
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

		//来自KFL KlayGE 看不懂
		// From Quake III. But the magic number is from http://www.lomont.org/Math/Papers/2003/InvSqrt.pdf
		inline float Recip_Sqrt(float number)
		{
			float const threehalfs = 1.5f;

			float x2 = number * 0.5f;
			union FNI
			{
				float f;
				int32 i;
			} fni;
			fni.f = number;											// evil floating point bit level hacking
			fni.i = 0x5f375a86 - (fni.i >> 1);						// what the fuck?
			fni.f = fni.f * (threehalfs - (x2 * fni.f * fni.f));	// 1st iteration
			fni.f = fni.f * (threehalfs - (x2 * fni.f * fni.f));		// 2nd iteration, this can be removed

			return fni.f;
		}

		template <typename T>
		inline T Abs(T value)
		{
			return T(std::fabs(value));
		}

		inline float Pow(float x, float y)
		{
			return std::pow(x, y);
		}

		inline float Exp(float x)
		{
			return std::exp(x);
		}

		inline float Log(float x)
		{
			return std::log(x);
		}

		inline float Log10(float x)
		{
			return std::log10(x);
		}

		inline float Sin(float x)
		{
			return std::sin(x);
		}

		inline float Cos(float x)
		{
			return sin(x + PI / 2);
		}

		inline void SinCos(float x, float& s, float& c)
		{
			s = sin(x);
			c = cos(x);
		}

		inline float Tan(float x)
		{
			return std::tan(x);
		}

		inline float Asin(float x)
		{
			return std::asin(x);
		}

		inline float Acos(float x)
		{
			return std::acos(x);
		}

		inline float Atan(float x)
		{
			return std::atan(x);
		}

		inline float Sinh(float x)
		{
			return std::sinh(x);
		}

		inline float Cosh(float x)
		{
			return std::cosh(x);
		}

		inline float Tanh(float x)
		{
			return std::tanh(x);
		}
	}
}

#endif