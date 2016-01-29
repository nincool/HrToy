#include "HrCore/Include/Render/HrRenderPass.h"
#include "HrCore/Include/Render/IShader.h"

using namespace Hr;

HrRenderPass::HrRenderPass()
{
	m_pShader = nullptr;
}

HrRenderPass::~HrRenderPass()
{

}

void HrRenderPass::BindPass(IRender* pRender)
{
	m_pShader->Bind(pRender);
}

void HrRenderPass::UnBindPass(IRender* pRender)
{
	m_pShader->UnBind(pRender);
}
