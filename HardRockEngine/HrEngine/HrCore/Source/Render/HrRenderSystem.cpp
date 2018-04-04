#include "Render/HrRenderSystem.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderFrame.h"
#include "Render/HrRender.h"
#include "Render/HrViewPort.h"
#include "Render/HrRenderable.h"
#include "Render/HrRenderQueue.h"
#include "Render/HrRenderFrameParameters.h"
#include "Asset/HrRenderEffect.h"
#include "Kernel/HrDirector.h"
#include "Kernel/HrCoreComponentWin.h"
#include "Scene/HrSceneNode.h"
#include "Scene/HrSceneObject.h"

using namespace Hr;

const std::string HrRenderSystem::m_sc_strScreenFrameBufferKey ="ScreenFrameBufferKey";

HrRenderSystem::HrRenderSystem(HrRenderFactoryPtr& pRenderFactory)
{
	m_pRenderFactory = pRenderFactory;
	m_pRenderParameters = HrMakeUniquePtr<HrRenderFrameParameters>();

	CreateRender();
	//Ĭ���ȴ�����Ļ��Ⱦ
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

			const std::vector<HrRenderablePtr>& vecRenderables = pRenderQueue->GetRenderables();
			for (auto& iteRenderable : vecRenderables)
			{
				pRenderFrameParam->SetCurrentRenderable(iteRenderable);

				iteRenderable->Render();
			}
		}
	}
}
