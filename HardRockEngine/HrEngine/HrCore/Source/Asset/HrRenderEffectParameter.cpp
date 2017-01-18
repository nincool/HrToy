#include "Asset/HrRenderEffectParameter.h"
#include "Asset/HrStreamData.h"
#include "Kernel/HrDirector.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrGraphicsBuffer.h"
#include "Render/HrSamplerState.h"

using namespace Hr;

std::vector<HrRenderParamDefine> HrRenderParamDefine::m_s_vecRenderParamDefine =
{
	HrRenderParamDefine(RPT_WORLD_MATRIX, "world_matrix", REDT_MATRIX_4X4, 16, 64),
	HrRenderParamDefine(RPT_INVERSE_WROLD_MATRIX, "inverse_world_matrix",  REDT_MATRIX_4X4, 16, 64),
	HrRenderParamDefine(RPT_TRANSPOSE_WORLD_MATRIX, "transpose_world_matrix",  REDT_MATRIX_4X4, 16, 64),
	HrRenderParamDefine(RPT_INVERSE_TRANSPOSE_WORLD_MATRIX, "inverse_transpose_world_matrix",  REDT_MATRIX_4X4, 16, 64),
	HrRenderParamDefine(RPT_WORLD_VIEW_PROJ_MATRIX, "world_view_proj_matrix", REDT_MATRIX_4X4, 16, 64),

	HrRenderParamDefine(RPT_AMBIENT_LIGHT_COLOR, "ambient_light_color", REDT_FLOAT4, 4, 16),
	HrRenderParamDefine(RPT_DIFFUSE_LIGHT_COLOR, "diffuse_light_color", REDT_FLOAT4, 4, 16),
	HrRenderParamDefine(RPT_SPECULAR_LIGHT_COLOR, "specular_light_color", REDT_FLOAT4, 4, 16),

	HrRenderParamDefine(RPT_LIGHT_DIRECTION, "light_direction", REDT_FLOAT3, 3, 12),

	HrRenderParamDefine(RPT_AMBIENT_MATERIAL_COLOR, "ambient_material_color", REDT_FLOAT4, 4, 16),
	HrRenderParamDefine(RPT_DIFFUSE_MATERIAL_COLOR, "diffuse_material_color", REDT_FLOAT4, 4, 16),
	HrRenderParamDefine(RPT_SPECULAR_MATERIAL_COLOR, "specular_material_color", REDT_FLOAT4, 4, 16),
	HrRenderParamDefine(RPT_REFLECT_MATERIAL_COLOR, "reflect_material_color", REDT_FLOAT4, 4, 16),
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

HrRenderVariable& HrRenderVariable::operator=(const HrTexture* pTexture)
{
	BOOST_ASSERT(false);
	return *this;
}

HrRenderVariable& HrRenderVariable::operator=(const HrSamplerState* pSamplerState)
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

void HrRenderVariable::Value(HrTexture*& val) const
{
	BOOST_ASSERT(false);
}

void HrRenderVariable::Value(HrSamplerState*& val) const
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

/////////////////////////////////= HrRenderVariableTexture =/////////////////////////////////////
HrRenderVariableTexture::HrRenderVariableTexture() : m_pTexture(nullptr)
{

}

HrRenderVariableTexture::~HrRenderVariableTexture()
{

}

HrRenderVariable& HrRenderVariableTexture::operator=(const HrTexture* pTexture)
{
	m_pTexture = const_cast<HrTexture*>(pTexture);
	return *this;
}

void HrRenderVariableTexture::Value(HrTexture*& val) const
{
	val = m_pTexture;
}

////////////////////////////////= HrRenderVarialbeSampler=////////////////////////////////////////
HrRenderVariableSamplerState::HrRenderVariableSamplerState()
{
	//TODO!!!!!!!!!!!!!!!!!
	m_pSamplerState = HrDirector::Instance()->GetRenderFactory()->CreateSamplerState();
}

HrRenderVariableSamplerState::~HrRenderVariableSamplerState()
{

}

HrRenderVariable& HrRenderVariableSamplerState::operator=(const HrSamplerState* pSamplerState)
{
	return *this;
}

void HrRenderVariableSamplerState::Value(HrSamplerState*& val) const
{
	val = m_pSamplerState;
}

///////////////////////////////////////////
//
//
///////////////////////////////////////////

HrRenderEffectParameter::HrRenderEffectParameter(const std::string& strVarName, size_t nHashName)
{
	m_paramType = RPT_UNKNOWN;
	m_bindType = REPBT_UNKNOWN;
	m_pRenderVariable = nullptr;
	m_pBindConstBuffer = nullptr;
	m_nStride = 0;
	m_nArraySize = 0;

	m_strName = strVarName;
	m_nHashName = nHashName;
}

HrRenderEffectParameter::~HrRenderEffectParameter()
{
	SAFE_DELETE(m_pRenderVariable);
}

void HrRenderEffectParameter::ParamInfo(EnumRenderParamType paramType, EnumRenderEffectDataType dataType, EnumRenderEffectParamBindType bindType, uint32 nStride, uint32 nArraySize)
{
	m_paramType = paramType;
	m_dataType = dataType;
	m_bindType = bindType;
	
	m_nArraySize = m_nArraySize <= 0 ? 1 : m_nArraySize;
	if (m_pRenderVariable != nullptr)
	{
		SAFE_DELETE(m_pRenderVariable);
	}
	switch (paramType)
	{
	case RPT_WORLD_VIEW_PROJ_MATRIX:
	case RPT_INVERSE_TRANSPOSE_WORLD_MATRIX:
	{
		BOOST_ASSERT(m_dataType == REDT_MATRIX_4X4 && m_nArraySize == 1);
		m_pRenderVariable = HR_NEW HrRenderVariableFloat4x4();
		break;
	}
	case RPT_AMBIENT_LIGHT_COLOR:
	case RPT_DIFFUSE_LIGHT_COLOR:
	case RPT_SPECULAR_LIGHT_COLOR:
	case RPT_AMBIENT_MATERIAL_COLOR:
	case RPT_DIFFUSE_MATERIAL_COLOR:
	case RPT_SPECULAR_MATERIAL_COLOR:
	case RPT_REFLECT_MATERIAL_COLOR:
	{
		BOOST_ASSERT(m_dataType == REDT_FLOAT4 && m_nArraySize == 1);
		m_pRenderVariable = HR_NEW HrRenderVariableFloat4();
		break;
	}
	case RPT_LIGHT_DIRECTION:
	{
		BOOST_ASSERT(m_dataType == REDT_FLOAT3 && m_nArraySize == 1);
		m_pRenderVariable = HR_NEW HrRenderVariableFloat3();
		break;
	}
	case RPT_TEXTURE:
	{
		switch (dataType)
		{
		case REDT_TEXTURE2D:
		{
			m_pRenderVariable = HR_NEW HrRenderVariableTexture();
			break;
		}
		}
		break;
	}
	case RPT_SAMPLER:
	{
		switch (dataType)
		{
		case REDT_SAMPLER2D:
		{
			m_pRenderVariable = HR_NEW HrRenderVariableSamplerState();
			break;
		}
		default:
			break;
		}
		break;
	}
	default:
		BOOST_ASSERT(nullptr);
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

HrRenderEffectStructParameter::HrRenderEffectStructParameter(const std::string& strTypeName, const std::string& strVarName, size_t nHashName)
{
	m_strTypeName = strTypeName;
	m_strName = strVarName;
	m_nHashName = nHashName;
}

HrRenderEffectStructParameter::~HrRenderEffectStructParameter()
{
	for (auto item : m_vecRenderEffectParameter)
	{
		SAFE_DELETE(item);
	}
}

void HrRenderEffectStructParameter::AddRenderEffectParameter(HrRenderEffectParameter* pRenderParameter)
{
	m_vecRenderEffectParameter.push_back(pRenderParameter);
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
