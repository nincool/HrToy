#include "HrDirector.h"
#include "Scene/HrSceneManager.h"
#include "Platform/AppWin32/HrWin32WindowEventUtilities.h"
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
#include "HrLog.h"

using namespace Hr;

HrDirector::HrDirector()
{
	m_bEndMainLoop = false;
	//m_pShareSceneManager = MakeSharedPtr<HrSceneManager>();
}

HrDirector::~HrDirector()
{

}

bool HrDirector::Init()
{
	HRLOG(_T("HrDirector Init!"));

	m_pUniqueRenderLoader = MakeUniquePtr<HrModuleLoader>("HrRenderD3D11");
	m_pUniqueRenderLoader->HrLoadModule();
	typedef void(*RENDER_INIT_FUNC)(HrRenderFactoryPtr& ptr);
	RENDER_INIT_FUNC func = static_cast<RENDER_INIT_FUNC>(m_pUniqueRenderLoader->GetProcAddress(std::string("HrModuleInitialize")));
	if (func)
	{
		func(m_pShareRenderFactory);
		if (m_pShareRenderFactory)
		{
			//m_pShareRender = m_pShareRenderFactory->CreateRender();
			//m_pShareRenderTarget = m_pShareRenderFactory->CreateRenderTarget();
		}
	}
	else
	{
		HRERROR(_T("RenderInitFunc is null"));
		return false;
	}

	//if (!m_pShareRender->Init())
	//{
	//	return false;
	//}

	//m_pShareRenderTarget->CreateRenderWindow(640, 480, &HrWin32WindowEventUtilities::WinProc);
	//m_pShareRender->SetRenderTarget(m_pShareRenderTarget);

	//HrResourceManagerFactory::GetInstance().CreateResourceManager();

	return true;
}

void HrDirector::StartMainLoop()
{
	while (!m_bEndMainLoop)
	{
#if HR_TARGET_PLATFORM == HR_PLATFORM_WIN32
		if (!HrWin32WindowEventUtilities::MessagePump())
		{
			break;
		}
#endif
		Update();
	}
}

void HrDirector::Update()
{
	//m_pShareSceneManager->UpdateScene();
	//m_pShareSceneManager->RenderScene(m_pShareRenderTarget);
}

void HrDirector::End()
{
	m_bEndMainLoop = true;

	//m_pShareSceneManager->Destroy();
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
	
	m_pShareRenderFactory.reset();

	typedef void(*RENDER_RELEASE_FUNC)();
	RENDER_RELEASE_FUNC releaseFunc = static_cast<RENDER_RELEASE_FUNC>(m_pUniqueRenderLoader->GetProcAddress(std::string("HrModuleUnload")));
	if (releaseFunc)
	{
		releaseFunc();
	}
	m_pUniqueRenderLoader->HrFreeModule();
	m_pUniqueRenderLoader.reset();
}

bool HrDirector::Render()
{
	return true;
}

void HrDirector::RunScene(const HrScenePtr& pScene)
{
	m_pShareSceneManager->RunScene(pScene);
}

