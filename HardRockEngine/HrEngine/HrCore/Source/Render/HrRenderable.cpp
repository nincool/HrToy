#include "Render/HrRenderable.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderFrameParameters.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrMesh.h"
#include "Kernel/HrDirector.h"

using namespace Hr;

HrRenderable::HrRenderable()
{	
}

HrRenderable::~HrRenderable()
{
}

const HrRenderLayoutPtr& HrRenderable::GetRenderLayout()
{
	return nullptr;
}

const HrRenderTechniquePtr& HrRenderable::GetRenderTechnique()
{
	return m_pCurTechnique;
}

uint32 HrRenderable::GetSubRenderableNum() const
{
	return m_vecSubRenderable.size();
}

const HrRenderablePtr HrRenderable::GetSubRenderable(uint32 nIndex) const
{
	return m_vecSubRenderable[nIndex];
}

bool HrRenderable::CanRender()
{
	return true;
}

void HrRenderable::SetRenderEffect(const HrRenderEffectPtr& pRenderEff)
{
	m_pRenderEffect = pRenderEff;
	//todo Ñ°ÕÒ×îºÏÊÊµÄ
	m_pCurTechnique = m_pRenderEffect->GetTechniqueByIndex(0);
}

const HrRenderEffectPtr& HrRenderable::GetRenderEffect() const
{
	return m_pRenderEffect;
}

const HrMaterialPtr& HrRenderable::GetMaterial()
{
	return nullptr;
}
