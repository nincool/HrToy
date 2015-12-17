#ifndef _HR_MATH_H_
#define _HR_MATH_H_

#include "HrMainPrerequisiters.h"
#include <cmath>

namespace Hr
{
	class HrMath
	{
	public:
		inline HrMath(){};

		static inline REAL Sqrt(REAL fValue)
		{
			return REAL(std::sqrt(fValue));
		}

		/**
		 *	@Brief: Absolute value function [12/17/2015 By Hr]
		*/
		static inline REAL Abs(REAL fValue) { return REAL(std::fabs(fValue)); }
		
	};
}


#endif

