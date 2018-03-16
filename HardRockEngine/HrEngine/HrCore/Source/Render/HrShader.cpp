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

void HrShader::BindRenderParameter(std::vector<HrRenderEffectParameterPtr>& vecRenderParameter
	, std::vector<HrRenderEffectConstantBufferPtr>& vecRenderConstBuffer)
{
	m_vecBindRenderParameter.swap(vecRenderParameter);
	m_vecBindRenderConstantBuffer.swap(vecRenderConstBuffer);

	BindRenderParameterImpl();
}

