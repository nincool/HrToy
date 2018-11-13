#include "HrCore/Include/Render/HrShader.h"
#include "HrCore/Include/Kernel/HrDirector.h"
#include "HrCore/Include/Kernel/HrFileUtils.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrShader::HrShader()
{
	m_shaderType = ST_VERTEX_SHADER;
	m_nHashName = 0;
}

HrShader::~HrShader()
{

}

void HrShader::BindRenderParameter(std::vector<HrRenderEffectConstantBufferPtr>&& vecRenderConstBuffer, std::vector<HrRenderEffectParameterPtr>&& vecShaderResouces)
{
	m_vecBindRenderResources.swap(vecShaderResouces);
	m_vecBindRenderConstantBuffer.swap(vecRenderConstBuffer);

	BindRenderParameterImpl();
}

void HrShader::SetSampler(const HrSamplerStatePtr& pSampler)
{
	m_pSampler = pSampler;
}

