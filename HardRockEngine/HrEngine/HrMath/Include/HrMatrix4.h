#ifndef _HR_MATRIX4_H_
#define _HR_MATRIX4_H_

#include "HrMathPrerequisites.h"
#include "HrVector3.h"

namespace Hr
{
	class HrMatrix4 
	{
		typedef REAL				value_type;

		typedef value_type*			pointer;
		typedef value_type const *	const_pointer;

		typedef value_type&			reference;
		typedef value_type const &	const_reference;

		typedef value_type*			iterator;
		typedef value_type const *	const_iterator;

		enum { row_num = 4, col_num = 4 };
		enum { elem_num = row_num * col_num };
	public:
		inline HrMatrix4()
		{
			memset(_m, 0, sizeof(_m));
		};
		explicit HrMatrix4( const REAL * rhs)
		{
			for (size_t i = 0; i < row_num * col_num; ++i)
			{
				_m[i] = *(rhs + i);
			}
		}
		HrMatrix4(HrMatrix4&& rhs)
		{
			memcpy(_m, rhs._m, sizeof(_m));
		}
		HrMatrix4(HrMatrix4 const & rhs)
		{
			memcpy(_m, rhs._m, sizeof(_m));
		}
		inline HrMatrix4(
			REAL m00, REAL m01, REAL m02, REAL m03,
			REAL m10, REAL m11, REAL m12, REAL m13,
			REAL m20, REAL m21, REAL m22, REAL m23,
			REAL m30, REAL m31, REAL m32, REAL m33)
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[0][3] = m03;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[1][3] = m13;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
			m[2][3] = m23;
			m[3][0] = m30;
			m[3][1] = m31;
			m[3][2] = m32;
			m[3][3] = m33;
		}

		static size_t size()
		{
			return elem_num;
		}

		static HrMatrix4 const & Zero()
		{
			static HrMatrix4 const out(
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0);
			return out;
		}
		static HrMatrix4 const & Identity()
		{
			static HrMatrix4 const out(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
			return out;
		}

		void Row(size_t index, HrVector3 const & rhs)
		{
			for (size_t i = index * elem_num, j = 0; i < (index + 1) * elem_num; ++i, ++j)
			{
				_m[i] = rhs[j];
			}
		}
		HrVector3 const Row(size_t index) const
		{
			BOOST_ASSERT(index < row_num);
			size_t nStartIndex = index * col_num;
			return HrVector3(_m[nStartIndex], _m[nStartIndex + 1], _m[nStartIndex + 2]);
		}

		void Col(size_t index, HrVector3 const & rhs)
		{
			_m[index] = rhs.x();
			_m[index + col_num] = rhs.y();
			_m[index + col_num * 2] = rhs.z();
		}
		HrVector3 const Col(size_t index) const
		{
			return HrVector3(_m[index], _m[index + col_num], _m[index + col_num * 2]);
		}

		HrMatrix4 Concatenate(const HrMatrix4 &m2) const
		{
			HrMatrix4 r;
			r.m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0] + m[0][3] * m2.m[3][0];
			r.m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1] + m[0][3] * m2.m[3][1];
			r.m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2] + m[0][3] * m2.m[3][2];
			r.m[0][3] = m[0][0] * m2.m[0][3] + m[0][1] * m2.m[1][3] + m[0][2] * m2.m[2][3] + m[0][3] * m2.m[3][3];

			r.m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0] + m[1][3] * m2.m[3][0];
			r.m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1] + m[1][3] * m2.m[3][1];
			r.m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2] + m[1][3] * m2.m[3][2];
			r.m[1][3] = m[1][0] * m2.m[0][3] + m[1][1] * m2.m[1][3] + m[1][2] * m2.m[2][3] + m[1][3] * m2.m[3][3];

			r.m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0] + m[2][3] * m2.m[3][0];
			r.m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1] + m[2][3] * m2.m[3][1];
			r.m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2] + m[2][3] * m2.m[3][2];
			r.m[2][3] = m[2][0] * m2.m[0][3] + m[2][1] * m2.m[1][3] + m[2][2] * m2.m[2][3] + m[2][3] * m2.m[3][3];

			r.m[3][0] = m[3][0] * m2.m[0][0] + m[3][1] * m2.m[1][0] + m[3][2] * m2.m[2][0] + m[3][3] * m2.m[3][0];
			r.m[3][1] = m[3][0] * m2.m[0][1] + m[3][1] * m2.m[1][1] + m[3][2] * m2.m[2][1] + m[3][3] * m2.m[3][1];
			r.m[3][2] = m[3][0] * m2.m[0][2] + m[3][1] * m2.m[1][2] + m[3][2] * m2.m[2][2] + m[3][3] * m2.m[3][2];
			r.m[3][3] = m[3][0] * m2.m[0][3] + m[3][1] * m2.m[1][3] + m[3][2] * m2.m[2][3] + m[3][3] * m2.m[3][3];

			return r;
		}

		reference operator()(size_t row, size_t col) 
		{
			return _m[row * col_num + col];
		}
		const_reference operator()(size_t row, size_t col) const 
		{
			return _m[row * col_num + col];
		}
		
		inline REAL* operator [] (size_t iRow)
		{
			BOOST_ASSERT(iRow < 4);
			return m[iRow];
		}
		inline const REAL *operator [] (size_t iRow) const
		{
			BOOST_ASSERT(iRow < 4);
			return m[iRow];
		}

		/** Matrix addition.
		*/
		HrMatrix4 operator + (const HrMatrix4 &m2) const
		{
			HrMatrix4 r;

			r.m[0][0] = m[0][0] + m2.m[0][0];
			r.m[0][1] = m[0][1] + m2.m[0][1];
			r.m[0][2] = m[0][2] + m2.m[0][2];
			r.m[0][3] = m[0][3] + m2.m[0][3];

			r.m[1][0] = m[1][0] + m2.m[1][0];
			r.m[1][1] = m[1][1] + m2.m[1][1];
			r.m[1][2] = m[1][2] + m2.m[1][2];
			r.m[1][3] = m[1][3] + m2.m[1][3];

			r.m[2][0] = m[2][0] + m2.m[2][0];
			r.m[2][1] = m[2][1] + m2.m[2][1];
			r.m[2][2] = m[2][2] + m2.m[2][2];
			r.m[2][3] = m[2][3] + m2.m[2][3];

			r.m[3][0] = m[3][0] + m2.m[3][0];
			r.m[3][1] = m[3][1] + m2.m[3][1];
			r.m[3][2] = m[3][2] + m2.m[3][2];
			r.m[3][3] = m[3][3] + m2.m[3][3];

			return r;
		}

		/** Matrix subtraction.
		*/
		inline HrMatrix4 operator - (const HrMatrix4 &m2) const
		{
			HrMatrix4 r;
			r.m[0][0] = m[0][0] - m2.m[0][0];
			r.m[0][1] = m[0][1] - m2.m[0][1];
			r.m[0][2] = m[0][2] - m2.m[0][2];
			r.m[0][3] = m[0][3] - m2.m[0][3];

			r.m[1][0] = m[1][0] - m2.m[1][0];
			r.m[1][1] = m[1][1] - m2.m[1][1];
			r.m[1][2] = m[1][2] - m2.m[1][2];
			r.m[1][3] = m[1][3] - m2.m[1][3];

			r.m[2][0] = m[2][0] - m2.m[2][0];
			r.m[2][1] = m[2][1] - m2.m[2][1];
			r.m[2][2] = m[2][2] - m2.m[2][2];
			r.m[2][3] = m[2][3] - m2.m[2][3];

			r.m[3][0] = m[3][0] - m2.m[3][0];
			r.m[3][1] = m[3][1] - m2.m[3][1];
			r.m[3][2] = m[3][2] - m2.m[3][2];
			r.m[3][3] = m[3][3] - m2.m[3][3];

			return r;
		}

		HrMatrix4 operator* (const HrMatrix4& rhs) const
		{
			return this->Concatenate(rhs);
		}

		HrMatrix4& operator*=(HrMatrix4 const & rhs)
		{
			*this = Concatenate(rhs);
			return *this;
		}

		HrMatrix4& operator*=(REAL rhs)
		{
			for (size_t i = 0; i < row_num; ++i)
			{
				_m[i] *= rhs;
			}
			return *this;
		}

		HrMatrix4& operator/=(REAL rhs)
		{
			return this->operator*=(1 / rhs);
		}

		HrMatrix4& operator=(HrMatrix4 const & rhs)
		{
			if (this != &rhs)
			{
				memcpy(_m, rhs._m, sizeof(_m));
			}
			return *this;
		}
		HrMatrix4& operator=(HrMatrix4&& rhs)
		{
			if (this != &rhs)
			{
				memcpy(_m, rhs._m, sizeof(_m));
			}
			return *this;
		}

		inline bool operator == (const HrMatrix4& m2) const
		{
			if (
				m[0][0] != m2.m[0][0] || m[0][1] != m2.m[0][1] || m[0][2] != m2.m[0][2] || m[0][3] != m2.m[0][3] ||
				m[1][0] != m2.m[1][0] || m[1][1] != m2.m[1][1] || m[1][2] != m2.m[1][2] || m[1][3] != m2.m[1][3] ||
				m[2][0] != m2.m[2][0] || m[2][1] != m2.m[2][1] || m[2][2] != m2.m[2][2] || m[2][3] != m2.m[2][3] ||
				m[3][0] != m2.m[3][0] || m[3][1] != m2.m[3][1] || m[3][2] != m2.m[3][2] || m[3][3] != m2.m[3][3])
				return false;
			return true;
		}

		/** Matrix concatenation using '*'.
		*/
		//HrMatrix4& operator+=(HrMatrix4 const & rhs)
		//{
		//	for (size_t i = 0; i < col_num * row_num; ++i)
		//	{
		//		_m[i] += rhs[i];
		//	}
		//	return *this;
		//}

		//HrMatrix4& operator-=(HrMatrix4 const & rhs)
		//{
		//	return *this;
		//}


	protected:
		/// The matrix entries, indexed by [row][col].
		union {
			REAL m[4][4];
			REAL _m[16];
		};
	};
}

#endif

