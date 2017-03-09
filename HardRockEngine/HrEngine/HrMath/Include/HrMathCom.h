#ifndef _HR_MATHCOM_H_
#define _HR_MATHCOM_H_

#include "HrMathPrerequisites.h"
#include "HrMath/Include/HrColor.h"
#include <cmath>

namespace Hr
{
	namespace HrMath
	{
		inline float PI() { return KlayGE::PI; }
		inline float PI2() { return KlayGE::PIdiv2; }
		inline float DEG90() { return KlayGE::DEG90; }

		inline float DEG2RAD() {
			return KlayGE::DEG2RAD;
		}
		inline float RAD2DEG() {
			return KlayGE::RAD2DEG;
		}

		inline Vector3 Degree2Radian(const Vector3& angle)
		{
			return Vector3(angle * DEG2RAD());
		}

		inline Vector3 Radian2Degree(const Vector3& angle)
		{
			return Vector3(angle * RAD2DEG());
		}

		//求绝对值
		inline float Abs(float value)
		{
			return std::fabs(value);
		}
		//开方
		inline float Sqrt(float x)
		{
			return std::sqrt(x);
		}

		inline float Recip_Sqrt(float number)
		{
			return KlayGE::MathLib::recip_sqrt(number);
		}
		//平方
		inline float Pow(float x, float y)
		{
			return std::pow(x, y);
		}
		//e x
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

		// 取小于等于x的最大整数
		inline int Floor(float const & x)
		{
			return static_cast<int>(x > 0 ? x : (x - 1));
		}
		// 取整
		inline int Trunc(float const & x)
		{
			return static_cast<int>(x);
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

		inline bool IsPowerOfTwo(unsigned int n) { return ((n&(n - 1)) == 0); }

		// 2D 向量
		///////////////////////////////////////////////////////////////////////////////
		inline float Cross(Vector2 const& lhs, Vector2 const& rhs)
		{
			return KlayGE::MathLib::cross(lhs, rhs);
		}

		// 3D 向量
		///////////////////////////////////////////////////////////////////////////////
		inline float Length(Vector3 const& rhs)
		{
			return KlayGE::MathLib::length(rhs);
		}

		inline Vector3 Cross(Vector3 const& lhs, Vector3 const& rhs)
		{
			return KlayGE::MathLib::cross(lhs, rhs);
		}

		inline Vector3 Normalize(Vector3 const& lhs)
		{
			return KlayGE::MathLib::normalize(lhs);
		}

		//四元数
		inline Quaternion Normalize(Quaternion const& lhs)
		{
			return KlayGE::MathLib::normalize(lhs);
		}

		inline Matrix4 ToMatrix(Quaternion const& lhs)
		{
			return KlayGE::MathLib::to_matrix(lhs);
		}

		inline Quaternion RotationQuaternionYawPitchRoll(Vector3 const& angle)
		{
			return KlayGE::MathLib::rotation_quat_yaw_pitch_roll(angle);
		}

		inline Quaternion RotationQuaternionPitchYawRoll(Vector3 const& angle)
		{
			return KlayGE::MathLib::rotation_quat_yaw_pitch_roll(angle.y(), angle.x(), angle.z());
		}

		// 4D 矩阵
		///////////////////////////////////////////////////////////////////////////////

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

		inline Matrix4 Scaling(Vector3 const& scale)
		{
			return KlayGE::MathLib::scaling(scale);
		}

		inline Matrix4 Translation(Vector3 const& pos)
		{
			return KlayGE::MathLib::translation(pos);
		}

		inline Matrix4 MakeTransform(const Vector3& pos, const Vector3& scale, const Quaternion& orientation)
		{
			// Ordering:
			//    1. Scale
			//    2. Rotate
			//    3. Translate
			Matrix4 matTranslation = Translation(pos);
			Matrix4 matScale = Scaling(scale);
			Matrix4 matRotate = ToMatrix(orientation);

			return matScale * matRotate * matTranslation;
		}
		// Color
		///////////////////////////////////////////////////////////////////////////////
		inline HrColor MakeColor(uint8 r, uint8 g, uint8 b, uint8 a)
		{
			return HrColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
		}

		inline HrColor MakeColor(const std::vector<uint8>& rgba)
		{
			BOOST_ASSERT(rgba.size() == 4);
			return HrColor(rgba[0] / 255.0f, rgba[1] / 255.0f, rgba[2] / 255.0f, rgba[3] / 255.0f);
		}
	}
}

#endif


