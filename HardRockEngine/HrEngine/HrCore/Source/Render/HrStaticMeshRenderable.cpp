#include "Render/HrStaticMeshRenderable.h"
#include "Asset/HrMesh.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrTexture.h"
#include "Asset/HrRenderEffectParameter.h"
#include "Render/HrRenderFrameParameters.h"


using namespace Hr;

HrStaticMeshRenderable::HrStaticMeshRenderable()
{

}

HrStaticMeshRenderable::HrStaticMeshRenderable(HrSubMesh* pSubMesh, HrMaterial* pMaterial)
{
	m_pSubMesh = pSubMesh;
	m_pMaterial = pMaterial;
}

HrStaticMeshRenderable::~HrStaticMeshRenderable()
{

}

HrRenderLayout* HrStaticMeshRenderable::GetRenderLayout()
{
	BOOST_ASSERT(m_pSubMesh);
	return m_pSubMesh->GetRenderLayout();
}

void HrStaticMeshRenderable::UpdateRenderFrameParametersImpl(HrRenderFrameParameters& renderFrameParameters)
{
	if (m_pSubMesh != nullptr)
	{
		HrMaterial* pMaterial = m_pSubMesh->GetMaterial();
		if (pMaterial != nullptr)
		{
			renderFrameParameters.SetCurrentMaterial(pMaterial);
		}
	}
}

void HrStaticMeshRenderable::UpdateEffectParametersImpl()
{
	if (m_pSubMesh != nullptr)
	{
		if (m_pSubMesh->GetTexture() != nullptr)
		{
			HrRenderEffectParameter* pTexParam = m_pRenderEffect->GetParameterByName("g_tex");
			if (pTexParam != nullptr)
				*pTexParam = m_pSubMesh->GetTexture();
		}
	}
}

