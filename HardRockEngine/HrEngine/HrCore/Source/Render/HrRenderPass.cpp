#include "Render/HrRenderPass.h"
#include "Render/HrShader.h"
#include "Render/HrRenderFactory.h"
#include "Asset/HrRenderEffectParameter.h"
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
	m_pVertexShader->Bind(pRender);
	m_pPixelShader->Bind(pRender);
}

void HrRenderPass::UnBindPass(HrRender* pRender)
{

}

HrShader* HrRenderPass::GetShader(HrShader::EnumShaderType shaderType)
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

void HrRenderPass::SetShader(HrShader* pShader, HrShader::EnumShaderType shaderType)
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

void HrRenderPass::CollectShaderParameters(std::vector<HrRenderEffectParameter*>& vecRenderEffectParameter)
{
	std::vector<HrRenderEffectParameter*> vecShaderBindParameter;
	if (m_pVertexShader)
	{
		m_pVertexShader->GetBindRenderParameter(vecShaderBindParameter);
		this->StorageShaderParameter(vecRenderEffectParameter, vecShaderBindParameter);
	}
	if (m_pPixelShader)
	{
		m_pPixelShader->GetBindRenderParameter(vecShaderBindParameter);
		this->StorageShaderParameter(vecRenderEffectParameter, vecShaderBindParameter);
	}
}

void HrRenderPass::StorageShaderParameter(std::vector<HrRenderEffectParameter*>& vecRenderEffectParameter, std::vector<HrRenderEffectParameter*>& vecShaderBindParameter)
{
	for (auto itemBind : vecShaderBindParameter)
	{
		auto posItem = std::find_if(vecRenderEffectParameter.begin(), vecRenderEffectParameter.end(), [&](HrRenderEffectParameter* pParam)
		{
			if (pParam->HashName() == itemBind->HashName())
			{
				return true;
			}
			return false;
		});
		if (posItem == vecRenderEffectParameter.end())
		{
			vecRenderEffectParameter.push_back(itemBind);
		}
	}
}

