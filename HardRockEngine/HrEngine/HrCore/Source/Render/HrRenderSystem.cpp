#include "Render/HrRenderSystem.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderFrame.h"
#include "Render/HrRender.h"
#include "Render/HrViewPort.h"
#include "Render/HrRenderable.h"
#include "Render/HrRenderQueue.h"
#include "Render/HrRenderFrameParameters.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrCoreComponentWin.h"

using namespace Hr;

const std::string HrRenderSystem::m_sc_strScreenFrameBufferKey ="ScreenFrameBufferKey";

HrRenderSystem::HrRenderSystem(HrRenderFactoryPtr& pRenderFactory)
{
	m_pRenderFactory = pRenderFactory;

	CreateRender();
	//默认先创建屏幕渲染
	CreateScreenFrameBuffer(HrDirector::Instance()->GetWinCoreComponent()->GetWindowWidth()
		, HrDirector::Instance()->GetWinCoreComponent()->GetWindowHeight());
}

HrRenderSystem::~HrRenderSystem()
{
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

void HrRenderSystem::BindScreenFrameBuffer()
{
	this->BindFrameBuffer(GetScreenFrameBuffer());
}

const HrRenderFramePtr& HrRenderSystem::GetBindFrameBuffer()
{
	return m_pRender->GetBindFrameBuffer();
}

void HrRenderSystem::CreateRender()
{
	m_pRender = m_pRenderFactory->CreateRender();
	m_pRender->Init();
}

void HrRenderSystem::CreateScreenFrameBuffer(uint32 nWidth, uint32 nHeight)
{
	m_pScreenFrameBuffer = m_pRenderFactory->CreateScreenRenderFrameBuffer(nWidth, nHeight);
	m_mapRenderFrames.insert(std::make_pair(m_sc_strScreenFrameBufferKey, m_pScreenFrameBuffer));
}

void HrRenderSystem::BindFrameBuffer(const HrRenderFramePtr& pRenderFrame)
{
	m_pRender->BindFrameBuffer(pRenderFrame);
}

void HrRenderSystem::ClearRenderTarget()
{
	GetBindFrameBuffer()->ClearTarget();
}

void HrRenderSystem::ClearDepthStencil()
{
	GetBindFrameBuffer()->ClearDepthStencil();
}

void HrRenderSystem::Present()
{
	GetBindFrameBuffer()->Present();
}

void HrRenderSystem::RenderBindFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrRenderFrameParametersPtr& pRenderFrameParam)
{
	const HrRenderFramePtr& pBindFrameBuffer = m_pRender->GetBindFrameBuffer();
	if (pBindFrameBuffer)
	{
		auto mapAllViewPorts = pBindFrameBuffer->GetAllViewPorts();
		for (auto& itemViewPort : mapAllViewPorts)
		{
			const HrViewPortPtr& pViewPort = itemViewPort.second;
			m_pRender->SetCurrentViewPort(pViewPort);
			pRenderFrameParam->SetCurrentCamera(pViewPort->GetCamera());

			const std::unordered_map<HrRenderablePtr, HrSceneNodePtr>& mapRenderables = pRenderQueue->GetRenderables();
			for (auto& itemMapRenderable : mapRenderables)
			{
				const HrRenderablePtr& pRenderable = itemMapRenderable.first;
				const HrSceneNodePtr& pSceneNode = itemMapRenderable.second;

				pRenderable->UpdateRenderFrameParameters(pRenderFrameParam);

				const HrRenderLayoutPtr& pRenderLayout = pRenderable->GetRenderLayout();
				const HrRenderTechniquePtr& pRenderTechnique = pRenderable->GetRenderTechnique();
				m_pRender->Render(pRenderTechnique, pRenderLayout);
			}

		}
	}
}
