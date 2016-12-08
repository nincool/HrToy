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
	for (size_t i = 0; i < m_vecSubRenderable.size(); ++i)
	{
		SAFE_DELETE(m_vecSubRenderable[i]);
	}
	m_vecSubRenderable.clear();
}

HrRenderTechnique* HrRenderable::GetRenderTechnique()
{
	return m_pRenderTechnique;
}

void HrRenderable::UpdateRenderFrameParameters(HrRenderFrameParameters& renderFrameParameters)
{
	renderFrameParameters.SetCurrentRenderable(this);
	UpdateRenderFrameParametersImpl(renderFrameParameters);

	m_pRenderTechnique->UpdateEffectParams(renderFrameParameters);
}

uint32 HrRenderable::GetSubRenderableNum() const
{
	return m_vecSubRenderable.size();
}

HrRenderable* HrRenderable::GetSubRenderable(uint32 nIndex) const
{
	return m_vecSubRenderable[nIndex];
}

bool HrRenderable::CanRender()
{
	return true;
}
