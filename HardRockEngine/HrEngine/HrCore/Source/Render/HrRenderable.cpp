#include "Render/HrRenderable.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrRenderTechnique.h"
#include "Render/IRenderFactory.h"
#include "HrDirector.h"


using namespace Hr;

HrRenderable::HrRenderable()
{	
	m_pRenderLayout = HrDirector::GetInstance().GetRenderFactory()->CreateRenderLayout();
	//m_pRenderTechnique = HR_NEW HrRenderTechnique();
}

HrRenderable::~HrRenderable()
{
	SAFE_DELETE(m_pRenderLayout);
	//SAFE_DELETE(m_pRenderTechnique);
}

