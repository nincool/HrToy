
#include "HrCore/Include/Render/HrRenderCommand.h"

using namespace Hr;



HrRenderCommand::HrRenderCommand(std::function<void()> funcRenderBegin, std::function<void()> funcRenderEnd)
{
	m_funcRenderBegin = funcRenderBegin;
	m_funcRenderEnd = funcRenderEnd;
	m_fGlobalOrder = 0;
	m_fDepth = 0;
}

float HrRenderCommand::GetGlobalOrder()
{
	return m_fGlobalOrder;
}

void HrRenderCommand::SetGlobalOrder(float fGlobalOrder)
{
	m_fGlobalOrder = fGlobalOrder;
}

void HrRenderCommand::SetDepth(float fDepth)
{
	m_fDepth = fDepth;
}

float HrRenderCommand::GetDepth()
{
	return m_fDepth;
}

void HrRenderCommand::SetTransform(HrTransform* pTransfrom)
{
	m_pTransform = pTransfrom;
}

HrTransform* HrRenderCommand::GetTransform()
{
	return m_pTransform;
}

void HrRenderCommand::SetMaterial(HrMaterial* pMaterial)
{
	m_pMaterial = pMaterial;
}

HrMaterial* HrRenderCommand::GetMaterial()
{
	return m_pMaterial;
}

void HrRenderCommand::SetRenderLayout(HrRenderLayout* pRenderLayout)
{
	m_pRenderLayout = pRenderLayout;
}

HrRenderLayout* HrRenderCommand::GetRenderLayout()
{
	return m_pRenderLayout;
}

void HrRenderCommand::SetRenderEffect(HrRenderEffect* pRenderEffect)
{
	m_pRenderEffect = pRenderEffect;
}

HrRenderEffect* HrRenderCommand::GetRenderEffect() const
{
	return m_pRenderEffect;
}

void HrRenderCommand::SetRenderTechnique(HrRenderTechnique* pRenderTechnique)
{
	m_pRenderTechnique = pRenderTechnique;
}

HrRenderTechnique* HrRenderCommand::GetRenderTechnique()
{
	return m_pRenderTechnique;
}

void HrRenderCommand::OnRenderBegin()
{
	if (m_funcRenderBegin)
		m_funcRenderBegin();
}

void HrRenderCommand::OnRenderEnd()
{
	if (m_funcRenderEnd)
		m_funcRenderEnd();
}

