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

		// 4D æÿ’Û
		///////////////////////////////////////////////////////////////////////////////
		//template <typename T>
		//Matrix4_T<T> mul(Matrix4_T<T> const & lhs, Matrix4_T<T> const & rhs) KLAYGE_NOEXCEPT;

		//template <typename T>
		//T determinant(Matrix4_T<T> const & rhs) KLAYGE_NOEXCEPT;

		//template <typename T>
		//Matrix4_T<T> inverse(Matrix4_T<T> const & rhs) KLAYGE_NOEXCEPT;

		inline Matrix4 Inverse(Matrix4 const& rhs)
		{
			return KlayGE::MathLib::inverse(rhs);
		}

		inline Matrix4 LookAtLh(Vector3 const& vEye, Vector3 const& vAt, Vector3 const& vUp)
		{
			return KlayGE::MathLib::look_at_lh(vEye, vAt, vUp);
		}

		//template <typename T>
		//Matrix4_T<T> look_at_rh(Vector_T<T, 3> const & vEye, Vector_T<T, 3> const & vAt) KLAYGE_NOEXCEPT;

		//template <typename T>
		//Matrix4_T<T> look_at_rh(Vector_T<T, 3> const & vEye, Vector_T<T, 3> const & vAt,
		//	Vector_T<T, 3> const & vUp) KLAYGE_NOEXCEPT;

		//template <typename T>
		//Matrix4_T<T> ortho_lh(T const & w, T const & h, T const & nearPlane, T const & farPlane) KLAYGE_NOEXCEPT;
		//template <typename T>
		//Matrix4_T<T> ortho_off_center_lh(T const & left, T const & right, T const & bottom, T const & top,
		//	T const & nearPlane, T const & farPlane) KLAYGE_NOEXCEPT;

		//template <typename T>
		//Matrix4_T<T> perspective_lh(T const & width, T const & height, T const & nearPlane, T const & farPlane) KLAYGE_NOEXCEPT;
		inline Matrix4 PerspectiveFovLh(float const& fov, float const& aspect, float const& nearPlane, float const& farPlane)
		{
			return KlayGE::MathLib::perspective_fov_lh(fov, aspect, nearPlane, farPlane);
		}
		//template <typename T>
		//Matrix4_T<T> perspective_fov_lh(T const & fov, T const & aspect, T const & nearPlane, T const & farPlane) KLAYGE_NOEXCEPT;
		//template <typename T>
		//Matrix4_T<T> perspective_off_center_lh(T const & left, T const & right, T const & bottom, T const & top,
		//	T const & nearPlane, T const & farPlane) KLAYGE_NOEXCEPT;

		//template <typename T>
		//Matrix4_T<T> reflect(Plane_T<T> const & p) KLAYGE_NOEXCEPT;

		//template <typename T>
		//Matrix4_T<T> rotation_x(T const & x) KLAYGE_NOEXCEPT;
		//template <typename T>
		//Matrix4_T<T> rotation_y(T const & y) KLAYGE_NOEXCEPT;
		//template <typename T>
		//Matrix4_T<T> rotation_z(T const & z) KLAYGE_NOEXCEPT;
		//template <typename T>
		//Matrix4_T<T> rotation(T const & angle, T const & x, T const & y, T const & z) KLAYGE_NOEXCEPT;
		//template <typename T>
		//Matrix4_T<T> rotation_matrix_yaw_pitch_roll(T const & yaw, T const & pitch, T const & roll) KLAYGE_NOEXCEPT;

		//template <typename T>
		//Matrix4_T<T> scaling(T const & sx, T const & sy, T const & sz) KLAYGE_NOEXCEPT;
		//template <typename T>
		//Matrix4_T<T> scaling(Vector_T<T, 3> const & s) KLAYGE_NOEXCEPT;

		//template <typename T>
		//Matrix4_T<T> shadow(Vector_T<T, 4> const & l, Plane_T<T> const & p) KLAYGE_NOEXCEPT;

		//template <typename T>
		//Matrix4_T<T> to_matrix(Quaternion_T<T> const & quat) KLAYGE_NOEXCEPT;

		//template <typename T>
		//Matrix4_T<T> translation(T const & x, T const & y, T const & z) KLAYGE_NOEXCEPT;
		//template <typename T>
		//Matrix4_T<T> translation(Vector_T<T, 3> const & pos) KLAYGE_NOEXCEPT;

		inline Matrix4 Transpose(Matrix4 const & rhs)
		{
			return KlayGE::MathLib::transpose(rhs);
		}

		//template <typename T>
		//Matrix4_T<T> lh_to_rh(Matrix4_T<T> const & rhs) KLAYGE_NOEXCEPT;

		//template <typename T>
		//void decompose(Vector_T<T, 3>& scale, Quaternion_T<T>& rot, Vector_T<T, 3>& trans, Matrix4_T<T> const & rhs) KLAYGE_NOEXCEPT;

		//template <typename T>
		//Matrix4_T<T> transformation(Vector_T<T, 3> const * scaling_center, Quaternion_T<T> const * scaling_rotation, Vector_T<T, 3> const * scale,
		//	Vector_T<T, 3> const * rotation_center, Quaternion_T<T> const * rotation, Vector_T<T, 3> const * trans) KLAYGE_NOEXCEPT;


		//template <typename T>
		//Matrix4_T<T> ortho_rh(T const & width, T const & height, T const & nearPlane, T const & farPlane) KLAYGE_NOEXCEPT;
		//template <typename T>
		//Matrix4_T<T> ortho_off_center_rh(T const & left, T const & right, T const & bottom, T const & top,
		//	T const & nearPlane, T const & farPlane) KLAYGE_NOEXCEPT;
		//template <typename T>
		//Matrix4_T<T> perspective_rh(T const & width, T const & height,
		//	T const & nearPlane, T const & farPlane) KLAYGE_NOEXCEPT;
		//template <typename T>
		//Matrix4_T<T> perspective_fov_rh(T const & fov, T const & aspect,
		//	T const & nearPlane, T const & farPlane) KLAYGE_NOEXCEPT;
		//template <typename T>
		//Matrix4_T<T> perspective_off_center_rh(T const & left, T const & right, T const & bottom, T const & top,
		//	T const & nearPlane, T const & farPlane) KLAYGE_NOEXCEPT;

		//template <typename T>
		//Matrix4_T<T> rh_to_lh(Matrix4_T<T> const & rhs) KLAYGE_NOEXCEPT;

		//template <typename T>
		//Matrix4_T<T> rotation_matrix_yaw_pitch_roll(Vector_T<T, 3> const & ang) KLAYGE_NOEXCEPT;

	}
}

#endif
