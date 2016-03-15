#include "HrCore/Include/Render/HrShader.h"
#include "HrCore/Include/Render/IRenderFactory.h"
#include "HrCore/Include/Render/HrHardwareBuffer.h"
#include "HrCore/Include/HrDirector.h"

using namespace Hr;

HrShader::HrShader()
{
	m_shaderType = ST_VERTEX_SHADER;
}

HrShader::~HrShader()
{
	for (auto& item : m_vecRenderConstantBuffer)
	{
		SAFE_DELETE(item);
	}
	m_vecRenderConstantBuffer.clear();
}

void HrShader::SetShaderType(_SHADER_TYPE_ shaderType)
{
	m_shaderType = shaderType;
}

void HrShader::UpdateAutoParams(HrRenderFrameParameters& renderFrameParameters)
{
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

