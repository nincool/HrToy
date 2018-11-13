#include "Render/HrRenderPass.h"
#include "Render/HrShader.h"
#include "Render/HrDepthStencilState.h"
#include "Render/HrBlendState.h"
#include "Render/HrRasterizerState.h"
#include "Render/HrRenderFactory.h"
#include "Asset/HrRenderEffectParameter.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrRenderModule.h"

#include "Render/HrRenderSystem.h"

using namespace Hr;

HrRenderPass::HrRenderPass(const std::string& strPassName)
{
	m_strPassName = strPassName;
	m_pVertexShader = nullptr;
	m_pPixelShader = nullptr;

	m_pDepthStencilState = nullptr;
	m_pBlendState = nullptr;
	m_pRasterizerState = nullptr;
}

HrRenderPass::~HrRenderPass()
{
}

void HrRenderPass::BindPass(const HrRenderPtr& pRender)
{
	BOOST_ASSERT(m_pBlendState);
	m_pBlendState->Accept(pRender);
	
	BOOST_ASSERT(m_pDepthStencilState);
	m_pDepthStencilState->Accept(pRender);
	
	BOOST_ASSERT(m_pRasterizerState);
	m_pRasterizerState->Accept(pRender);
	
	BOOST_ASSERT(m_pVertexShader);
	m_pVertexShader->Accept(pRender);

	BOOST_ASSERT(m_pPixelShader);
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

	return nullptr;
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

void HrRenderPass::SetRasterizerState(const HrRasterizerStatePtr& pRasterizerState)
{
	m_pRasterizerState = pRasterizerState;
}

void HrRenderPass::SetDepthStencilState(const HrDepthStencilStatePtr& pDepthStencilState)
{
	m_pDepthStencilState = pDepthStencilState;
}

void HrRenderPass::SetBlendState(const HrBlendStatePtr& pBlendState)
{
	m_pBlendState = pBlendState;
}

void HrRenderPass::SetSamplerState(const HrSamplerStatePtr& pSamplerState)
{
	m_pSamplerState = pSamplerState;

}

