#include "Render/HrRenderable.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderFrameParameters.h"
#include "Asset/HrMesh.h"
#include "Kernel/HrDirector.h"

using namespace Hr;

HrRenderable::HrRenderable()
{	
	m_pRenderEffect = nullptr;
	m_pRenderTechnique = nullptr;
}

HrRenderable::~HrRenderable()
{
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

