#include "HrDirector.h"
#include "HrRenderSystem/Include/IRenderer.h"
#include "HrWin32WindowEventUtilities.h"
#include "HrSystemSupporter.h"
#include "HrLog.h"
#include "HrTimer.h"

using namespace Hr;

HrDirector* HrDirector::m_s_pInstance = nullptr;

HrDirector::HrDirector()
{
	m_pSystemSupporter = nullptr;

	m_hHandleRender = nullptr;
	m_pRenderSystem = nullptr;

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

	if (!LoadRenderSystem())
	{
		HRERROR(_T("Director Init : LoadRenderSystem Error!"));
		return false;
	}
	
	return true;
}

bool Hr::HrDirector::LoadRenderSystem()
{
	typedef IRenderer*(*RENDER_START_FUNC)();
	TCHAR finalModuleName[MAX_PATH] = HR_PREFIX;
	_tcscat(finalModuleName, _T("HrRenderD3D11"));
	_tcscat(finalModuleName, HR_SUFFIX);

	m_hHandleRender = HR_MODULE_OPEN(finalModuleName);
	if (m_hHandleRender != nullptr)
	{
		RENDER_START_FUNC pFuncStart = (RENDER_START_FUNC)HR_MODULE_GETSYSTEM(m_hHandleRender, HR_MODULE_START_FUNC);
		if (pFuncStart != nullptr)
		{
			m_pRenderSystem = pFuncStart();
		}
	}
	if (m_pRenderSystem == nullptr)
	{
		return false;
	}
	m_pRenderSystem->Init(600, 480, HrWin32WindowEventUtilities::WinProc);

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
	
	Release();
}

void HrDirector::Release()
{
	typedef void(*RENDER_END_FUNC)();
	if (m_hHandleRender != nullptr)
	{
		RENDER_END_FUNC pFuncEnd = (RENDER_END_FUNC)HR_MODULE_GETSYSTEM(m_hHandleRender, HR_MUDULE_END_FUNC);
		if (pFuncEnd != nullptr)
		{
			pFuncEnd();
		}
		HR_MODULE_FREE(m_hHandleRender);
	}
}

bool HrDirector::Render()
{
	m_pRenderSystem->StartRender();

	return true;
}


