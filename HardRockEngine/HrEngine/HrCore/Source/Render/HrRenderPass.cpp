#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/HrShader.h"
#include "Render/HrRenderFactory.h"
#include "HrDirector.h"


using namespace Hr;

HrRenderPass::HrRenderPass(std::string strPassName)
{
	m_strPassName = strPassName;

	m_pVertexShader = HrDirector::Instance()->GetRenderFactory()->CreateShader();
	m_pVertexShader->SetShaderType(HrShader::ST_VERTEX_SHADER);
	
	m_pPixelShader = HrDirector::Instance()->GetRenderFactory()->CreateShader();
	m_pPixelShader->SetShaderType(HrShader::ST_PIXEL_SHADER);
}

HrRenderPass::~HrRenderPass()
{
	SAFE_DELETE(m_pVertexShader);
	SAFE_DELETE(m_pPixelShader);
}

void HrRenderPass::SetVSEntryPoint(std::string strVSEntryPoint)
{
	m_pVertexShader->SetEntryPoint(strVSEntryPoint);
}

void HrRenderPass::SetPSEntryPoint(std::string strPSEntryPoint)
{
	m_pPixelShader->SetEntryPoint(strPSEntryPoint);
}

void HrRenderPass::StreamIn(HrStreamData& streamData)
{
	m_pVertexShader->StreamIn(streamData);
	m_pPixelShader->StreamIn(streamData);
}

void HrRenderPass::BindPass(HrRender* pRender)
{
	m_pVertexShader->Bind(pRender);
	m_pPixelShader->Bind(pRender);
}

void HrRenderPass::UnBindPass(HrRender* pRender)
{
	m_pVertexShader->UnBind(pRender);
	m_pPixelShader->UnBind(pRender);
}

HrShader* HrRenderPass::GetVertexShader()
{
	return m_pVertexShader;
}

HrShader* HrRenderPass::GetPixelShader()
{
	return m_pPixelShader;
}

void HrRenderPass::UpdateShaderParams(HrRenderFrameParameters& renderFrameParameters)
{
	if (m_pVertexShader)
	{
		m_pVertexShader->UpdateAutoParams(renderFrameParameters);
	}
}


