#include "Kernel/HrDirector.h"
#include "Kernel/HrInputManager.h"
#include "Kernel/HrLog.h"
#include "Kernel/HrScheduler.h"
#include "Platform/AppWin32/HrWindowWin.h"
#include "Scene/HrSceneManager.h"

#include "Render/HrRenderSystem.h"
#include "Kernel/HrRenderCoreComponent.h"

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
	m_pSceneManager = HrMakeSharedPtr<HrSceneManager>();
	m_pScheduler = HrMakeSharedPtr<HrScheduler>();
}

HrDirector::~HrDirector()
{
	//内存检测
	m_pScheduler.reset();
	m_pSceneManager.reset();
}

bool HrDirector::Init()
{
	HRLOG(_T("HrDirector Init!"));

	if (!CreateAppWindow())
	{
		return false;
	}



	if (!CreateRenderEngine())
	{
		HRERROR("CreateRenderEngine Error!");
		return false;
	}

	if (!CreateRenderTarget())
	{
		HRERROR("CreateRenderTarget Error!");
		return false;
	}
	
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

	CreateRenderComponent();

	m_fDeltaTime = 0;
	m_lastUpdate = std::chrono::steady_clock::now();

	return true;
}

bool HrDirector::CreateAppWindow()
{
	m_pWindow = HrMakeSharedPtr<HrWindowWin>();

	return true;
}

void HrDirector::ReleaseAppWindow()
{

}

void HrDirector::CreateRenderComponent()
{
	m_pRenderComponent = HrMakeSharedPtr<HrRenderCoreComponent>("HrRenderD3D11");
}

bool HrDirector::CreateRenderEngine()
{
	m_pRenderModuleLoader = HrMakeUniquePtr<HrModuleLoader>("HrRenderD3D11");
	m_pRenderModuleLoader->HrLoadModule();
	
	typedef void(*RENDER_INIT_FUNC)(HrRenderFactoryPtr& ptr);
	RENDER_INIT_FUNC func = static_cast<RENDER_INIT_FUNC>(m_pRenderModuleLoader->GetProcAddress(std::string("HrModuleInitialize")));
	if (func)
	{
		func(m_pRenderFactory);
		if (m_pRenderFactory)
		{
			m_pRenderEngine = m_pRenderFactory->CreateRender();
		}
	}
	else
	{
		HRERROR(_T("RenderInitFunc is null"));
		return false;
	}

	if (!m_pRenderEngine->Init())
	{
		return false;
	}

	return true;
}

void HrDirector::ReleaseRenderEngine()
{
	m_pRenderTarget.reset();
	m_pRenderEngine->ReleaseRenderEngine();
	m_pRenderEngine.reset();

	m_pRenderFactory.reset();

	typedef void(*RENDER_RELEASE_FUNC)();
	RENDER_RELEASE_FUNC releaseFunc = static_cast<RENDER_RELEASE_FUNC>(m_pRenderModuleLoader->GetProcAddress(std::string("HrModuleUnload")));
	if (releaseFunc)
	{
		releaseFunc();
	}
	m_pRenderModuleLoader->HrFreeModule();
	m_pRenderModuleLoader.reset();

}

bool HrDirector::CreateRenderTarget()
{
	m_pRenderTarget = m_pRenderFactory->CreateRenderTarget();
	m_pRenderTarget->CreateRenderTargetView(HrContextConfig::Instance()->GetRenderTargetViewWidth(), HrContextConfig::Instance()->GetRenderTargetViewHeight());
	m_pRenderEngine->SetRenderTarget(m_pRenderTarget);

	return true;
}

void HrDirector::ReleaseRenderTarget()
{

}

bool HrDirector::CreateRenderState()
{
	if (m_pRenderFactory)
	{
		m_pRenderFactory->CreateBuildInRasterizerState();
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
		m_pWindow->Update();

		if (m_bEndMainLoop)
		{
			break;
		}

		Update();
	}
}

void HrDirector::Update()
{
	HrInputManager::Instance()->Capture();

	std::chrono::steady_clock::time_point nowTime = std::chrono::steady_clock::now();
	m_fDeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(nowTime - m_lastUpdate).count() / 1000000.0f;
	m_fDeltaTime = (std::max)(0.0f, m_fDeltaTime);
	m_lastUpdate = nowTime;

	m_pScheduler->Update(m_fDeltaTime);

	m_pSceneManager->UpdateScene();
	m_pSceneManager->RenderScene(m_pRenderTarget);
}

void HrDirector::End()
{
	m_bEndMainLoop = true;

	m_pSceneManager->Destroy();

	if (m_pWindow)
	{
		m_pWindow->Destroy();
	}
}

void HrDirector::Release()
{
	//先释放资源
	HrResourceManager::Instance()->ReleaseAllResources();
	ReleaseRenderEngine();
}

bool HrDirector::Render()
{
	return true;
}

void HrDirector::RunScene(const HrScenePtr& pScene)
{
	m_pSceneManager->RunScene(pScene);
}
