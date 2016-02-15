﻿#include "HrDirector.h"
#include "Scene/HrSceneManager.h"
#include "AppWin32/HrWin32WindowEventUtilities.h"
#include "HrUtilTools/Include/HrUtil.h"
#include "HrUtilTools/Include/HrModuleLoader.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderFactory.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
#include "HrLog.h"


using namespace Hr;

HrDirectorPtr HrDirector::m_s_pUniqueDirector;

HrDirector& HrDirector::GetInstance()
{
	if (!m_s_pUniqueDirector)
	{
		m_s_pUniqueDirector = MakeUniquePtr<HrDirector>();
	}
	return *m_s_pUniqueDirector;
}

void HrDirector::ReleaseInstance()
{
	if (m_s_pUniqueDirector)
	{
		m_s_pUniqueDirector->Release();
	}
	m_s_pUniqueDirector.reset();
}

HrDirector::HrDirector()
{
	m_bEndMainLoop = false;
	m_pShareSceneManager = std::dynamic_pointer_cast<ISceneManager>(MakeSharedPtr<HrSceneManager>());
}

HrDirector::~HrDirector()
{
}

bool HrDirector::Init()
{
	HRLOG(_T("HrDirector Init!"));

	m_pUniqueRenderLoader = MakeUniquePtr<HrModuleLoader>("HrRenderD3D11");
	m_pUniqueRenderLoader->HrLoadModule();
	typedef void(*RENDER_INIT_FUNC)(IRenderFactoryPtr& ptr);
	RENDER_INIT_FUNC func = static_cast<RENDER_INIT_FUNC>(m_pUniqueRenderLoader->GetProcAddress(std::string("HrModuleInitialize")));
	if (func)
	{
		func(m_pShareRenderFactory);
		if (m_pShareRenderFactory)
		{
			m_pShareRender = m_pShareRenderFactory->CreateRender();
		}
	}
	else
	{
		HRERROR(_T("RenderInitFunc is null"));
		return false;
	}

	m_pShareRender->Init(640, 480, &HrWin32WindowEventUtilities::WinProc);

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
		//m_pTimer->Tick();
		Render();
	}
}

void HrDirector::End()
{
	m_bEndMainLoop = true;
}

void HrDirector::Release()
{
	m_pShareRender->Release();
	m_pShareRender.reset();
	m_pShareRenderFactory.reset();
	typedef void(*RENDER_RELEASE_FUNC)();
	RENDER_RELEASE_FUNC releaseFunc = static_cast<RENDER_RELEASE_FUNC>(m_pUniqueRenderLoader->GetProcAddress(std::string("HrModuleUnload")));
	if (releaseFunc)
	{
		releaseFunc();
	}
	m_pUniqueRenderLoader->HrFreeModule();
}

bool HrDirector::Render()
{
	m_pShareRender->StartRender();

	return true;
}

void HrDirector::RunScene(const IScenePtr& pScene)
{
	m_pShareSceneManager->RunScene(pScene);
}

