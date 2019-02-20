#include "Render/HrRenderable.h"
#include "Render/HrRenderLayout.h"
#include "Render/HrRenderTechnique.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrVertex.h"
#include "Render/HrRenderFrameParameters.h"
#include "Asset/HrMaterial.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrMesh.h"
#include "Asset/HrRenderEffectParameter.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrSceneModule.h"
#include "Kernel/HrRenderModule.h"
#include "Kernel/HrResourceModule.h"

using namespace Hr;

HrRenderable::HrRenderable(const HrSubMeshPtr& pSubMesh)
{
	m_pSubMesh = pSubMesh;

	SetRenderEffect(HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>());
}

HrRenderable::~HrRenderable()
{
}

const HrRenderLayoutPtr& HrRenderable::GetRenderLayout()
{
	return m_pSubMesh->GetRenderLayout();
}

const HrRenderTechniquePtr& HrRenderable::GetTechnique()
{
	return m_pTechnique;
}

void HrRenderable::SetRenderEffect(const HrRenderEffectPtr& pRenderEff)
{
	if (m_pRenderEffect != pRenderEff)
	{
		m_pRenderEffect = pRenderEff;
		m_pTechnique = m_pRenderEffect->GetBestTechnique(m_pSubMesh->GetRenderLayout());
		BOOST_ASSERT(m_pTechnique);
	}
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

void HrRenderable::Render()
{
	OnRenderBegin();

	HrDirector::Instance()->GetRenderModule()->DoRender(GetTechnique(), GetRenderLayout());

	OnRenderEnd();
}

void HrRenderable::OnRenderBegin()
{
	UpdateRenderEffectParam();
}

void HrRenderable::OnRenderEnd()
{
}

bool HrRenderable::CheckRenderLayoutMatchShader()
{
	if (m_pSubMesh && m_pTechnique)
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

void HrRenderable::UpdateRenderEffectParam()
{
	auto& pRenderFrameParam = HrDirector::Instance()->GetSceneModule()->GetRenderFrameParameters();
	GetRenderEffect()->UpdateAutoEffectParams(pRenderFrameParam);

	uint32 nEnableAlbedoTex = 0u;
	const HrTexturePtr& pDiffuseTex = GetSubMesh()->GetMaterial()->GetTexture(HrMaterial::TS_ALBEDO);
	if (pDiffuseTex)
	{
		auto& pDiffuseTexParam = GetRenderEffect()->GetParameterByName("texAlbedo");
		if (pDiffuseTexParam)
			pDiffuseTexParam->operator=(pDiffuseTex.get());
		nEnableAlbedoTex = 1u;
	}

	uint32 nEnableMetalTex = 0u;
	const HrTexturePtr& pMetalnessTex = GetSubMesh()->GetMaterial()->GetTexture(HrMaterial::TS_METALNESS);
	if (pMetalnessTex)
	{
		auto& pMetalnessParam = GetRenderEffect()->GetParameterByName("texMetallic");
		if (pMetalnessParam)
			pMetalnessParam->operator=(pMetalnessTex.get());
		nEnableMetalTex = 1u;
	}

	uint32 nEnableNormalmap = 0u;
	const HrTexturePtr& pNormalmapTex = GetSubMesh()->GetMaterial()->GetTexture(HrMaterial::TS_NORMALMAP);
	if (pNormalmapTex)
	{
		auto& pNormalmapTexParam = GetRenderEffect()->GetParameterByName("texNormal");
		if (pNormalmapTexParam)
			pNormalmapTexParam->operator=(pNormalmapTex.get());
		nEnableNormalmap = 1u;
	}

	auto& pMaterialParam0 = GetRenderEffect()->GetMaterialParameterByName("material_param0");
	if (pMaterialParam0)
		*pMaterialParam0 = (nEnableAlbedoTex | (nEnableMetalTex << 1) | (nEnableNormalmap << 2) );
}

const AABBox& HrRenderable::GetAABBox()
{
	return m_pSubMesh->GetAABB();
}

