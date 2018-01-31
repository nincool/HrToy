#include "Kernel/HrCoreComponentRender.h"
#include "Kernel/HrLog.h"
#include "Render/HrRenderSystem.h"
#include "Render/HrRenderTarget.h"
#include "Render/HrRenderFactory.h"
#include "Render/HrRenderFrame.h"

using namespace Hr;

HrCoreComponentRender::HrCoreComponentRender(const std::string& strRenderModule)
{
	if (this->CreateRenderFactory(strRenderModule))
	{
		CreateRenderSystem();
	}
}

HrCoreComponentRender::~HrCoreComponentRender()
{

}

bool HrCoreComponentRender::InitComponent()
{
	//初始化默认渲染到屏幕
	m_pRenderSystem->BindScreenFrameBuffer();

	return true;
}

void HrCoreComponentRender::BindFrameBuffer(const HrRenderFramePtr& pRenderFrame)
{
	m_pRenderSystem->BindFrameBuffer(pRenderFrame);
}

void HrCoreComponentRender::OnRenderFrameBegin()
{
	ClearRenderFame();
}

void HrCoreComponentRender::OnRenderFrameEnd()
{
}

void HrCoreComponentRender::RenderBindFrameBuffer(const HrRenderQueuePtr& pRenderQueue, const HrRenderFrameParametersPtr& pRenderFrameParam)
{
	m_pRenderSystem->RenderBindFrameBuffer(pRenderQueue, pRenderFrameParam);
}

void HrCoreComponentRender::ClearRenderFame()
{
	m_pRenderSystem->ClearRenderTarget();
	m_pRenderSystem->ClearDepthStencil();
}

void HrCoreComponentRender::Present()
{
	m_pRenderSystem->Present();
}

bool HrCoreComponentRender::CreateRenderFactory(const std::string& strRenderModule)
{
	m_pRenderModuleLoader = HrMakeUniquePtr<HrModuleLoader>(strRenderModule);
	if (m_pRenderModuleLoader->HrLoadModule())
	{
		typedef void(*RENDER_INIT_FUNC)(HrRenderFactoryPtr& ptr);
		RENDER_INIT_FUNC func = static_cast<RENDER_INIT_FUNC>(m_pRenderModuleLoader->GetProcAddress(std::string("HrModuleInitialize")));
		if (func)
		{
			func(m_pRenderFactory);
		}

		return true;
	}

	return false;
}

const HrRenderFactoryPtr& HrCoreComponentRender::GetRenderFactory() const
{
	return m_pRenderFactory;
}

void HrCoreComponentRender::CreateRenderSystem()
{
	if (m_pRenderFactory)
	{
		m_pRenderSystem = HrMakeSharedPtr<HrRenderSystem>(m_pRenderFactory);
	}
}

void HrCoreComponentRender::AddViewPort(const HrViewPortPtr& pViewPort)
{
	m_pRenderSystem->GetBindFrameBuffer()->AddViewPort(pViewPort);
}

