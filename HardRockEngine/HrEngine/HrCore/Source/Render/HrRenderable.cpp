#include "Render/HrRenderable.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderFrameParameters.h"
#include "Render/HrVertex.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrMesh.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrCoreComponentScene.h"
#include "Kernel/HrCoreComponentRender.h"

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

void HrRenderable::SetSubMesh(const HrSubMeshPtr& pSubMesh)
{
	m_pSubMesh = pSubMesh;
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
	BOOST_ASSERT(m_pSubMesh);
	return m_pSubMesh->GetMaterial();
}

const HrSubMeshPtr& HrRenderable::GetSubMesh()
{
	return m_pSubMesh;
}

void HrRenderable::SetAttachSceneObject(const HrSceneObjectPtr& pSceneObj)
{
	m_pAttachSceneObj = pSceneObj;
}

HrSceneObjectPtr HrRenderable::GetAttachSceneObject()
{
	if (!m_pAttachSceneObj.expired())
	{
		return m_pAttachSceneObj.lock();
	}

	return nullptr;
}

void HrRenderable::Render()
{
	OnRenderBegin();

	HrDirector::Instance()->GetRenderCoreComponent()->DoRender(GetRenderTechnique(), GetRenderLayout());

	OnRenderEnd();
}

void HrRenderable::OnRenderBegin()
{
	auto& pRenderFrameParam = HrDirector::Instance()->GetSceneCoreComponent()->GetRenderFrameParameters();
	GetRenderEffect()->UpdateAutoEffectParams(pRenderFrameParam);
}

void HrRenderable::OnRenderEnd()
{

}

bool HrRenderable::CheckRenderLayoutMatchShader()
{
	if (m_pSubMesh && m_pCurTechnique)
	{
		std::vector<std::pair<std::string, uint32> > vecInputSemantics;
		auto vecVertexStreams = m_pSubMesh->GetRenderLayout()->GetVertexStreams();
		for (size_t i = 0; i < vecVertexStreams.size(); ++i)
		{
			auto vecVertexElement = vecVertexStreams[i]->GetVertex()->GetVertexElement();
			
		}

		return true;
	}

	return false;
}
