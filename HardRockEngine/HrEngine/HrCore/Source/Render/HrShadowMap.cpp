#include "Render/HrShadowMap.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderFrame.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrRenderModule.h"
#include "Kernel/HrResourceModule.h"
#include "Kernel/HrSceneModule.h"
#include "Render/HrViewPort.h"
#include "Render/HrCamera.h"
#include "Asset/HrTexture.h"
#include "Asset/HrMeshModel.h"
#include "Asset/HrMesh.h"
#include "Asset/HrRenderEffect.h"
#include "Asset/HrRenderEffectParameter.h"
#include "Asset/HrTexture.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrScene.h"
#include "Scene/HrSceneObject.h"

using namespace Hr;

HrShadowMap::~HrShadowMap()
{
}

void HrShadowMap::CreateShadowTexture(uint32 nWidth, uint32 nHeight)
{
	m_pDepthStencilFrameBuffer = HrDirector::Instance()->GetRenderModule()->GetRenderFactory()->CreateDepthStencilFrameBuffer(nWidth, nHeight);
	
	m_pShadowMapCamera = HrMakeSharedPtr<HrCamera>("ShadowMapTextureCamera");
	//HrViewPortPtr pViewPort = HrMakeSharedPtr<HrViewPort>(0.0f, 0.0f, static_cast<float>(nWidth), static_cast<float>(nHeight), 0);
	//pViewPort->SetCamera(m_pShadowMapCamera);
}

const HrRenderFramePtr& HrShadowMap::GetDepthStencilFrame()
{
	return m_pDepthStencilFrameBuffer;
}

const HrCameraPtr& HrShadowMap::GetShadowMapCamera()
{
	return m_pShadowMapCamera;
}

void HrShadowMap::OnStartRenderFrame()
{
	m_pDepthStencilFrameBuffer->ClearTarget();
	m_pDepthStencilFrameBuffer->ClearDepthStencil();
}

void HrShadowMap::OnEndRenderFrame()
{

}

///////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////
//void HrScreenQuadRenderable::UpdateRenderEffectParam()
//{
//	auto& pGBufferPosParam = GetRenderEffect()->GetParameterByName("texGBufferPos");
//	if (pGBufferPosParam)
//		pGBufferPosParam->operator=(m_pDeferredGBufferData->m_pGBufferPosition.get());
//
//	auto& pGBufferNormalParam = GetRenderEffect()->GetParameterByName("texGBufferNormal");
//	if (pGBufferNormalParam)
//		pGBufferNormalParam->operator=(m_pDeferredGBufferData->m_pGBufferNormal.get());
//
//	auto& pGBufferAlbedoParam = GetRenderEffect()->GetParameterByName("texGBufferAlbedo");
//	if (pGBufferAlbedoParam)
//		pGBufferAlbedoParam->operator=(m_pDeferredGBufferData->m_pGBufferAlbedo.get());
//}
//
//void HrScreenQuadRenderable::OnRenderBegin()
//{
//	HrStaticMeshRenderable::OnRenderBegin();
//}
//
//void HrScreenQuadRenderable::OnRenderEnd()
//{
//	HrStaticMeshRenderable::OnRenderEnd();
//}
//
//HrDeferredRender::HrDeferredRender()
//{
//	m_pDeferredGBufferData = HrMakeSharedPtr<HrDeferredGBufferData>();
//	m_pDeferredFrameBuffer = HrDirector::Instance()->GetRenderModule()->GetRenderFactory()->CreateDeferredFrameBuffer(1200, 800, m_pDeferredGBufferData);
//}
//
//HrDeferredRender::~HrDeferredRender()
//{
//
//}
//
//const HrRenderFramePtr& HrDeferredRender::GetDeferredFrameBuffer()
//{
//	return m_pDeferredFrameBuffer;
//}
//
//void HrDeferredRender::CreateScreenQuad()
//{
//	m_pSceneQuadNode = CreateQuadNodeP("TestDeferredQuad", 1200, 800);
//	//todo  这里渲染必须加入到Scene是否可以优化下
//	//HrDirector::Instance()->GetSceneModule()->GetRunningScene()->AddNode(pSceneNode);
//	m_pScreenQuad = m_pSceneQuadNode->GetChildByIndex(0)->GetSceneObject()->GetComponent<HrRenderableComponent>()->GetRenderable();
//}
//
//const HrSceneNodePtr& HrDeferredRender::GetSceneQuadNode()
//{
//	return m_pSceneQuadNode;
//}
//
//const HrRenderablePtr& HrDeferredRender::GetScreenQuadRenderable()
//{
//	if (!m_pScreenQuad)
//	{
//		CreateScreenQuad();
//	}
//	return m_pScreenQuad;
//}
//
//HrSceneNodePtr HrDeferredRender::CreateQuadNodeP(const std::string& strName, float fWidth, float fHeight)
//{
//	HrSceneNodePtr pSceneNode = CreateSceneNode(strName);
//
//	std::shared_ptr<HrMeshModelQuadP> pMeshModel = HrMakeSharedPtr<HrMeshModelQuadP>(fWidth, fHeight);
//
//	for (size_t i = 0; i < pMeshModel->GetMesh()->GetSubMeshNum(); ++i)
//	{
//		auto& pSubMesh = pMeshModel->GetMesh()->GetSubMesh(i);
//		HrSceneNodePtr pSubMeshNode = CreateSceneNode(pSubMesh->GetName());
//		HrRenderableComponentPtr pRenderableCom = pSubMeshNode->GetSceneObject()->AddComponent<HrRenderableComponent>();
//		HrRenderablePtr pRenderable = HrMakeSharedPtr<HrScreenQuadRenderable>(pSubMesh, m_pDeferredGBufferData);
//		pRenderableCom->SetRenderable(pRenderable);
//		pRenderable->SetRenderEffect(HrDirector::Instance()->GetResourceModule()->RetriveResource<HrRenderEffect>("HrDeferredShading.json"));
//
//		pSceneNode->AddChild(pSubMeshNode);
//	}
//
//	return pSceneNode;
//}
//
//HrSceneNodePtr HrDeferredRender::CreateSceneNode(const std::string& strName)
//{
//	HrSceneNodePtr pSceneNode = HrMakeSharedPtr<HrSceneNode>(strName);
//
//	return pSceneNode;
//}
//
