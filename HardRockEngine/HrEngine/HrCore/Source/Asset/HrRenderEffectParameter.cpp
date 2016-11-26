#include "Asset/HrRenderEffectParameter.h"
#include "Asset/HrStreamData.h"
#include "Kernel/HrDirector.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrGraphicsBuffer.h"

using namespace Hr;

std::vector<HrRenderParamDefine> HrRenderParamDefine::m_s_vecRenderParamDefine =
{
	HrRenderParamDefine(RPT_WORLDVIEWPROJ_MATRIX, "worldviewproj_matrix", REDT_MATRIX_4X4, 16)
};

//////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////

HrRenderVariable::HrRenderVariable()
	:m_pData(nullptr), m_dataType(REDT_FLOAT1), m_semantic(RS_UNKNOW), m_nBufferOffset(0), m_nStride(0)
{
}

HrRenderVariable::~HrRenderVariable()
{
}

HrRenderVariable& HrRenderVariable::operator=(bool const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(uint32_t const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(int32_t const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(float const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(uint2 const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(uint3 const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(uint4 const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(int2 const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(int3 const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(int4 const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(float2 const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(float3 const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(float4 const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(float4x4 const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

//HrRenderVariable& HrRenderVariable::operator=(TexturePtr const & /*value*/)
//{
//	BOOST_ASSERT(false);
//	return *this;
//}
//
//HrRenderVariable& HrRenderVariable::operator=(TextureSubresource const & /*value*/)
//{
//	BOOST_ASSERT(false);
//	return *this;
//}
//
//HrRenderVariable& HrRenderVariable::operator=(SamplerStateObjectPtr const & /*value*/)
//{
//	BOOST_ASSERT(false);
//	return *this;
//}
//
//HrRenderVariable& HrRenderVariable::operator=(GraphicsBufferPtr const & /*value*/)
//{
//	BOOST_ASSERT(false);
//	return *this;
//}

HrRenderVariable& HrRenderVariable::operator=(std::string const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

//HrRenderVariable& HrRenderVariable::operator=(ShaderDesc const & /*value*/)
//{
//	BOOST_ASSERT(false);
//	return *this;
//}

HrRenderVariable& HrRenderVariable::operator=(std::vector<bool> const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(std::vector<uint32_t> const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(std::vector<int32_t> const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(std::vector<float> const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(std::vector<uint2> const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(std::vector<uint3> const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(std::vector<uint4> const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(std::vector<int2> const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(std::vector<int3> const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(std::vector<int4> const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(std::vector<float2> const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(std::vector<float3> const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(std::vector<float4> const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(std::vector<float4x4> const & /*value*/)
{
	BOOST_ASSERT(false);
	return *this;
}

void HrRenderVariable::Value(bool& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(uint32_t& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(int32_t& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(float& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(uint2& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(uint3& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(uint4& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(int2& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(int3& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(int4& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(float2& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(float3& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(float4& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(float4x4& /*value*/) const
{
	BOOST_ASSERT(false);
}

//void HrRenderVariable::Value(TexturePtr& /*value*/) const
//{
//	BOOST_ASSERT(false);
//}
//
//void HrRenderVariable::Value(TextureSubresource& /*value*/) const
//{
//	BOOST_ASSERT(false);
//}
//
//void HrRenderVariable::Value(SamplerStateObjectPtr& /*value*/) const
//{
//	BOOST_ASSERT(false);
//}
//
//void HrRenderVariable::Value(GraphicsBufferPtr& /*value*/) const
//{
//	BOOST_ASSERT(false);
//}

void HrRenderVariable::Value(std::string& /*value*/) const
{
	BOOST_ASSERT(false);
}

//void HrRenderVariable::Value(ShaderDesc& /*value*/) const
//{
//	BOOST_ASSERT(false);
//}

void HrRenderVariable::Value(std::vector<bool>& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(std::vector<uint32_t>& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(std::vector<int32_t>& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(std::vector<float>& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(std::vector<uint2>& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(std::vector<uint3>& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(std::vector<uint4>& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(std::vector<int2>& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(std::vector<int3>& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(std::vector<int4>& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(std::vector<float2>& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(std::vector<float3>& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(std::vector<float4>& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(std::vector<float4x4>& /*value*/) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::BindToCBuffer(HrRenderEffectConstantBuffer* cbuff, uint32_t offset, uint32_t stride)
{
	HR_UNUSED(cbuff);
	HR_UNUSED(offset);
	HR_UNUSED(stride);

	BOOST_ASSERT(false);
}

void HrRenderVariable::RebindToCBuffer(HrRenderEffectConstantBuffer* cbuff)
{
	HR_UNUSED(cbuff);

	BOOST_ASSERT(false);
}


/////////////////////////////////= HrRenderVariableFloat4x4 =/////////////////////////////////////

HrRenderVariable& HrRenderVariableFloat4x4::operator=(const float4x4& value)
{
	return HrRenderVariableConcrete<float4x4>::operator=(HrMath::Transpose(value));
}

void HrRenderVariableFloat4x4::Value(float4x4& val) const
{
	HrRenderVariableConcrete<float4x4>::Value(val);
	val = HrMath::Transpose(val);
}

///////////////////////////////////////////
//
//
///////////////////////////////////////////

HrRenderEffectParameter::HrRenderEffectParameter(const std::string& strVarName, size_t nHashName)
{
	m_paramType = RPT_UNKNOWN;
	m_pRenderVariable = nullptr;
	m_pBindConstBuffer = nullptr;
	m_nStride = 0;
	m_nElements = 0;

	m_strName = strVarName;
	m_nHashName = nHashName;
}

HrRenderEffectParameter::~HrRenderEffectParameter()
{
	SAFE_DELETE(m_pRenderVariable);
}

void HrRenderEffectParameter::ParamInfo(EnumRenderParamType paramType, EnumRenderEffectDataType dataType, uint32 nElements)
{
	m_paramType = paramType;
	m_dataType = dataType;
	switch (dataType)
	{
	case REDT_FLOAT1:
		break;
	case REDT_FLOAT2:
		break;
	case REDT_FLOAT3:
		break;
	case REDT_FLOAT4:
		break;
	case REDT_SAMPLER1D:
		break;
	case REDT_SAMPLER2D:
		break;
	case REDT_SAMPLER3D:
		break;
	case REDT_SAMPLERCUBE:
		break;
	case REDT_SAMPLERRECT:
		break;
	case REDT_SAMPLER1DSHADOW:
		break;
	case REDT_SAMPLER2DSHADOW:
		break;
	case REDT_SAMPLER2DARRAY:
		break;
	case REDT_MATRIX_2X2:
		break;
	case REDT_MATRIX_2X3:
		break;
	case REDT_MATRIX_2X4:
		break;
	case REDT_MATRIX_3X2:
		break;
	case REDT_MATRIX_3X3:
		break;
	case REDT_MATRIX_3X4:
		break;
	case REDT_MATRIX_4X2:
		break;
	case REDT_MATRIX_4X3:
		break;
	case REDT_MATRIX_4X4:
		m_nStride = 16;
		break;
	case REDT_INT1:
		break;
	case REDT_INT2:
		break;
	case REDT_INT3:
		break;
	case REDT_INT4:
		break;
	case REDT_SUBROUTINE:
		break;
	case REDT_DOUBLE1:
		break;
	case REDT_DOUBLE2:
		break;
	case REDT_DOUBLE3:
		break;
	case REDT_DOUBLE4:
		break;
	case REDT_MATRIX_DOUBLE_2X2:
		break;
	case REDT_MATRIX_DOUBLE_2X3:
		break;
	case REDT_MATRIX_DOUBLE_2X4:
		break;
	case REDT_MATRIX_DOUBLE_3X2:
		break;
	case REDT_MATRIX_DOUBLE_3X3:
		break;
	case REDT_MATRIX_DOUBLE_3X4:
		break;
	case REDT_MATRIX_DOUBLE_4X2:
		break;
	case REDT_MATRIX_DOUBLE_4X3:
		break;
	case REDT_MATRIX_DOUBLE_4X4:
		break;
	case REDT_UINT1:
		break;
	case REDT_UINT2:
		break;
	case REDT_UINT3:
		break;
	case REDT_UINT4:
		break;
	case REDT_BOOL1:
		break;
	case REDT_BOOL2:
		break;
	case REDT_BOOL3:
		break;
	case REDT_BOOL4:
		break;
	case REDT_SAMPLER_WRAPPER1D:
		break;
	case REDT_SAMPLER_WRAPPER2D:
		break;
	case REDT_SAMPLER_WRAPPER3D:
		break;
	case REDT_SAMPLER_WRAPPERCUBE:
		break;
	case REDT_SAMPLER_STATE:
		break;
	case REDT_UNKNOWN:
		break;
	default:
		break;
	}
	m_nElements = nElements <= 0 ? 1 : nElements;
	if (m_pRenderVariable != nullptr)
	{
		SAFE_DELETE(m_pRenderVariable);
	}
	switch (paramType)
	{
	case RPT_WORLDVIEWPROJ_MATRIX:
	{
		BOOST_ASSERT(m_dataType == REDT_MATRIX_4X4 && m_nElements == 1);
		m_pRenderVariable = HR_NEW HrRenderVariableFloat4x4();
		break;
	}
	}

}

void HrRenderEffectParameter::BindConstantBuffer(HrRenderEffectConstantBuffer* pConstantBuffer, uint32 nOffset)
{
	BOOST_ASSERT(m_pRenderVariable);
	m_pBindConstBuffer = pConstantBuffer;
	m_pRenderVariable->BindToCBuffer(pConstantBuffer, nOffset, m_nStride);
}

////////////////////////////////////////////
//
//
////////////////////////////////////////////

HrRenderStructParameter::HrRenderStructParameter(const std::string& strVarName, size_t nHashName)
{
	m_strName = strVarName;
	m_nHashName = nHashName;
}

HrRenderStructParameter::~HrRenderStructParameter()
{

}


////////////////////////////////////////////
//
//
////////////////////////////////////////////

HrRenderEffectConstantBuffer::HrRenderEffectConstantBuffer(const std::string& strConstBufferName
	, size_t nHashName, size_t nSize)
{
	m_strConstBufferName = strConstBufferName;
	m_nHashName = nHashName;
	m_nSize = nSize;

	m_pConstantBufferData = HR_NEW HrStreamData(m_nSize);
	m_pConstantBuffer = HrDirector::Instance()->GetRenderFactory()->CreateHardwareBuffer();
	m_pConstantBuffer->BindStream(nullptr, m_nSize, HrGraphicsBuffer::HBU_GPUREAD_CPUWRITE, HrGraphicsBuffer::HBB_CONST);
}

HrRenderEffectConstantBuffer::~HrRenderEffectConstantBuffer()
{
	SAFE_DELETE(m_pConstantBufferData);
	SAFE_DELETE(m_pConstantBuffer);
}

Byte* HrRenderEffectConstantBuffer::GetStreamOffsetPoint(uint32 nOffset)
{
	BOOST_ASSERT(nOffset < m_pConstantBufferData->GetBufferSize());
	return m_pConstantBufferData->GetBufferPoint() + nOffset;
}

const Byte* HrRenderEffectConstantBuffer::GetStreamOffsetPoint(uint32 nOffset) const
{
	BOOST_ASSERT(nOffset < m_pConstantBufferData->GetBufferSize());
	return m_pConstantBufferData->GetBufferPoint() + nOffset;
}

Byte* HrRenderEffectConstantBuffer::GetStreamDataPoint()
{
	return m_pConstantBufferData->GetBufferPoint();
}

const Byte* HrRenderEffectConstantBuffer::GetStreamDataPoint() const
{
	return m_pConstantBufferData->GetBufferPoint();
}

void HrRenderEffectConstantBuffer::UpdateConstantBuffer()
{
	if (m_bDirty)
	{
		HrGraphicsBuffer::Mapper mapper(*m_pConstantBuffer, HrGraphicsBuffer::HBA_WRITE_ONLY);
		std::memcpy(mapper.Pointer<Byte>(), m_pConstantBufferData->GetBufferPoint(), m_pConstantBufferData->GetBufferSize());
		m_bDirty = false;
	}
}
