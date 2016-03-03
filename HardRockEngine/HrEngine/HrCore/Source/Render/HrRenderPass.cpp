#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/IShader.h"

using namespace Hr;

HrRenderPass::HrRenderPass(std::string strPassName)
{
	m_strPassName = strPassName;
	m_pVertexShader = nullptr;
}

HrRenderPass::~HrRenderPass()
{

}

void HrRenderPass::SetVSEntryPoint(std::string strVSEntryPoint)
{
	m_pVertexShader->SetEntryPoint(strVSEntryPoint);
}

void HrRenderPass::SetPSEntryPoint(std::string stePSEntryPoint)
{

}

void HrRenderPass::StreamIn(HrStreamData& streamData)
{
	//
}

void HrRenderPass::BindPass(IRender* pRender)
{
	m_pVertexShader->Bind(pRender);
}

void HrRenderPass::UnBindPass(IRender* pRender)
{
	m_pVertexShader->UnBind(pRender);
}
