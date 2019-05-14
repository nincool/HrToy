#include "Render/HrSkyBox.h"
#include "Asset/HrTexture.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrRenderEffectParameter.h"
#include "Render/HrRenderFrameParameters.h"
#include "Render/HrMeshRenderable.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrResourceModule.h"
#include "Kernel/HrSceneModule.h"

using namespace Hr;

//////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////

HrSkyBox::HrSkyBox(const HrSubMeshPtr& pSubMesh) : HrStaticMeshRenderable(pSubMesh)
{
	SetRenderEffect(HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("HrSky.json"));
	m_pEffectParamCubeMap = m_pRenderEffect->GetParameterByName("texReflectCube");
	m_pEffectParamWVP = m_pRenderEffect->GetParameterByName("world_view_proj_matrix");
}

HrSkyBox::~HrSkyBox()
{

}

void HrSkyBox::SetCubeMap(const HrTexturePtr& pCubeMap)
{
	m_pEffectParamCubeMap->operator =(pCubeMap.get());
}

void HrSkyBox::OnRenderBegin()
{
	auto& pRenderFrameParam = HrDirector::Instance()->GetSceneModule()->GetRenderFrameParameters();
	const float3& cameraPos = pRenderFrameParam->GetCameraPosition();
	Matrix4 worldMat = pRenderFrameParam->GetWorldMatrix();
	worldMat(3, 0) = cameraPos[0];
	worldMat(3, 1) = cameraPos[1];
	worldMat(3, 2) = cameraPos[2];
	*m_pEffectParamWVP = worldMat * pRenderFrameParam->GetViewProjMatrix();
}

void HrSkyBox::OnRenderEnd()
{

}
