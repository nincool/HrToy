#include "HrDirector.h"
#include "Platform/AppWin32/HrWindowWin.h"
#include "Scene/HrSceneManager.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrUtilTools/Include/HrModuleLoader.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderFactory.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
#include "Asset/HrGeometryFactory.h"
#include "Asset/HrComponentFactory.h"
#include "Asset/HrResourceManagerFactory.h"
#include "Asset/HrRenderEffectManager.h"
#include "Render/HrRenderTarget.h"
#include "Render/HrCamera.h"
#include "Render/HrRenderFactory.h"
#include "Config/HrContextConfig.h"
#include "HrLog.h"

using namespace Hr;

HrDirector::HrDirector()
{
	m_bEndMainLoop = false;
	m_pSceneManager = MakeSharedPtr<HrSceneManager>();
}

HrDirector::~HrDirector()
{

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
		return false;
	}

	if (!CreateRenderTarget())
	{
		return false;
	}

	HrResourceManagerFactory::GetInstance().CreateResourceManager();

	return true;
}

bool HrDirector::CreateAppWindow()
{
	m_pWindow = MakeSharedPtr<HrWindowWin>();

	return true;
}

bool HrDirector::CreateRenderEngine()
{
	m_pRenderModuleLoader = MakeUniquePtr<HrModuleLoader>("HrRenderD3D11");
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

bool HrDirector::CreateRenderTarget()
{
	m_pRenderTarget = m_pRenderFactory->CreateRenderTarget();
	m_pRenderTarget->CreateRenderWindow(HrContextConfig::Instance()->GetRenderTargetViewWidth(), HrContextConfig::Instance()->GetRenderTargetViewHeight());
	m_pRenderEngine->SetRenderTarget(m_pRenderTarget);

	return true;
}

void HrDirector::StartMainLoop()
{
	while (!m_bEndMainLoop)
	{
		m_pWindow->Update();

		Update();
	}
}

void HrDirector::Update()
{
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
	HrGeometryFactory::ReleaseInstance();
	HrComponentFactory::ReleaseInstance();
	HrResourceManagerFactory::ReleaseInstance();

	//m_pShareRenderTarget.reset();
	//m_pShareSceneManager.reset();
	
	//m_pShareRender->Release();
	//m_pShareRender.reset();
	
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

bool HrDirector::Render()
{
	return true;
}

void HrDirector::RunScene(const HrScenePtr& pScene)
{
	m_pSceneManager->RunScene(pScene);
}

