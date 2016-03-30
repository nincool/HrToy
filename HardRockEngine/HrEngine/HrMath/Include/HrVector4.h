#ifndef _HR_VECTOR4_H_
#define _HR_VECTOR4_H_

#include "HrMathPrerequisites.h"
#include <boost/operators.hpp>
#include "HrMathCom.h"

namespace Hr
{
	class HrVector4
	{
	public:
		HrVector4()
		{
		}
		HrVector4(const REAL fX, const REAL fY, const REAL fZ, const REAL fW)
		{
			m_x = fX; m_y = fY; m_z = fZ; m_w = fW;
		}
		HrVector4(HrVector4& v)
		{
			m_x = v.m_x; m_y = v.m_y; m_z = v.m_z; m_w = v.m_w;
		}
		HrVector4(const HrVector4& v)
		{
			m_x = v.m_x; m_y = v.m_y; m_z = v.m_z; m_w = v.m_w;
		}
		HrVector4(HrVector4&& v)
		{
			m_x = v.m_x; m_y = v.m_y; m_z = v.m_z; m_w = v.m_w;
		}

		static HrVector4 const& Zero()
		{
			static HrVector4 const zero(0.0f, 0.0f, 0.0f, 0.0f);
			return zero;
		}

		inline REAL operator [] (const size_t i) const
		{
			BOOST_ASSERT(i < 4);

			return *(&m_x + i);
		}

		inline REAL& operator [] (const size_t i)
		{
			BOOST_ASSERT(i < 4);

			return *(&m_x + i);
		}

		inline HrVector4& operator += (const HrVector4& rkVector)
		{
			m_x += rkVector.m_x;
			m_y += rkVector.m_y;
			m_z += rkVector.m_z;
			m_w += rkVector.m_w;

			return *this;
		}

		inline HrVector4& operator -= (const HrVector4& rkVector)
		{
			m_x -= rkVector.m_x;
			m_y -= rkVector.m_y;
			m_z -= rkVector.m_z;
			m_w -= rkVector.m_w;

			return *this;
		}

		inline HrVector4& operator -= (const REAL fScalar)
		{
			m_x -= fScalar;
			m_y -= fScalar;
			m_z -= fScalar;
			m_w -= fScalar;

			return *this;
		}

		inline HrVector4& operator *= (const REAL fScalar)
		{
			m_x *= fScalar;
			m_y *= fScalar;
			m_z *= fScalar;
			m_w *= fScalar;

			return *this;
		}

		inline HrVector4& operator *= (const HrVector4& rkVector)
		{
			m_x *= rkVector.m_x;
			m_y *= rkVector.m_y;
			m_z *= rkVector.m_z;
			m_w *= rkVector.m_w;

			return *this;
		}

		inline HrVector4 operator /= (const REAL fScalar)
		{
			BOOST_ASSERT(fScalar != 0.0);

			REAL fInv = 1.0f / fScalar;

			m_x *= fInv;
			m_y *= fInv;
			m_z *= fInv;
			m_w *= fInv;

			return *this;
		}

		inline HrVector4 operator /= (const HrVector4& rkVector)
		{
			m_x /= rkVector.m_x;
			m_y /= rkVector.m_y;
			m_z /= rkVector.m_z;
			m_w /= rkVector.m_w;

			return *this;
		}

		inline HrVector4& operator = (const HrVector4& rkVector)
		{
			m_x = rkVector.m_x;
			m_y = rkVector.m_y;
			m_z = rkVector.m_z;
			m_w = rkVector.m_w;

			return *this;
		}

		inline bool operator == (const HrVector4& rkVector) const
		{
			return (m_x == rkVector.m_x && m_y == rkVector.m_y && m_z == rkVector.m_z && m_w == rkVector.m_w);
		}

		inline bool operator != (const HrVector4& rkVector) const
		{
			return (m_x != rkVector.m_x || m_y != rkVector.m_y || m_z != rkVector.m_z && m_w == rkVector.m_w);
		}

		//arithmetic operations
		inline HrVector4 operator + (const HrVector4& rkVector) const
		{
			return HrVector4(
				m_x + rkVector.m_x,
				m_y + rkVector.m_y,
				m_z + rkVector.m_z,
				m_w + rkVector.m_w);
		}

		inline HrVector4 operator - (const HrVector4& rkVector) const
		{
			return HrVector4(
				m_x - rkVector.m_x,
				m_y - rkVector.m_y,
				m_z - rkVector.m_z,
				m_w - rkVector.m_w);
		}

		inline HrVector4 operator * (const REAL fScalar) const
		{
			return HrVector4(
				m_x * fScalar,
				m_y * fScalar,
				m_z * fScalar,
				m_w * fScalar);
		}

		inline HrVector4 operator * (const HrVector4& rhs) const
		{
			return HrVector4(
				m_x * rhs.m_x,
				m_y * rhs.m_y,
				m_z * rhs.m_z,
				m_w * rhs.m_w);
		}

		inline HrVector4 operator / (const REAL fScalar) const
		{
			BOOST_ASSERT(fScalar != 0.0);
			REAL fInv = 1.0f / fScalar;

			return HrVector4(
				m_x * fInv,
				m_y * fInv,
				m_z * fInv,
				m_w * fInv);
		}

		inline HrVector4 operator / (const HrVector4& rhs) const
		{
			return HrVector4(
				m_x / rhs.m_x,
				m_y / rhs.m_y,
				m_z / rhs.m_z,
				m_w / rhs.m_w);
		}

		inline const HrVector4& operator + () const
		{
			return *this;
		}

		inline HrVector4 operator - () const
		{
			return HrVector4(-m_x, -m_y, -m_z, -m_w);
		}



		/**
		 *	@Brief: Returns the length of the vector [12/8/2015 By Hr]
		 */
		inline REAL Length() const
		{
			return HrMath::Sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
		}

		/**
		 *	@Brief:  Returns the square of the vector  [12/8/2015 By Hr]
		 */
		inline REAL SquareLength() const
		{
			return m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w;
		}

		/**
		 *	@Brief:  Returns the distance to another vector.[12/8/2015 By Hr]
		 */
		inline REAL Distance(const HrVector4& rhs) const
		{
			return (*this - rhs).Length();
		}

		/**
		 *	@Brief:Returns the square of the distance to another vector.  [12/8/2015 By Hr]
		 */
		inline REAL SquareDistance(const HrVector4& rhs) const
		{
			return (*this - rhs).SquareLength();
		}

		/**
		 *	@Brief:Calculates the dot (scalar) product of this vector with another.  [12/8/2015 By Hr]
		 */
		inline REAL DotProduct(const HrVector4& vec) const
		{
			return m_x * vec.m_x + m_y * vec.m_y + m_z * vec.m_z + m_w * vec.m_w;
		}

		REAL x() const { return m_x; }
		REAL y() const { return m_y; }
		REAL z() const { return m_z; } 
		REAL w() const { return m_w; }

		protected:
			REAL m_x;
			REAL m_y;
			REAL m_z;
			REAL m_w;
	};
}

#endif