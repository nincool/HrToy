#include "Asset/HrRenderEffectParameter.h"

using namespace Hr;

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
	m_strConstBufferName = strConstBufferName;
	m_nHashName = nHashName;
}

HrRenderEffectConstantBuffer::~HrRenderEffectConstantBuffer()
{

}




