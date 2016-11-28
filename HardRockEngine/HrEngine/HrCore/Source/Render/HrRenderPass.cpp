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

void HrRenderPass::CollectShaderParameters(std::vector<HrRenderEffectParameter*>& vecRenderEffectParameter, std::vector<HrRenderEffectStructParameter*>& vecRenderEffectStruct)
{
	std::vector<HrRenderEffectParameter*> vecShaderBindParameter;
	std::vector<HrRenderEffectStructParameter*> vecShaderBindStruct;
	if (m_pVertexShader)
	{
		m_pVertexShader->GetBindRenderParameter(vecShaderBindParameter, vecShaderBindStruct);
		this->StorageShaderParameter(vecRenderEffectParameter, vecRenderEffectStruct, vecShaderBindParameter, vecShaderBindStruct);
	}
	if (m_pPixelShader)
	{
		m_pPixelShader->GetBindRenderParameter(vecShaderBindParameter, vecShaderBindStruct);
		this->StorageShaderParameter(vecRenderEffectParameter, vecRenderEffectStruct, vecShaderBindParameter, vecShaderBindStruct);
	}
}

void HrRenderPass::StorageShaderParameter(std::vector<HrRenderEffectParameter*>& vecRenderEffectParameter
	, std::vector<HrRenderEffectStructParameter*>& vecRenderEffectStruct
	, std::vector<HrRenderEffectParameter*>& vecShaderBindParameter
	, std::vector<HrRenderEffectStructParameter*>& vecShaderBindStruct)
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
	for (auto itemBind : vecShaderBindStruct)
	{
		auto posItem = std::find_if(vecRenderEffectStruct.begin(), vecRenderEffectStruct.end(), [&](HrRenderEffectStructParameter* pParam)
		{
			if (pParam->HashName() == itemBind->HashName())
			{
				return true;
			}
			return false;
		});
		if (posItem == vecRenderEffectStruct.end())
		{
			vecRenderEffectStruct.push_back(itemBind);
		}
	}
}

