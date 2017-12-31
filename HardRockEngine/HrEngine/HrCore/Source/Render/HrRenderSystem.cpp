#include "Render/HrRenderSystem.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderFrame.h"
#include "Render/HrRender.h"


using namespace Hr;

HrRenderSystem::HrRenderSystem(HrRenderFactoryPtr& pRenderFactory)
{
	m_pRenderFactory = pRenderFactory;
}

HrRenderSystem::~HrRenderSystem()
{

}

void HrRenderSystem::InitRenderSystem()
{
	InitRender();

	m_pRenderTarget = m_pRenderFactory->CreateRenderTarget();

	BindScreenFrameBuffer();
}

const HrRenderFactoryPtr& HrRenderSystem::GetRenderFactory()
{
	return m_pRenderFactory;
}

const HrRenderPtr& HrRenderSystem::GetRender()
{
	return m_pRender;
}

const HrRenderFramePtr& HrRenderSystem::GetScreenFrameBuffer()
{
	return m_pScreenFrameBuffer;
}

const HrRenderTargetPtr& HrRenderSystem::GetRenderTarget()
{
	return m_pRenderTarget;
}

void HrRenderSystem::SetCurrentFrameBuffer(const HrRenderFramePtr& pRenderFrame)
{
	m_pRender->SetCurrentFrameBuffer(pRenderFrame);
}

HrRenderFramePtr HrRenderSystem::GetCurrentFrameBuffer()
{
	return m_pRender->GetCurrentFrameBuffer();
}

void HrRenderSystem::InitRender()
{
	m_pRender = m_pRenderFactory->CreateRender();
	m_pRender->Init();
}

void HrRenderSystem::BindScreenFrameBuffer()
{
	if (!m_pScreenFrameBuffer)
	{
		m_pScreenFrameBuffer = m_pRenderFactory->CreateRenderFrameBuffer();
		m_pScreenFrameBuffer->AttachRenderTarget(m_pRenderTarget);
	}
	m_pScreenFrameBuffer->OnBind();
}

void HrRenderSystem::ClearRenderTarget()
{
	HrRenderFramePtr pFrameBuffer = GetCurrentFrameBuffer();
	HrRenderFramePtr pTempFrameBuffer = m_pScreenFrameBuffer;
	pFrameBuffer->ClearTarget();
	//GetCurrentFrameBuffer()->ClearTarget();
}

void HrRenderSystem::ClearDepthStencil()
{
	GetCurrentFrameBuffer()->ClearDepthStencil();
}

void HrRenderSystem::SwapChain()
{
	GetCurrentFrameBuffer()->SwapChain();
}

