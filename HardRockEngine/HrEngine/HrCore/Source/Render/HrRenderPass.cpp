#include "Render/HrRenderPass.h"
#include "Render/HrShader.h"
#include "Render/HrDepthStencilState.h"
#include "Render/HrBlendState.h"
#include "Render/HrRasterizerState.h"
#include "Render/HrRenderFactory.h"
#include "Asset/HrRenderEffectParameter.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrCoreComponentRender.h"

#include "Render/HrRenderSystem.h"

using namespace Hr;

HrRenderPass::HrRenderPass(const std::string& strPassName)
{
	m_strPassName = strPassName;
	m_pVertexShader = nullptr;
	m_pPixelShader = nullptr;

	//TODO!!!to release
	//m_pBlendState = HrDirector::Instance()->GetRenderCoreComponent()->GetRenderSystem()->GetRenderFactory()->CreateBlendState();
	m_pDepthStencilState = nullptr;
	m_pBlendState = nullptr;
	m_pRasterizerState = HrDirector::Instance()->GetRenderCoreComponent()->GetRenderSystem()->GetRenderFactory()->GetDefualtRasterizerState();
}

HrRenderPass::~HrRenderPass()
{
}

void HrRenderPass::BindPass(const HrRenderPtr& pRender)
{
	BOOST_ASSERT(m_pDepthStencilState);
	BOOST_ASSERT(m_pBlendState);
	BOOST_ASSERT(m_pRasterizerState);

	BOOST_ASSERT(m_pVertexShader);
	BOOST_ASSERT(m_pPixelShader);

	//m_pDepthStencilState->Bind(pRender);
	//m_pBlendState->Bind(pRender);
	//m_pRasterizerState->Bind(pRender);

	m_pVertexShader->Accept(pRender);
	m_pPixelShader->Accept(pRender);
}

void HrRenderPass::UnBindPass(const HrRenderPtr& pRender)
{

}

const HrShaderPtr& HrRenderPass::GetShader(HrShader::EnumShaderType shaderType)
{
	switch (shaderType)
	{
	case HrShader::ST_VERTEX_SHADER:
		return m_pVertexShader;
	case HrShader::ST_PIXEL_SHADER:
		return m_pPixelShader;
	case HrShader::ST_GEOMETRY_SHADER:
		break;
	case HrShader::ST_DOMAIN_SHADER:
		break;
	case HrShader::ST_HULL_SHADER:
		break;
	case HrShader::ST_COMPUTE_SHADER:
		break;
	case HrShader::ST_NUMSHADERTYPES:
		break;
	default:
		break;
	}
}

void HrRenderPass::SetShader(const HrShaderPtr& pShader, HrShader::EnumShaderType shaderType)
{
	switch (shaderType)
	{
	case HrShader::ST_VERTEX_SHADER:
		m_pVertexShader = pShader;
		break;
	case HrShader::ST_PIXEL_SHADER:
		m_pPixelShader = pShader;
		break;
	case HrShader::ST_GEOMETRY_SHADER:
		break;
	case HrShader::ST_DOMAIN_SHADER:
		break;
	case HrShader::ST_HULL_SHADER:
		break;
	case HrShader::ST_COMPUTE_SHADER:
		break;
	case HrShader::ST_NUMSHADERTYPES:
		break;
	default:
		break;
	}
}

void HrRenderPass::SetDepthStencilState(HrDepthStencilState* pDepthStencilState)
{
	m_pDepthStencilState = pDepthStencilState;
}

void HrRenderPass::SetBlendState(HrBlendState* pBlendState)
{
	m_pBlendState = pBlendState;
}


