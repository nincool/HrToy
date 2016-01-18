/************************************************************************
*
* @Comment：引用自 KlayGE Matrix site:http://www.klayge.org/
* @Author: Hr
* @Date: [1/11/2016 By Hr]
*
************************************************************************/
#ifndef _MATRIX_T_H_
#define _MATRIX_T_H_

#include <boost/operators.hpp>
#include "Vector_T.h"

namespace Hr
{
	// 4D 矩阵
	///////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class Matrix4_T : boost::addable < Matrix4_T<T>,
		boost::subtractable < Matrix4_T<T>,
		boost::dividable2 < Matrix4_T<T>, T,
		boost::multipliable2 < Matrix4_T<T>, T,
		boost::multipliable < Matrix4_T<T>,
		boost::equality_comparable<Matrix4_T<T>> >> >> >
	{
		typedef T					value_type;

		typedef value_type*			pointer;
		typedef value_type const *	const_pointer;

		typedef value_type&			reference;
		typedef value_type const &	const_reference;

		typedef value_type*			iterator;
		typedef value_type const *	const_iterator;

		enum { row_num = 4, col_num = 4 };
		enum { elem_num = row_num * col_num };

	public:
		Matrix4_T() 
		{
		}
		explicit Matrix4_T(T const * rhs)
		{
			for (size_t i = 0; i < row_num; ++i)
			{
				m_[i] = Vector_T<T, col_num>(rhs);
				rhs += col_num;
			}
		}
		Matrix4_T(Matrix4_T&& rhs) : m_(std::move(rhs.m_))
		{
		}
		Matrix4_T(Matrix4_T const & rhs) : m_(rhs.m_)
		{
		}
		Matrix4_T(T f11, T f12, T f13, T f14,
			T f21, T f22, T f23, T f24,
			T f31, T f32, T f33, T f34,
			T f41, T f42, T f43, T f44)
		{
			m_[0][0] = f11;	m_[0][1] = f12;	m_[0][2] = f13;	m_[0][3] = f14;
			m_[1][0] = f21;	m_[1][1] = f22;	m_[1][2] = f23;	m_[1][3] = f24;
			m_[2][0] = f31;	m_[2][1] = f32;	m_[2][2] = f33;	m_[2][3] = f34;
			m_[3][0] = f41;	m_[3][1] = f42;	m_[3][2] = f43;	m_[3][3] = f44;
		}

		static size_t size() 
		{
			return elem_num;
		}

		Matrix4_T<T> const & Zero() 
		{
			static Matrix4_T const out(
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0);
			return out;
		}

		static Matrix4_T<T> const & Identity() 
		{
			static Matrix4_T const out(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
			return out;
		}

		reference operator()(size_t row, size_t col) 
		{
			return m_[row][col];
		}
		const_reference operator()(size_t row, size_t col) const 
		{
			return m_[row][col];
		}

		Vector_T<T, col_num>& operator[](size_t index)
		{
			return m_[index];
		}
		const Vector_T<T, col_num>& operator[](size_t index) const
		{
			return m_[index];
		}

		void Row(size_t index, Vector_T<T, col_num> const & rhs)
		{
			m_[index] = rhs;
		}
		Vector_T<T, 4> const & Row(size_t index) const
		{
			return m_[index];
		}
		void Col(size_t index, Vector_T<T, row_num> const & rhs)
		{
			for (size_t i = 0; i < row_num; ++i)
			{
				m_[i][index] = rhs[i];
			}
		}
		Vector_T<T, 4> const Col(size_t index) const
		{
			Vector_T<T, row_num> ret;
			for (size_t i = 0; i < row_num; ++i)
			{
				ret[i] = m_[i][index];
			}
			return ret;
		}

		// 赋值操作符
		Matrix4_T& operator+=(Matrix4_T const & rhs)
		{
			m_ += rhs.m_;
			return *this;
		}
		Matrix4_T& operator-=(Matrix4_T const & rhs)
		{
			m_ -= rhs.m_;
			return *this;
		}

		Matrix4_T Concatenate(const Matrix4_T &m2) const
		{
			Matrix4_T r;
			r[0][0] = m_[0][0] * m2[0][0] + m_[0][1] * m2[1][0] + m_[0][2] * m2[2][0] + m_[0][3] * m2[3][0];
			r[0][1] = m_[0][0] * m2[0][1] + m_[0][1] * m2[1][1] + m_[0][2] * m2[2][1] + m_[0][3] * m2[3][1];
			r[0][2] = m_[0][0] * m2[0][2] + m_[0][1] * m2[1][2] + m_[0][2] * m2[2][2] + m_[0][3] * m2[3][2];
			r[0][3] = m_[0][0] * m2[0][3] + m_[0][1] * m2[1][3] + m_[0][2] * m2[2][3] + m_[0][3] * m2[3][3];

			r[1][0] = m_[1][0] * m2[0][0] + m_[1][1] * m2[1][0] + m_[1][2] * m2[2][0] + m_[1][3] * m2[3][0];
			r[1][1] = m_[1][0] * m2[0][1] + m_[1][1] * m2[1][1] + m_[1][2] * m2[2][1] + m_[1][3] * m2[3][1];
			r[1][2] = m_[1][0] * m2[0][2] + m_[1][1] * m2[1][2] + m_[1][2] * m2[2][2] + m_[1][3] * m2[3][2];
			r[1][3] = m_[1][0] * m2[0][3] + m_[1][1] * m2[1][3] + m_[1][2] * m2[2][3] + m_[1][3] * m2[3][3];

			r[2][0] = m_[2][0] * m2[0][0] + m_[2][1] * m2[1][0] + m_[2][2] * m2[2][0] + m_[2][3] * m2[3][0];
			r[2][1] = m_[2][0] * m2[0][1] + m_[2][1] * m2[1][1] + m_[2][2] * m2[2][1] + m_[2][3] * m2[3][1];
			r[2][2] = m_[2][0] * m2[0][2] + m_[2][1] * m2[1][2] + m_[2][2] * m2[2][2] + m_[2][3] * m2[3][2];
			r[2][3] = m_[2][0] * m2[0][3] + m_[2][1] * m2[1][3] + m_[2][2] * m2[2][3] + m_[2][3] * m2[3][3];

			r[3][0] = m_[3][0] * m2[0][0] + m_[3][1] * m2[1][0] + m_[3][2] * m2[2][0] + m_[3][3] * m2[3][0];
			r[3][1] = m_[3][0] * m2[0][1] + m_[3][1] * m2[1][1] + m_[3][2] * m2[2][1] + m_[3][3] * m2[3][1];
			r[3][2] = m_[3][0] * m2[0][2] + m_[3][1] * m2[1][2] + m_[3][2] * m2[2][2] + m_[3][3] * m2[3][2];
			r[3][3] = m_[3][0] * m2[0][3] + m_[3][1] * m2[1][3] + m_[3][2] * m2[2][3] + m_[3][3] * m2[3][3];

			return r;
		}
		Matrix4_T& operator*=(Matrix4_T const & rhs)
		{
			*this = Concatenate(rhs);
			return *this;
		}
		Matrix4_T& operator*=(T rhs)
		{
			for (size_t i = 0; i < row_num; ++i)
			{
				m_[i] *= rhs;
			}
			return *this;
		}
		Matrix4_T& operator/=(T rhs)
		{
			return this->operator*=(1 / rhs);
		}

		Matrix4_T& operator=(Matrix4_T const & rhs)
		{
			if (this != &rhs)
			{
				m_ = rhs.m_;
			}
			return *this;
		}
		Matrix4_T& operator=(Matrix4_T&& rhs)
		{
			m_ = std::move(rhs.m_);
			return *this;
		}

		// 一元操作符
		Matrix4_T const operator+() const
		{
			return *this;
		}
		Matrix4_T const operator-() const
		{
			Matrix4_T temp(*this);
			temp.m_ = -m_;
			return temp;
		}

		bool operator==(Matrix4_T const & rhs) const
		{
			return m_ == rhs.m_;
		}

	private:
		Vector_T< Vector_T<T, col_num>, row_num> m_;
	};


}


#endif





