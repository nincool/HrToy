#include "Render/HrRenderable.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderFrameParameters.h"
#include "Kernel/HrDirector.h"


using namespace Hr;

HrRenderable::HrRenderable()
{	
	//m_pRenderLayout = HrDirector::Instance()->GetRenderFactory()->CreateRenderLayout();
	m_pRenderTechnique = nullptr;
}

HrRenderable::~HrRenderable()
{
	//SAFE_DELETE(m_pRenderLayout);
}

HrRenderLayout* HrRenderable::GetRenderLayout()
{
	//return m_pRenderLayout;
	 
}

HrRenderTechnique* HrRenderable::GetRenderTechnique()
{
	return m_pRenderTechnique;
}

void HrRenderable::UpdateRenderFrameParameters(HrRenderFrameParameters& renderFrameParameters)
{
	renderFrameParameters.SetCurrentRenderable(this);
	m_pRenderTechnique->UpdateEffectParams(renderFrameParameters);
}

