#include "HrDirector.h"
#include "HrRenderSystem/Include/IRenderer.h"
#include "HrWin32WindowEventUtilities.h"

using namespace Hr;

HrDirector* HrDirector::m_s_pInstance = nullptr;

HrDirector::HrDirector()
{
	m_hHandleRender = nullptr;
	m_pRenderSystem = nullptr;
}

HrDirector::~HrDirector()
{
}

bool HrDirector::Init()
{
	if (!LoadRenderSystem())
	{
		return false;
	}
	
	return true;
}

bool Hr::HrDirector::LoadRenderSystem()
{
	typedef IRenderer*(*RENDER_START_FUNC)();
	TCHAR finalModuleName[MAX_PATH] = HR_PREFIX;
	_tcscat(finalModuleName, "HrRenderD3D11");
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
	m_pRenderSystem->Create(600, 480, HrWin32WindowEventUtilities::WinProc);

	return true;
}

void HrDirector::Go()
{
	while (true)
	{
		HrWin32WindowEventUtilities::MessagePump();
		Sleep(1);
	}
}
