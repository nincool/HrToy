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

HrRenderable::HrRenderable()
{	
	m_pSceneObj = nullptr;
}

HrRenderable::HrRenderable(const HrSubMeshPtr& pSubMesh)
{
	m_pSubMesh = pSubMesh;
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

//void HrRenderable::SetSubMesh(const HrSubMeshPtr& pSubMesh)
//{
//	m_pSubMesh = pSubMesh;
//}

void HrRenderable::SetRenderEffect(const HrRenderEffectPtr& pRenderEff)
{
	m_pRenderEffect = pRenderEff;

	m_pCurTechnique = m_pRenderEffect->GetBestTechnique(m_pSubMesh->GetRenderLayout());
	BOOST_ASSERT(m_pCurTechnique);
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

void HrRenderable::SetAttachSceneObject(HrSceneObject* pSceneObj)
{
	m_pSceneObj = pSceneObj;
}

HrSceneObject* HrRenderable::GetAttachSceneObject() const
{
	return m_pSceneObj;
}

void HrRenderable::Render(const HrRenderTechniquePtr& pRenderTech)
{
	OnRenderBegin();

	if (pRenderTech)
		HrDirector::Instance()->GetRenderModule()->DoRender(pRenderTech, GetRenderLayout());
	else
		HrDirector::Instance()->GetRenderModule()->DoRender(GetRenderTechnique(), GetRenderLayout());

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

void HrRenderable::UpdateRenderEffectParam()
{
	auto& pRenderFrameParam = HrDirector::Instance()->GetSceneModule()->GetRenderFrameParameters();
	GetRenderEffect()->UpdateAutoEffectParams(pRenderFrameParam);

	uint32 nUseBaseTex = 0u;
	const HrTexturePtr& pDiffuseTex = GetSubMesh()->GetMaterial()->GetTexture(HrMaterial::TS_ALBEDO);
	if (pDiffuseTex)
	{
		auto& pDiffuseTexParam = GetRenderEffect()->GetParameterByName("texAlbedo");
		if (pDiffuseTexParam)
			pDiffuseTexParam->operator=(pDiffuseTex.get());
		nUseBaseTex = 1u;
	}
	auto& pFlagUseBaseTex = GetRenderEffect()->GetParameterByName("flag_use_basetex");
	if (pFlagUseBaseTex)
		*pFlagUseBaseTex = nUseBaseTex;

	uint32 nUseNormalMap = 0u;
	const HrTexturePtr& pNormalmapTex = GetSubMesh()->GetMaterial()->GetTexture(HrMaterial::TS_NORMAL);
	if (pNormalmapTex)
	{
		auto& pNormalmapTexParam = GetRenderEffect()->GetParameterByName("texNormal");
		if (pNormalmapTexParam)
			pNormalmapTexParam->operator=(pNormalmapTex.get());
		nUseNormalMap = 1u;
	}
	auto& pFlagUseNormalTex = GetRenderEffect()->GetParameterByName("flag_use_normalmap");
	if (pFlagUseNormalTex)
		*pFlagUseNormalTex = nUseNormalMap;
}

const AABBox& HrRenderable::GetAABBox()
{
	return m_pSubMesh->GetAABB();
}
