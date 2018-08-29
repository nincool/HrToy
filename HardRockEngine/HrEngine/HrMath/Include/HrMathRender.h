#ifndef _HR_MATHRENDER_H_
#define _HR_MATHRENDER_H_

#include "HrMathPrerequisites.h"
#include <cmath>

namespace Hr
{
	namespace HrMath
	{
		float const MAX_SHININESS = 8192;
		float const INV_LOG_MAX_SHININESS = 1 / log(MAX_SHININESS);

		inline float Shininess2Glossiness(float shininess)
		{
			return log(shininess) * INV_LOG_MAX_SHININESS;
		}

		inline float Glossiness2Shininess(float glossiness)
		{
			return pow(MAX_SHININESS, glossiness);
		}
	}
}

#endif
