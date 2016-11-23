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

void HrShader::BindRenderParameter(std::vector<HrRenderEffectParameter*>& vecRenderParameters, std::vector<HrRenderEffectConstantBuffer*>& vecRenderConstBuffers)
{
	m_vecBindRenderParameters.swap(vecRenderParameters);
	m_vecBindRenderConstantBuffers.swap(vecRenderConstBuffers);

	BindRenderParameterImpl();
}

void HrShader::GetBindRenderParameter(std::vector<HrRenderEffectParameter*>& vecRenderParameters)
{
	vecRenderParameters = m_vecBindRenderParameters;
}

