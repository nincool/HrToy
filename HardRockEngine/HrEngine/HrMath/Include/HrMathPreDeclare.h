#ifndef _HR_MATHPREDECLARE_H_
#define _HR_MATHPREDECLARE_H_

#include "HrMath/Include/KFL/PreDeclare.hpp"
#include "HrMath/Include/HrMathConfig.h"

namespace Hr
{
//#ifdef HR_MATH_SIMD
	//选定基本类型
	typedef KlayGE::float2 Vector2;
	typedef KlayGE::float3 Vector3;
	
	typedef KlayGE::float4 Vector4;
	

	typedef Vector2 float2;
	typedef Vector3 float4float3;
	typedef Vector4 float4;

	typedef KlayGE::float4x4 Matrix4;
	typedef KlayGE::float4x4 float4x4;

	typedef KlayGE::Quaternion Quaternion;

	typedef KlayGE::Color Color;

	typedef KlayGE::int1 int1;
	typedef KlayGE::int2 int2;
	typedef KlayGE::int3 int3;
	typedef KlayGE::int4 int4;
	typedef KlayGE::uint1 uint1;
	typedef KlayGE::uint2 uint2;
	typedef KlayGE::uint3 uint3;
	typedef KlayGE::uint4 uint4;
	typedef KlayGE::float1 float1;
	typedef KlayGE::float2 float2;
	typedef KlayGE::float3 float3;
	typedef KlayGE::float4 float4;

//#endif // HR_MATH_SIMD

	class Radian;
	class Degree;
}

#endif


