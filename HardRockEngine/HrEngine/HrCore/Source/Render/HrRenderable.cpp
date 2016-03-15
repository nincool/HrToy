#include "Render/HrRenderable.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrRenderTechnique.h"
#include "Render/IRenderFactory.h"
#include "HrDirector.h"


using namespace Hr;

HrRenderable::HrRenderable()
{	
	m_pRenderLayout = HrDirector::GetInstance().GetRenderFactory()->CreateRenderLayout();
	m_pRenderTechnique = nullptr;
}

HrRenderable::~HrRenderable()
{
	SAFE_DELETE(m_pRenderLayout);
}

IRenderLayout* HrRenderable::GetRenderLayout()
{
	return m_pRenderLayout;
}

IRenderTechnique* HrRenderable::GetRenderTechnique()
{
	return m_pRenderTechnique;
}

void HrRenderable::Update(HrRenderFrameParameters& renderFrameParameters)
{
	m_pRenderTechnique->UpdateEffectParams(renderFrameParameters);
}

