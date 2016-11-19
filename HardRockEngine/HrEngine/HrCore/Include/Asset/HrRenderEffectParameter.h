#ifndef _HR_RENDEREFFECTCONSTANTBUFFER_H_
#define _HR_RENDEREFFECTCONSTANTBUFFER_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	//by definition, will always use either float4 or int4 constant types since that is the fundamental underlying type in assembler. from ogre
	enum EnumRenderEffectDataType
	{
		REDT_FLOAT1 = 1,
		REDT_FLOAT2 = 2,
		REDT_FLOAT3 = 3,
		REDT_FLOAT4 = 4,
		REDT_SAMPLER1D = 5,
		REDT_SAMPLER2D = 6,
		REDT_SAMPLER3D = 7,
		REDT_SAMPLERCUBE = 8,
		REDT_SAMPLERRECT = 9,
		REDT_SAMPLER1DSHADOW = 10,
		REDT_SAMPLER2DSHADOW = 11,
		REDT_SAMPLER2DARRAY = 12,
		REDT_MATRIX_2X2 = 13,
		REDT_MATRIX_2X3 = 14,
		REDT_MATRIX_2X4 = 15,
		REDT_MATRIX_3X2 = 16,
		REDT_MATRIX_3X3 = 17,
		REDT_MATRIX_3X4 = 18,
		REDT_MATRIX_4X2 = 19,
		REDT_MATRIX_4X3 = 20,
		REDT_MATRIX_4X4 = 21,
		REDT_INT1 = 22,
		REDT_INT2 = 23,
		REDT_INT3 = 24,
		REDT_INT4 = 25,
		REDT_SUBROUTINE = 26,
		REDT_DOUBLE1 = 27,
		REDT_DOUBLE2 = 28,
		REDT_DOUBLE3 = 29,
		REDT_DOUBLE4 = 30,
		REDT_MATRIX_DOUBLE_2X2 = 31,
		REDT_MATRIX_DOUBLE_2X3 = 32,
		REDT_MATRIX_DOUBLE_2X4 = 33,
		REDT_MATRIX_DOUBLE_3X2 = 34,
		REDT_MATRIX_DOUBLE_3X3 = 35,
		REDT_MATRIX_DOUBLE_3X4 = 36,
		REDT_MATRIX_DOUBLE_4X2 = 37,
		REDT_MATRIX_DOUBLE_4X3 = 38,
		REDT_MATRIX_DOUBLE_4X4 = 39,
		REDT_UINT1 = 40,
		REDT_UINT2 = 41,
		REDT_UINT3 = 42,
		REDT_UINT4 = 43,
		REDT_BOOL1 = 44,
		REDT_BOOL2 = 45,
		REDT_BOOL3 = 46,
		REDT_BOOL4 = 47,
		REDT_SAMPLER_WRAPPER1D = 48,
		REDT_SAMPLER_WRAPPER2D = 49,
		REDT_SAMPLER_WRAPPER3D = 50,
		REDT_SAMPLER_WRAPPERCUBE = 51,
		REDT_SAMPLER_STATE = 52, //only for hlsl 4.0
		REDT_UNKNOWN = 99

	};

	class HrRenderEffectParameter : public boost::noncopyable
	{
	public:
		HrRenderEffectParameter();
		~HrRenderEffectParameter();

	private:

	};

	class HrRenderEffectConstantBuffer : public boost::noncopyable
	{
	public:
		HrRenderEffectConstantBuffer();
		~HrRenderEffectConstantBuffer();

		
	private:
		HrGraphicsBuffer* m_pConstantBuffer;
	};
}

#endif



