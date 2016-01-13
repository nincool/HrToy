/************************************************************************
*
* @Comment：引用自 KlayGE Plane_T site:http://www.klayge.org/
*	        描述一个平面 ax + by + cz + d = 0
* @Author: Hr
* @Date: [1/11/2016 By Hr]
*
************************************************************************/  
#ifndef _PLANE_T_H_
#define _PLANE_T_H_

#include <boost/operators.hpp>
#include "Vector_T.h"

namespace Hr
{
	template <typename T>
	class Plane_T : boost::equality_comparable < Plane_T<T> >
	{
	public:
		enum { elem_num = 4 };

		typedef T value_type;

		typedef typename Vector_T<T, elem_num>::pointer pointer;
		typedef typename Vector_T<T, elem_num>::const_pointer const_pointer;

		typedef typename Vector_T<T, elem_num>::reference reference;
		typedef typename Vector_T<T, elem_num>::const_reference const_reference;

		typedef typename Vector_T<T, elem_num>::iterator iterator;
		typedef typename Vector_T<T, elem_num>::const_iterator const_iterator;
	public:
		Plane_T() 
		{
		}
		explicit Plane_T(T const * rhs) : plane_(rhs)
		{
		}

		Plane_T(Plane_T const & rhs) : plane_(rhs.plane_)
		{
		}

		Plane_T(Plane_T&& rhs) : plane_(std::move(rhs.plane_))
		{
		}

		Plane_T(Vector_T<T, elem_num> const & rhs) : plane_(rhs)
		{
		}

		Plane_T(Vector_T<T, elem_num>&& rhs) : plane_(rhs)
		{
		}

		Plane_T(T a, T b, T c, T d)
		{
			this->a() = a;
			this->b() = b;
			this->c() = c;
			this->d() = d;
		}

		// 取向量
		iterator Begin() 
		{
			return plane_.begin();
		}
		const_iterator Begin() const 
		{
			return plane_.begin();
		}
		iterator End() 
		{
			return plane_.end();
		}
		const_iterator End() const 
		{
			return plane_.end();
		}
		reference operator[](size_t index) 
		{
			return plane_[index];
		}
		const_reference operator[](size_t index) const 
		{
			return plane_[index];
		}

		reference a() 
		{
			return plane_[0];
		}
		const_reference a() const 
		{
			return plane_[0];
		}
		reference b() 
		{
			return plane_[1];
		}
		const_reference b() const 
		{
			return plane_[1];
		}
		reference c() 
		{
			return plane_[2];
		}
		const_reference c() const 
		{
			return plane_[2];
		}
		reference d() 
		{
			return plane_[3];
		}
		const_reference d() const 
		{
			return plane_[3];
		}

			// 赋值操作符
		Plane_T& operator=(Plane_T const & rhs)
		{
			if (this != &rhs)
			{
				plane_ = rhs.plane_;
			}
			return *this;
		}
		Plane_T& operator=(Plane_T&& rhs)
		{
			plane_ = std::move(rhs.plane_);
			return *this;
		}
		Plane_T& operator=(Vector_T<T, elem_num> const & rhs)
		{
			plane_ = rhs;
			return *this;
		}
		Plane_T& operator=(Vector_T<T, elem_num>&& rhs)
		{
			plane_ = std::move(rhs);
			return *this;
		}

		// 一元操作符
		Plane_T const operator+() const
		{
			return *this;
		}
		Plane_T const operator-() const
		{
			return Plane_T<T>(-this->a(), -this->b(), -this->c(), -this->d());
		}

		// 取法向向量
		Vector_T<T, 3> const Normal() const
		{
			return Vector_T<T, 3>(this->a(), this->b(), this->c());
		}
		void Normal(Vector_T<T, 3> const & rhs)
		{
			this->a() = rhs.x();
			this->b() = rhs.y();
			this->c() = rhs.z();
		}

		bool operator==(Plane_T<T> const & rhs) const
		{
			return plane_ = rhs.plane_;
		}
	private:
		Vector_T<T, elem_num> plane_;
	};
}

#endif