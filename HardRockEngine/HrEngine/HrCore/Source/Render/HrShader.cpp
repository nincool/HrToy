#include "HrCore/Include/Render/HrShader.h"

using namespace Hr;

HrShader::HrShader()
{
	m_shaderType = ST_VERTEX_SHADER;
}

HrShader::~HrShader()
{
}

void Hr::HrShader::SetShaderType(_SHADER_TYPE_ shaderType)
{
	m_shaderType = shaderType;
}

void HrShader::SetEntryPoint(std::string strEntryPoint)
{
	m_strEntryPoint = strEntryPoint;
}

void HrShader::Bind(IRender* pRender)
{
}

void HrShader::UnBind(IRender* pRender)
{
}

void HrShader::StreamIn(HrStreamData& streamData)
{
}

