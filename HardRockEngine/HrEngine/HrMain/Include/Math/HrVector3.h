#ifndef _HR_VECTOR3_H_
#define _HR_VECTOR3_H_

#include "HrMainPrerequisiters.h"
#include "HrMath.h"

namespace Hr
{
	class HR_MAIN_API HrVector3
	{
	public:
		inline HrVector3(){}
		inline HrVector3(const REAL fX, const REAL fY, const REAL fZ)
			: x(fX), y(fY), z(fZ)
		{}

		inline void Swap(HrVector3& other)
		{
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
		}

		inline REAL operator [] (const size_t i) const
		{
			assert(i < 3);
			
			return *(&x + i);
		}

		inline REAL& operator [] (const size_t i) 
		{
			assert(i < 3);

			return *(&x + i);
		}

		inline HrVector3& operator = (const HrVector3& rkVector)
		{
			x = rkVector.x;
			y = rkVector.y;
			z = rkVector.z;

			return *this;
		}

		inline bool operator == (const HrVector3& rkVector) const
		{
			return (x == rkVector.x && y == rkVector.y && z == rkVector.z);
		}

		inline bool operator != (const HrVector3& rkVector) const
		{
			return (x != rkVector.x || y != rkVector.y || z != rkVector.z);
		}

		//arithmetic operations
		inline HrVector3 operator + (const HrVector3& rkVector) const
		{
			return HrVector3(
				x + rkVector.x,
				y + rkVector.y,
				z + rkVector.z);
		}

		inline HrVector3 operator - (const HrVector3& rkVector) const
		{
			return HrVector3(
				x - rkVector.x,
				y - rkVector.y,
				z - rkVector.z);
		}

		inline HrVector3 operator * (const REAL fScalar) const
		{
			return HrVector3(
				x * fScalar,
				y * fScalar,
				z * fScalar);
		}

		inline HrVector3 operator * (const HrVector3& rhs) const
		{
			return HrVector3(
				x * rhs.x,
				y * rhs.y,
				z * rhs.z);
		}

		inline HrVector3 operator / (const REAL fScalar) const
		{
			assert(fScalar != 0.0);
			REAL fInv = 1.0f / fScalar;
			
			return HrVector3(
				x * fInv,
				y * fInv,
				z * fInv);
		}

		inline HrVector3 operator / (const HrVector3& rhs) const
		{
			return HrVector3(
				x / rhs.x,
				y / rhs.y,
				z / rhs.z);
		}

		inline const HrVector3& operator + () const
		{
			return *this;
		}

		inline HrVector3 operator - () const
		{
			return HrVector3(-x, -y, -z);
		}

		inline HrVector3& operator += (const HrVector3& rkVector)
		{
			x += rkVector.x;
			y += rkVector.y;
			z += rkVector.z;

			return *this;
		}

		inline HrVector3& operator -= (const HrVector3& rkVector)
		{
			x -= rkVector.x;
			y -= rkVector.y;
			z -= rkVector.z;

			return *this;
		}

		inline HrVector3& operator -= (const REAL fScalar)
		{
			x -= fScalar;
			y -= fScalar;
			z -= fScalar;

			return *this;
		}

		inline HrVector3& operator *= (const REAL fScalar)
		{
			x *= fScalar;
			y *= fScalar;
			z *= fScalar;

			return *this;
		}

		inline HrVector3& operator *= (const HrVector3& rkVector)
		{
			x *= rkVector.x;
			y *= rkVector.y;
			z *= rkVector.z;

			return *this;
		}

		inline HrVector3 operator /= (const REAL fScalar)
		{
			assert(fScalar != 0.0);
			
			REAL fInv = 1.0f / fScalar;

			x *= fInv;
			y *= fInv;
			z *= fInv;

			return *this;
		}

		inline HrVector3 operator /= (const HrVector3& rkVector)
		{
			x /= rkVector.x;
			y /= rkVector.y;
			z /= rkVector.z;

			return *this;
		}

		/**
		 *	@Brief: Returns the length of the vector [12/8/2015 By Hr]
		*/
		inline REAL Length() const
		{
			return HrMath::Sqrt(x * x + y * y + z * z);
		}

		/**
		 *	@Brief:  Returns the square of the vector  [12/8/2015 By Hr]
		*/
		inline REAL SquareLength() const
		{
			return x * x + y * y + z * z;
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
			return x * vec.x + y * vec.y + z * vec.z;
		}

		/**
		 *	@Brief:  Calculates the cross-product of 2 vectors[12/8/2015 By Hr]
		*/
		inline HrVector3 CrossProduct(const HrVector3& rkVector) const
		{
			return HrVector3(
				y * rkVector.z - z * rkVector.y,
				z * rkVector.x - x * rkVector.z,
				x * rkVector.y - y * rkVector.x);
		}

		inline REAL Normalise()
		{
			REAL fLength = HrMath::Sqrt(x * x + y * y + z * z);

			if (fLength > REAL(0.0f))
			{
				REAL fInvLength = 1.0f / fLength;
				x *= fInvLength;
				y *= fInvLength;
				z *= fInvLength;
			}

			return fLength;
		}

	public:
		REAL x, y, z;

		static const HrVector3 ZERO;
		static const HrVector3 UNIT_X;
		static const HrVector3 UNIT_Y;
		static const HrVector3 UNIT_Z;
		static const HrVector3 NEGATIVE_UNIT_X;
		static const HrVector3 NEGATIVE_UNIT_Y;
		static const HrVector3 NEGATIVE_UNIT_Z;
		static const HrVector3 UNIT_SCALE;

	};
}

#endif

