#ifndef _HR_MATHPREDECLARE_H_
#define _HR_MATHPREDECLARE_H_

#include "HrMath/Include/KFL/PreDeclare.hpp"
#include "HrMath/Include/HrMathConfig.h"

namespace Hr
{
#ifdef HR_MATH_SIMD
	//选定基本类型
	typedef KlayGE::float3 Vector3;
	typedef KlayGE::float4 Vector4;

	typedef Vector3 float3;
	typedef Vector4 float4;

	typedef KlayGE::float4x4 Matrix4;

	typedef KlayGE::Quaternion Quaternion;

#endif // HR_MATH_SIMD

	class Radian;
	class Degree;
}

#endif


