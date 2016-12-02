#ifndef _HR_MATHCOM_H_
#define _HR_MATHCOM_H_

#include "HrMathPrerequisites.h"
#include <cmath>

namespace Hr
{
	namespace HrMath
	{
		inline float PI() { return KlayGE::PI; }
		inline float PI2() { return KlayGE::PIdiv2; }
		inline float DEG90() { return KlayGE::DEG90; }

		inline float Abs(float value)
		{
			return std::fabs(value);
		}

		inline float Sqrt(float x)
		{
			return std::sqrt(x);
		}

		inline float Recip_Sqrt(float number)
		{
			return KlayGE::MathLib::recip_sqrt(number);
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
			return KlayGE::MathLib::cos(x);
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

		inline float Atan2(float y, float x)
		{
			return std::atan2(y, x);
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

		template<typename T>
		inline bool IsNaN(T x)
		{
			return std::isnan(x);
		}

		inline float Length(Vector3 const& rhs)
		{
			return KlayGE::MathLib::length(rhs);
		}
		
		// 2D 向量
		///////////////////////////////////////////////////////////////////////////////
		inline float Cross(Vector2 const& lhs, Vector2 const& rhs)
		{
			return KlayGE::MathLib::cross(lhs, rhs);
		}

		// 3D 向量
		///////////////////////////////////////////////////////////////////////////////
		inline Vector3 Cross(Vector3 const& lhs, Vector3 const& rhs)
		{
			return KlayGE::MathLib::cross(lhs, rhs);
		}

		inline Vector3 Normalize(Vector3 const& lhs)
		{
			return KlayGE::MathLib::normalize(lhs);
		}

		// 4D 矩阵
		///////////////////////////////////////////////////////////////////////////////

		//Matrix4_T<T> inverse(Matrix4_T<T> const & rhs) KLAYGE_NOEXCEPT;
		inline Matrix4 Inverse(Matrix4 const& rhs)
		{
			return KlayGE::MathLib::inverse(rhs);
		}

		inline Matrix4 LookAtLh(Vector3 const& vEye, Vector3 const& vAt, Vector3 const& vUp)
		{
			return KlayGE::MathLib::look_at_lh(vEye, vAt, vUp);
		}

		inline Matrix4 PerspectiveFovLh(float const& fov, float const& aspect, float const& nearPlane, float const& farPlane)
		{
			return KlayGE::MathLib::perspective_fov_lh(fov, aspect, nearPlane, farPlane);
		}


		inline Matrix4 Transpose(Matrix4 const & rhs)
		{
			return KlayGE::MathLib::transpose(rhs);
		}

		// Color
		///////////////////////////////////////////////////////////////////////////////
		//inline Color Black() {static Color color(0.0f, 0.0f, 0.0f, 1.0f); return color;}
		//inline Color White() { static Color color(1.0f, 1.0f, 1.0f, 1.0f); return color; }
		//inline Color Red() { static Color color(1.0f, 0.0f, 0.0f, 1.0f); return color;}
		//inline Color Green() {static Color color(1.0f, 1.0f, 0.0f, 1.0f); return color;}
		//inline Color Blue() {static Color color(0.0f, 0.0f, 1.0f, 1.0f); return color;}
		//inline Color Yellow() {static Color color(1.0f, 1.0f, 0.0f, 1.0f); return color;}
		//inline Color Cyan() {static Color color(0.0f, 1.0f, 1.0f, 1.0f); return color;}
		//inline Color Magenta() {static Color color(1.0f, 0.0f, 1.0f, 1.0f); return color;}
		//inline Color Silver() {static Color color(0.75f, 0.75f, 0.75f, 1.0f); return color;}
	}
}

#endif
