#include "Kernel/HrDirector.h"
#include "Kernel/HrInputManager.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrScheduler.h"
#include "Scene/HrSceneManager.h"

#include "Render/HrRenderSystem.h"
#include "Kernel/HrCoreComponentEvent.h"
#include "Kernel/HrCoreComponentRender.h"
#include "Kernel/HrCoreComponentWin.h"
#include "Kernel/HrCoreComponentScene.h"

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderFactory.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
#include "Render/HrRenderTarget.h"
#include "Render/HrCamera.h"
#include "Render/HrRenderFactory.h"
#include "Asset/HrResourceManager.h"
#include "Config/HrContextConfig.h"

using namespace Hr;

HrDirector::HrDirector()
{
	m_bEndMainLoop = false;
	m_pScheduler = HrMakeSharedPtr<HrScheduler>();
}

HrDirector::~HrDirector()
{
}

bool HrDirector::Init()
{
	HRLOG(_T("HrDirector Init!"));

	CreateEventComponent();
	CreateWindowComponent();
	CreateSceneComponent();
	CreateRenderComponent();
	
	if (!CreateRenderState())
	{
		HRERROR("CreateRenderState Error!");
		return false;
	}

	if (!CreateResourceManager())
	{
		HRERROR("CreateResourceManager Error!");
		return false;
	}

	if (!CreateInputManager())
	{
		HRERROR("CreateInputManager Error!");
		return false;
	}

	m_fDeltaTime = 0;
	m_lastUpdate = std::chrono::steady_clock::now();

	return true;
}


bool HrDirector::CreateRenderState()
{
	//todo
	if (true)
	{
		m_pRenderComponent->GetRenderSystem()->GetRenderFactory()->CreateBuildInRasterizerState();
		return true;
	}
	return false;
}

void HrDirector::ReleaseRenderState()
{

}

bool HrDirector::CreateResourceManager()
{
	HrResourceManager::Instance()->InitResourceManager();

	return true;
}

void HrDirector::ReleaseResourceManager()
{

}

bool HrDirector::CreateInputManager()
{
	HrInputManager::Instance()->CreateInputSystem();

	return true;
}

void HrDirector::ReleaseInputManager()
{
	
}

void HrDirector::StartMainLoop()
{
	while (!m_bEndMainLoop)
	{
		m_pWindowComponet->UpdateWindowMsg();

		if (m_bEndMainLoop)
		{
			break;
		}

		Update();
		Render();
	}
}

void HrDirector::Update()
{
	CalculateDeltaTime();

	HrInputManager::Instance()->Capture();

	m_pScheduler->Update(m_fDeltaTime);

	m_pWindowComponet->Update(m_fDeltaTime);
	m_pSceneManagerComponent->Update(m_fDeltaTime);
	m_pRenderComponent->Update(m_fDeltaTime);
}

bool HrDirector::Render()
{
	m_pSceneManagerComponent->RenderScene();
	return true;
}

void HrDirector::CalculateDeltaTime()
{
	std::chrono::steady_clock::time_point nowTime = std::chrono::steady_clock::now();
	m_fDeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(nowTime - m_lastUpdate).count() / 1000000.0f;
	m_fDeltaTime = (std::max)(0.0f, m_fDeltaTime);
	m_lastUpdate = nowTime;
}

void HrDirector::End()
{
	m_bEndMainLoop = true;

	m_pSceneManagerComponent->Destroy();

	if (m_pWindowComponet)
	{
		m_pWindowComponet->DestroyWindow();
	}
}

void HrDirector::Release()
{
	//先释放资源
	HrResourceManager::Instance()->ReleaseAllResources();
}

void HrDirector::RunScene(const HrScenePtr& pScene)
{
	m_pSceneManagerComponent->RunScene(pScene);
}

void HrDirector::CreateEventComponent()
{
	m_pEventComponent = HrMakeSharedPtr<HrCoreComponentEvent>();
}

void HrDirector::CreateWindowComponent()
{
	m_pWindowComponet = HrMakeSharedPtr<HrCoreComponentWin>();
}

void HrDirector::CreateRenderComponent()
{
	m_pRenderComponent = HrMakeSharedPtr<HrCoreComponentRender>("HrRenderD3D11");
	m_pRenderComponent->InitComponent();
}

void HrDirector::CreateSceneComponent()
{
	m_pSceneManagerComponent = HrMakeSharedPtr<HrCoreComponentScene>();
}

const HrCoreComponentEventPtr& HrDirector::GetEventComponent()
{
	return m_pEventComponent;
}

const HrCoreComponentWinPtr& HrDirector::GetWinCoreComponent()
{
	return m_pWindowComponet;
}

const HrCoreComponentRenderPtr& HrDirector::GetRenderCoreComponent()
{
	return m_pRenderComponent;
}

const HrCoreComponentScenePtr& HrDirector::GetSceneComponent()
{
	return m_pSceneManagerComponent;
}

