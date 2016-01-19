#include "HrDirector.h"
#include "HrSceneManager.h"
#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11Render.h"
#include "HrWin32WindowEventUtilities.h"
#include "HrSystemSupporter.h"
#include "HrLog.h"
#include "HrTimer.h"

using namespace Hr;
using namespace std;

HrDirector* HrDirector::m_s_pInstance = nullptr;

HrDirector::HrDirector()
{
	m_pSystemSupporter = nullptr;

	m_hHandleRender = nullptr;
	m_pShareRenderSystem = nullptr;

	m_pTimer = HR_NEW HrTimer();

	m_bEndMainLoop = false;
}

HrDirector::~HrDirector()
{
	HR_DELETE(m_pSystemSupporter);
	HR_DELETE(m_pTimer);
}

bool HrDirector::Init()
{
	if (m_pSystemSupporter == nullptr)
	{
		m_pSystemSupporter = HR_NEW HrSystemSupporter();
	}
	m_pSystemSupporter->Init();

	m_pShareSceneManager = make_shared<HrSceneManager>();

	if (!LoadRenderSystem())
	{
		HRERROR(_T("Director Init : LoadRenderSystem Error!"));
		return false;
	}
	
	return true;
}

bool Hr::HrDirector::LoadRenderSystem()
{
	typedef void (*RENDER_START_FUNC)(HrD3D11RenderPtr& ptr);
	TCHAR finalModuleName[MAX_PATH] = HR_PREFIX;
	_tcscat(finalModuleName, _T("HrRenderD3D11"));
	_tcscat(finalModuleName, HR_SUFFIX);

	m_hHandleRender = HR_MODULE_OPEN(finalModuleName);
	if (m_hHandleRender != nullptr)
	{
		RENDER_START_FUNC pFuncStart = (RENDER_START_FUNC)HR_MODULE_GETSYSTEM(m_hHandleRender, HR_MODULE_START_FUNC);
		if (pFuncStart != nullptr)
		{
			pFuncStart(m_pShareRenderSystem);
		}
	}
	if (m_pShareRenderSystem == nullptr)
	{
		return false;
	}
	if (!m_pShareRenderSystem->Init(600, 480, HrWin32WindowEventUtilities::WinProc))
	{
		HRERROR(_T("RenderSystem Init Error!"));

		return false;
	}

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
		m_pTimer->Tick();
		Render();
	}
}

void HrDirector::End()
{
	m_bEndMainLoop = true;
}

void HrDirector::Release()
{
	m_pShareRenderSystem->Release();
	typedef void(*RENDER_END_FUNC)();
	if (m_hHandleRender != nullptr)
	{
		RENDER_END_FUNC pFuncEnd = (RENDER_END_FUNC)HR_MODULE_GETSYSTEM(m_hHandleRender, HR_MUDULE_END_FUNC);
		if (pFuncEnd != nullptr)
		{
			pFuncEnd();
		}
		m_pShareRenderSystem.reset();
		HR_MODULE_FREE(m_hHandleRender);
	}
}

bool HrDirector::Render()
{
	m_pShareRenderSystem->StartRender();

	return true;
}


