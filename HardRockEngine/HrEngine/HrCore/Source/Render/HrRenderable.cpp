#include "Render/HrRenderable.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderFactory.h"
#include "HrDirector.h"


using namespace Hr;

HrRenderable::HrRenderable()
{	
	m_pRenderLayout = HrDirector::Instance()->GetRenderFactory()->CreateRenderLayout();
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

