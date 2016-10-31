#ifndef _HR_VECTOR3_H_
#define _HR_VECTOR3_H_

#include "HrMathPrerequisites.h"
#include <boost/operators.hpp>
#include "HrMathCom.h"

namespace Hr
{
	class HrVector3 
	{
	public:
		HrVector3()
		{
		}
		HrVector3(const REAL fX, const REAL fY, const REAL fZ)
		{
			m_x = fX; m_y = fY; m_z = fZ;
		}

		HrVector3(HrVector3& v)
		{
			m_x = v.m_x; m_y = v.m_y; m_z = v.m_z;
		}

		HrVector3(HrVector3&& v)
		{
			m_x = v.m_x; m_y = v.m_y; m_z = v.m_z;
		}

		static HrVector3 const& Zero()
		{
			static HrVector3 const zero(0.0f, 0.0f, 0.0f);
			return zero;
		}

		inline REAL operator [] (const size_t i) const
		{
			BOOST_ASSERT(i < 3);

			return *(&m_x + i);
		}

		inline REAL& operator [] (const size_t i)
		{
			BOOST_ASSERT(i < 3);

			return *(&m_x + i);
		}

		inline HrVector3& operator += (const HrVector3& rkVector)
		{
			m_x += rkVector.m_x;
			m_y += rkVector.m_y;
			m_z += rkVector.m_z;

			return *this;
		}

		inline HrVector3& operator -= (const HrVector3& rkVector)
		{
			m_x -= rkVector.m_x;
			m_y -= rkVector.m_y;
			m_z -= rkVector.m_z;

			return *this;
		}

		inline HrVector3& operator -= (const REAL fScalar)
		{
			m_x -= fScalar;
			m_y -= fScalar;
			m_z -= fScalar;

			return *this;
		}

		inline HrVector3& operator *= (const REAL fScalar)
		{
			m_x *= fScalar;
			m_y *= fScalar;
			m_z *= fScalar;

			return *this;
		}

		inline HrVector3& operator *= (const HrVector3& rkVector)
		{
			m_x *= rkVector.m_x;
			m_y *= rkVector.m_y;
			m_z *= rkVector.m_z;

			return *this;
		}

		inline HrVector3 operator /= (const REAL fScalar)
		{
			BOOST_ASSERT(fScalar != 0.0);

			REAL fInv = 1.0f / fScalar;

			m_x *= fInv;
			m_y *= fInv;
			m_z *= fInv;

			return *this;
		}

		inline HrVector3 operator /= (const HrVector3& rkVector)
		{
			m_x /= rkVector.m_x;
			m_y /= rkVector.m_y;
			m_z /= rkVector.m_z;

			return *this;
		}

		inline HrVector3& operator = (const HrVector3& rkVector)
		{
			m_x = rkVector.m_x;
			m_y = rkVector.m_y;
			m_z = rkVector.m_z;

			return *this;
		}

		inline bool operator == (const HrVector3& rkVector) const
		{
			return (m_x == rkVector.m_x && m_y == rkVector.m_y && m_z == rkVector.m_z);
		}

		inline bool operator != (const HrVector3& rkVector) const
		{
			return (m_x != rkVector.m_x || m_y != rkVector.m_y || m_z != rkVector.m_z);
		}

		//arithmetic operations
		inline HrVector3 operator + (const HrVector3& rkVector) const
		{
			return HrVector3(
				m_x + rkVector.m_x,
				m_y + rkVector.m_y,
				m_z + rkVector.m_z);
		}

		inline HrVector3 operator - (const HrVector3& rkVector) const
		{
			return HrVector3(
				m_x - rkVector.m_x,
				m_y - rkVector.m_y,
				m_z - rkVector.m_z);
		}

		inline HrVector3 operator * (const REAL fScalar) const
		{
			return HrVector3(
				m_x * fScalar,
				m_y * fScalar,
				m_z * fScalar);
		}

		inline HrVector3 operator * (const HrVector3& rhs) const
		{
			return HrVector3(
				m_x * rhs.m_x,
				m_y * rhs.m_y,
				m_z * rhs.m_z);
		}

		inline HrVector3 operator / (const REAL fScalar) const
		{
			BOOST_ASSERT(fScalar != 0.0);
			REAL fInv = 1.0f / fScalar;

			return HrVector3(
				m_x * fInv,
				m_y * fInv,
				m_z * fInv);
		}

		inline HrVector3 operator / (const HrVector3& rhs) const
		{
			return HrVector3(
				m_x / rhs.m_x,
				m_y / rhs.m_y,
				m_z / rhs.m_z);
		}

		inline const HrVector3& operator + () const
		{
			return *this;
		}

		inline HrVector3 operator - () const
		{
			return HrVector3(-m_x, -m_y, -m_z);
		}



		/**
		 *	@Brief: Returns the length of the vector [12/8/2015 By Hr]
		 */
		inline REAL Length() const
		{
			return HrMath::Sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
		}

		/**
		 *	@Brief:  Returns the square of the vector  [12/8/2015 By Hr]
		 */
		inline REAL SquareLength() const
		{
			return m_x * m_x + m_y * m_y + m_z * m_z;
		}

		/**
		 *	@Brief:  Returns the distance to another vector.[12/8/2015 By Hr]
		 */
		inline REAL Distance(const HrVector3& rhs) const
		{
			return (*this - rhs).Length();
		}

		/**
		 *	@Brief:Returns the square of the distance to another vector.  [12/8/2015 By Hr]
		 */
		inline REAL SquareDistance(const HrVector3& rhs) const
		{
			return (*this - rhs).SquareLength();
		}

		/**
		 *	@Brief:Calculates the dot (scalar) product of this vector with another.  [12/8/2015 By Hr]
		 */
		inline REAL DotProduct(const HrVector3& vec) const
		{
			return m_x * vec.m_x + m_y * vec.m_y + m_z * vec.m_z;
		}

		/**
		 *	@Brief:  Calculates the cross-product of 2 vectors[12/8/2015 By Hr]
		 */
		inline HrVector3 CrossProduct(const HrVector3& rkVector) const
		{
			return HrVector3(
				m_y * rkVector.m_z - m_z * rkVector.m_y,
				m_z * rkVector.m_x - m_x * rkVector.m_z,
				m_x * rkVector.m_y - m_y * rkVector.m_x);
		}

		REAL x() const { return m_x; }
		REAL y() const { return m_y; }
		REAL z() const { return m_z; } 

		void x(REAL x) { m_x = x; }
		void y(REAL y) { m_y = y; }
		void z(REAL z) { m_z = z; }

	protected:
		REAL m_x;
		REAL m_y;
		REAL m_z;
	};
}

#endif