#include "Kernel/HrDirector.h"
#include "Kernel/HrInputManager.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrScheduler.h"
#include "Scene/HrSceneManager.h"

#include "Render/HrRenderSystem.h"
#include "Kernel/HrEventSystemModule.h"
#include "Kernel/HrRenderModule.h"
#include "Kernel/HrWindowModule.h"
#include "Kernel/HrSceneModule.h"
#include "Kernel/HrResourceModule.h"

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
	HRLOG("HrDirector Destroy");
}

bool HrDirector::Init(void* pHwnd)
{
	HRLOG(_T("HrDirector Init!"));

	CreateModules(pHwnd);

	if (!CreateRenderState())
	{
		HRERROR("CreateRenderState Error!");
		return false;
	}

	if (!pHwnd)
	{
		if (!CreateInputManager())
		{
			HRERROR("CreateInputManager Error!");
			return false;
		}
	}

	m_fDeltaTime = 0;
	m_lastUpdate = std::chrono::steady_clock::now();

	return true;
}

void HrDirector::CreateModules(void* pHwnd)
{
	CreateEventSystemModule();
	CreateResourceModule();
	CreateWindowModule(pHwnd);
	CreateSceneModule();
	CreateRenderModule();

	for (auto& item : m_arrModules)
	{
		item->InitComponent();
	}
}

bool HrDirector::CreateRenderState()
{
	//todo
	if (true)
	{
		m_pRenderModule->GetRenderFactory()->CreateBuildInRasterizerState();
		return true;
	}
	return false;
}

void HrDirector::ReleaseRenderState()
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
		m_pWindowModule->UpdateWindowMsg();

		if (m_bEndMainLoop)
		{
			break;
		}

		LoopOnce();
	}
}

void HrDirector::LoopOnce()
{
	Update();
	Render();
}

void HrDirector::Update()
{
	CalculateDeltaTime();

	HrInputManager::Instance()->Capture();
	m_pScheduler->Update(m_fDeltaTime);

	for (auto& item : m_arrModules)
	{
		item->Update(m_fDeltaTime);
	}
}

bool HrDirector::Render()
{
	m_pSceneModule->RenderScene();
	
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

	m_pSceneModule->Destroy();

	if (m_pWindowModule)
	{
		m_pWindowModule->DestroyWindow();
	}
}

void HrDirector::Destroy()
{

} 

void HrDirector::CreateEventSystemModule()
{
	m_pEventSystemModule = HrMakeSharedPtr<HrEventSystemModule>();
	m_arrModules[MT_EVENTSYSTEM] = m_pEventSystemModule;
}

void HrDirector::CreateWindowModule(void* pHwnd)
{
	m_pWindowModule = HrMakeSharedPtr<HrWindowModule>(pHwnd);
	m_arrModules[MT_WINDOW] = m_pWindowModule;
}

void HrDirector::CreateRenderModule()
{
	m_pRenderModule = HrMakeSharedPtr<HrRenderModule>("HrRenderD3D11");
	m_arrModules[MT_RENDER] = m_pRenderModule;
}

void HrDirector::CreateSceneModule()
{
	m_pSceneModule = HrMakeSharedPtr<HrSceneModule>();
	m_arrModules[MT_SCENE] = m_pSceneModule;
}

void HrDirector::CreateResourceModule()
{
	m_pResourceModule = HrMakeSharedPtr<HrResourceModule>();
	m_arrModules[MT_RESOURCE] = m_pResourceModule;
}

const HrEventSystemModulePtr& HrDirector::GetEventSystemModule()
{
	return m_pEventSystemModule;
}

const HrWindowModulePtr& HrDirector::GetWindowModule()
{
	return m_pWindowModule;
}

const HrRenderModulePtr& HrDirector::GetRenderModule()
{
	return m_pRenderModule;
}

const HrSceneModulePtr& HrDirector::GetSceneModule()
{
	return m_pSceneModule;
}

const HrResourceModulePtr& HrDirector::GetResourceModule()
{
	return m_pResourceModule;
}

void HrDirector::Schedule(const std::function<void(float)>& callBack, void* pTarget, const std::string& strKey, float fInterval, uint32 nRepeat, float fDelay)
{
	m_pScheduler->Schedule(callBack, pTarget, strKey, fInterval, nRepeat, fDelay);
}

void HrDirector::UnSchedule(size_t nTargetHashKeyID, size_t nHashID)
{
	m_pScheduler->UnSchedule(nTargetHashKeyID, nHashID);
}

const HrSchedulerPtr& HrDirector::GetScheduler()
{
	return m_pScheduler;
}

