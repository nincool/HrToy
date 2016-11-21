#include "Asset/HrRenderEffectParameter.h"
#include "Asset/HrStreamData.h"

using namespace Hr;


HrRenderVariable::HrRenderVariable()
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

void HrRenderVariable::BindToCBuffer(HrRenderEffectConstantBuffer& cbuff, uint32_t offset, uint32_t stride)
{
	HR_UNUSED(cbuff);
	HR_UNUSED(offset);
	HR_UNUSED(stride);

	BOOST_ASSERT(false);
}

void HrRenderVariable::RebindToCBuffer(HrRenderEffectConstantBuffer& cbuff)
{
	HR_UNUSED(cbuff);

	BOOST_ASSERT(false);
}

///////////////////////////////////////////
//
//
///////////////////////////////////////////

HrRenderEffectParameter::HrRenderEffectParameter(const std::string& strVarName, size_t nHashName)
{
	m_paramType = REDT_FLOAT1;
	m_pAttachConstBuffer = nullptr;
}

HrRenderEffectParameter::~HrRenderEffectParameter()
{

}

////////////////////////////////////////////
//
//
///////////////////////////////////////////

HrRenderEffectConstantBuffer::HrRenderEffectConstantBuffer(const std::string& strConstBufferName, size_t nHashName)
{
	m_pConstantBufferData = HR_NEW HrStreamData();
	m_strConstBufferName = strConstBufferName;
	m_nHashName = nHashName;
}

HrRenderEffectConstantBuffer::~HrRenderEffectConstantBuffer()
{
	SAFE_DELETE(m_pConstantBufferData);
}




