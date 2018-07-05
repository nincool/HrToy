#include "Render/HrShadowMap.h"
#include "Kernel/HrDirector.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderFrame.h"
#include "Kernel/HrCoreComponentRender.h"
#include "Render/HrViewPort.h"
#include "Render/HrCamera.h"
#include "Asset/HrTexture.h"

using namespace Hr;

HrShadowMap::~HrShadowMap()
{
}

void HrShadowMap::CreateShadowTexture(uint32 nWidth, uint32 nHeight)
{
	m_pDepthStencilFrameBuffer = HrDirector::Instance()->GetRenderCoreComponent()->GetRenderFactory()->CreateDepthStencilFrameBuffer(nWidth, nHeight);
	
	m_pShadowMapCamera = HrMakeSharedPtr<HrCamera>("ShadowMapTextureCamera");
	HrViewPortPtr pViewPort = HrMakeSharedPtr<HrViewPort>(0.0f, 0.0f, static_cast<float>(nWidth), static_cast<float>(nHeight), 0);
	pViewPort->SetCamera(m_pShadowMapCamera);
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

