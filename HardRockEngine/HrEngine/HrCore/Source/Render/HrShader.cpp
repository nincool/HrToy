#include "HrCore/Include/Render/HrShader.h"
#include "HrCore/Include/Render/HrRenderConstantBuffer.h"
#include "HrCore/Include/Kernel/HrDirector.h"


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

void HrShader::SetShaderType(EnumShaderType shaderType)
{
	m_shaderType = shaderType;
}

void HrShader::UpdateParams(HrRenderFrameParameters& renderFrameParameters)
{
}

void HrShader::SetEntryPoint(std::string strEntryPoint)
{
	m_strEntryPoint = strEntryPoint;
}

void HrShader::Bind(HrRender* pRender)
{
}

void HrShader::UnBind(HrRender* pRender)
{
}

void HrShader::StreamIn(HrStreamData& streamData)
{
}

HrRenderConstantBuffer* HrShader::AddRenderConstantBuffer()
{
	HrRenderConstantBuffer* pRenderConstantBuffer = HR_NEW HrRenderConstantBuffer();
	m_vecRenderConstantBuffer.push_back(pRenderConstantBuffer);

	return pRenderConstantBuffer;
}

