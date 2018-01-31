#include "Render/HrStaticMeshRenderable.h"
#include "HrCore/Include/Render/HrSkinnedMeshRenderable.h"
#include "HrCore/Include/Render/HrRenderTechnique.h"
#include "HrCore/Include/Render/HrRenderLayout.h"
#include "HrCore/Include/Render/HrRenderFrameParameters.h"
#include "HrCore/Include/Asset/HrRenderEffect.h"
#include "HrCore/Include/Asset/HrPrefabModel.h"
#include "HrCore/Include/Asset/HrMesh.h"
#include "HrCore/Include/Asset/HrResourceManager.h"
#include "HrCore/Include/Asset/HrRenderEffectParameter.h"
#include "HrCore/Include/Kernel/HrDirector.h"


using namespace Hr;

HrStaticMeshRenderable::HrStaticMeshRenderable()
{

}

HrStaticMeshRenderable::HrStaticMeshRenderable(const HrSubMeshPtr& pSubMesh, const HrMaterialPtr& pMaterial)
{

}

HrStaticMeshRenderable::~HrStaticMeshRenderable()
{

}

const HrRenderLayoutPtr& HrStaticMeshRenderable::GetRenderLayout()
{
	if (m_pSubMesh != nullptr)
	{
		return m_pSubMesh->GetRenderLayout();
	}
	else
	{
		TRE("HrStaticMeshRenderable::GerRenderLayout Error!");
	}
}

void HrStaticMeshRenderable::UpdateRenderFrameParametersImpl(const HrRenderFrameParametersPtr& renderFrameParameters)
{
	//if (m_pSubMesh != nullptr)
	//{
	//	HrMaterial* pMaterial = m_pSubMesh->GetMaterial();
	//	if (pMaterial != nullptr)
	//	{
	//		renderFrameParameters.SetCurrentMaterial(pMaterial);
	//	}
	//}
}

void HrStaticMeshRenderable::UpdateEffectParametersImpl()
{
	//if (m_pSubMesh != nullptr)
	//{
	//	if (m_pSubMesh->GetTexture() != nullptr)
	//	{
	//		HrRenderEffectParameter* pTexParam = m_pRenderEffect->GetParameterByName("g_tex");
	//		if (pTexParam != nullptr)
	//		{
	//			HrTexture* pTexture = m_pSubMesh->GetTexture();
	//			if (pTexture == nullptr)
	//			{
	//				pTexture = HrResourceManager::Instance()->GetDefaultTexture();
	//			}
	//			*pTexParam = pTexture;
	//		}
	//	}
	//}
}

