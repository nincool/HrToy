#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/HrShader.h"
#include "Render/HrRenderFactory.h"
#include "Kernel/HrDirector.h"


using namespace Hr;

HrRenderPass::HrRenderPass(std::string strPassName)
{
	m_strPassName = strPassName;
	m_pVertexShader = nullptr;
	m_pPixelShader = nullptr;
}

HrRenderPass::~HrRenderPass()
{
}

void HrRenderPass::BindPass(HrRender* pRender)
{

}

void HrRenderPass::UnBindPass(HrRender* pRender)
{

}

void HrRenderPass::SetShader(HrShader* pShader, HrShader::EnumShaderType shaderType)
{
	switch (shaderType)
	{
	case HrShader::ST_VERTEX_SHADER:
		m_pVertexShader = pShader;
		break;
	case Hr::HrShader::ST_PIXEL_SHADER:
		m_pPixelShader = pShader;
		break;
	case Hr::HrShader::ST_GEOMETRY_SHADER:
		break;
	case Hr::HrShader::ST_DOMAIN_SHADER:
		break;
	case Hr::HrShader::ST_HULL_SHADER:
		break;
	case Hr::HrShader::ST_COMPUTE_SHADER:
		break;
	case Hr::HrShader::ST_NUMSHADERTYPES:
		break;
	default:
		break;
	}
}

void HrRenderPass::UpdateShaderParams(HrRenderFrameParameters& renderFrameParameters)
{
	if (m_pVertexShader)
	{
		m_pVertexShader->UpdateParams(renderFrameParameters);
	}
}

