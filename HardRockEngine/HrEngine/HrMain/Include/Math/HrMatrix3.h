#ifndef _HR_MATRIX3_H_
#define _HR_MATRIX3_H_

#include "HrMainPrerequisiters.h"
#include "HrVector3.h"

namespace Hr
{
	class HR_MAIN_API HrMatrix3
	{
	public:
		inline HrMatrix3(){};
		inline explicit HrMatrix3(const REAL arr[3][3])
		{
			memcpy(m, arr, 9 * sizeof(REAL));
		}
		inline HrMatrix3(const HrMatrix3& rkMatrix)
		{
			memcpy(m, rkMatrix.m, 9 * sizeof(REAL));
		}
		HrMatrix3(REAL fEntry00, REAL fEntry01, REAL fEntry02,
			REAL fEntry10, REAL fEntry11, REAL fEntry12,
			REAL fEntry20, REAL fEntry21, REAL fEntry22)
		{
			m[0][0] = fEntry00;
			m[0][1] = fEntry01;
			m[0][2] = fEntry02;
			m[1][0] = fEntry10;
			m[1][1] = fEntry11;
			m[1][2] = fEntry12;
			m[2][0] = fEntry20;
			m[2][1] = fEntry21;
			m[2][2] = fEntry22;
		}

		inline void Swap(HrMatrix3& other)
		{
			std::swap(m[0][0], other.m[0][0]);
			std::swap(m[0][1], other.m[0][1]);
			std::swap(m[0][2], other.m[0][2]);
			std::swap(m[1][0], other.m[1][0]);
			std::swap(m[1][1], other.m[1][1]);
			std::swap(m[1][2], other.m[1][2]);
			std::swap(m[2][0], other.m[2][0]);
			std::swap(m[2][1], other.m[2][1]);
			std::swap(m[2][2], other.m[2][2]);
		}

		inline const REAL* operator[](size_t nRow) const
		{
			return m[nRow];
		}
		inline REAL* operator[] (size_t nRow)
		{
			return m[nRow];
		}

		/*inline operator Real* ()
		{
		return (Real*)m[0];
		}*/
		HrVector3 GetColumn(size_t nCol) const;
		void SetColumn(size_t nCol, const HrVector3& v3);
		void FromAxes(const HrVector3& xAxis, const HrVector3& yAxis, const HrVector3& zAxis);

		/// Assignment and comparison
		inline HrMatrix3& operator=(const HrMatrix3& rkMatrix)
		{
			memcpy(m, rkMatrix.m, 9 * sizeof(REAL));
			return *this;
		}
		bool operator== (const HrMatrix3& rkMatrix) const;

		inline bool operator!= (const HrMatrix3& rkMatrix) const
		{
			return !operator==(rkMatrix);
		}

		HrMatrix3 operator+ (const HrMatrix3& rkMatrix) const;
		HrMatrix3 operator- (const HrMatrix3& rkMatrix) const;
		HrMatrix3 operator* (const HrMatrix3& rkMatrix) const;
		HrMatrix3 operator- () const;
		
		HrVector3 operator* (const HrVector3& rkPoint) const;
		HrMatrix3 operator* (REAL fScalar) const;

		//Transpose
		HrMatrix3 Transpose() const;
		bool Inverse(HrMatrix3& rkInverse, REAL fTolerance = 1e-06) const;
		HrMatrix3 Inverse(REAL fTolerance = 1e-06) const;
		//Determinant
		REAL Determinant() const;

		inline HR_MAIN_API friend std::ostream& operator <<
			(std::ostream& o, const HrMatrix3& mat)
		{
			o << "Matrix3(" << mat[0][0] << ", " << mat[0][1] << ", " << mat[0][2] << ", "
				<< mat[1][0] << ", " << mat[1][1] << ", " << mat[1][2] << ", "
				<< mat[2][0] << ", " << mat[2][1] << ", " << mat[2][2] << ")";
			return o;
		}
	public:
		static const HrMatrix3 ZERO;
		static const HrMatrix3 IDENTITY;
	protected:
		REAL m[3][3];

	};
}

#endif

